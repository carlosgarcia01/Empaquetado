/*
Case of study: AURA70/TSLLH-11082017-121735 -> There are three glints in the first frame

*/
#include "otracker.h"
#include <iostream>

HaarSurroundFeature::HaarSurroundFeature(int r1, int r2) : r_inner(r1), r_outer(r2){
    //  _________________
    // |        -ve      |
    // |     _______     |
    // |    |   +ve |    |
    // |    |   .   |    |
    // |    |_______|    |
    // |         <r1>    |
    // |_________<--r2-->|

    // Number of pixels in each part of the kernel
    int count_inner = r_inner*r_inner;
    int count_outer = r_outer*r_outer - r_inner*r_inner;

    // Frobenius normalized values
    //
    // Want norm = 1 where norm = sqrt(sum(pixelvals^2)), so:
    //  sqrt(count_inner*val_inner^2 + count_outer*val_outer^2) = 1
    //
    // Also want sum(pixelvals) = 0, so:
    //  count_inner*val_inner + count_outer*val_outer = 0
    //
    // Solving both of these gives:
    //val_inner = std::sqrt( (double)count_outer/(count_inner*count_outer + sq(count_inner)) );
    //val_outer = -std::sqrt( (double)count_inner/(count_inner*count_outer + sq(count_outer)) );

    // Square radius normalised values
    //
    // Want the response to be scale-invariant, so scale it by the number of pixels inside it:
    //  val_inner = 1/count = 1/r_outer^2
    //
    // Also want sum(pixelvals) = 0, so:
    //  count_inner*val_inner + count_outer*val_outer = 0
    //
    // Hence:
    val_inner = 1.0 / (r_inner*r_inner);
    val_outer = -val_inner*count_inner/count_outer;

}

cv::Size2f OTracker::m_lastEllipse;

float OTracker::calcBlurriness(const cv::Mat &frame){
    cv::Mat dst;
    cv::Laplacian(frame, dst, CV_64F);
    cv::Scalar mu, sigma;
    cv::meanStdDev(dst, mu, sigma);
    return sigma.val[0] * sigma.val[0];
}
OTracker::OTracker() :  m_cannyThreshold1(30),
                        //v1.0.9: m_cannyThreshold2(90),
                        m_cannyThreshold2(65),
                        //v1.0.8: m_erode(1),
                        m_erode(3),
                        m_lastErode(-1),
#if OSCANN == 0 //v1.0.6: New
                        m_withMouse(false),
                        m_mouseR(0),
#endif
                        m_blurImg(9),
                        m_blurRoi(9),
                        m_paddingValue(15),
                        m_glintsRoiPadding(10),
                        m_glintPadding(6),          //TODODroopyEyelid(2) -> KO  : NORMAL(6)
                        m_glintsDistance(10.0),
                        //v1.0.9: H12O 4107575 m_thresholdImg(0.29),
                        m_thresholdImg(0.22),
                        m_thresholdGlints(0.75){
    m_totalProcessed = 0;
    m_upperLeft = cv::Point(-1,-1);
    m_mouseGlintsTL = cv::Point(-1,-1);
    m_userRoi = cv::Rect(0,0,0,0);
    m_lastGlintsBR = cv::Point(0,0);
    m_lastGlintsTL = cv::Point(0,0);
    m_lastEllipse = cv::Size2f(-1,-1);
    resetBlinkVars();
    m_blinks.clear();
    if(params.defaultValues){
        params.Radius_Min = 3;
        //params.Radius_Max = 360;
        //Changed from 70 to 90 for H12O/epilepsia/generalizada/3995241
        params.Radius_Max = 90;
        params.CannyBlur = 1;
        params.StarburstPoints = 64;
        params.PercentageInliers = 30;
        params.InlierIterations = 2;
        params.ImageAwareSupport = true;
        params.EarlyTerminationPercentage = 95;
        params.EarlyRejection = true;
        params.Seed = -1;
    }
    double theta = 0.0;
    for(int i=-48,j=0; i<params.StarburstPoints-48;i++, j++){
        theta = i * 2*PI/params.StarburstPoints;
        m_ptoDirs[j] = cv::Point2f((float)std::cos(theta), (float)std::sin(theta));
        m_starburstPtos[j] = false;
    }
    m_vdoImg = cv::Mat(cv::Size(640, 480), CV_8UC3);
    //v1.0.8
    m_initialErode = m_erode;
}
OTracker::~OTracker(){}
void OTracker::setID(unsigned int id){m_id = id;}
std::string OTracker::getLastError(){
    return m_errorMsg;
}
#if OSCANN == 0 //v1.0.6: New
    void OTracker::onMouse( int event, int x, int y){
        if(event == cv::EVENT_LBUTTONDOWN){
            m_upperLeft = cv::Point(x, y);
        }else if(event == cv::EVENT_MOUSEMOVE){
            if(m_upperLeft != cv::Point(-1,-1)){
                cv::Mat tmp;
                tmp = m_imgMouse.clone();
                cv::rectangle(tmp,cv::Rect(m_upperLeft.x, m_upperLeft.y, x-m_upperLeft.x, y-m_upperLeft.y),cv::Scalar(128,0,0));
                m_userRoi = cv::Rect(m_upperLeft.x, m_upperLeft.y, x-m_upperLeft.x, y-m_upperLeft.y);
                m_withMouse = true;
                m_lastGlintsTL = cv::Point(0,0);
                m_lastGlintsBR = cv::Point(0,0);
                cv::imshow("vdoImg", tmp);
                tmp.release();
            }
            if(m_mouseGlintsTL != cv::Point(-1,-1)){
                cv::Mat tmp;
                tmp = m_imgMouse.clone();
                m_lastGlintsBR = cv::Point(x, y);
                if(m_userRoi != cv::Rect(0,0,0,0))
                    cv::rectangle(tmp,m_userRoi,cv::Scalar(128,0,0));
                cv::rectangle(tmp,cv::Rect(m_lastGlintsTL.x, m_lastGlintsTL.y, x-m_lastGlintsTL.x, y-m_lastGlintsTL.y),cv::Scalar(255,0,255));
                //v1.0.8
                m_erode = m_initialErode;
                m_lastErode = -1;
                m_mouseR=0;
                cv::imshow("vdoImg", tmp);
                tmp.release();
            }
        }else if(event == cv::EVENT_LBUTTONUP){
            m_upperLeft = cv::Point(-1,-1);
        }else if(event == cv::EVENT_RBUTTONDOWN){
                m_mouseGlintsTL = cv::Point(x, y);
                m_lastGlintsTL = cv::Point(x, y);
        }else if(event == cv::EVENT_RBUTTONUP){
            m_mouseGlintsTL = cv::Point(-1, -1);
        }
    }
    void OTracker::onMouse( int event, int x, int y, int, void* userdata ){
        OTracker* oTracker = reinterpret_cast<OTracker*>(userdata);
            oTracker->onMouse(event, x, y);
    }
    char OTracker::drawResult(unsigned int key, cv::Mat img){
        char str[256];
        int base = 16;
        cv::Mat tmp = img.clone();
        m_imgMouse = img.clone();
        if(m_roiGlintsLarge != cv::Rect(-1,-1,-1,-1)){
            cv::rectangle(tmp,m_roiGlintsLarge,cv::Scalar(0,255,255));
            cv::putText(tmp, "roiGlintsLarge", m_roiGlintsLarge.br(), 50, 0.5, cv::Scalar(0,255,255),1,1);
        }
        cv::ellipse(tmp,m_ellipse,cv::Scalar(255,0,255));
        cv::circle(tmp,m_pupil,2,cv::Scalar(255,255,0),2);
        cross(tmp,cv::Point2f(m_pupil.x, m_pupil.y-m_ellipse.size.height/4) ,5,cv::Scalar(255,0,255));
        cross(tmp,m_leftGlint,5,cv::Scalar(0,0,255));
        cross(tmp,m_rightGlint,5,cv::Scalar(0,255,0));
        cv::rectangle(tmp,m_userRoi,cv::Scalar(0,255,0));
        cv::putText(tmp, "userRoi", m_userRoi.br(), 50, 0.5, cv::Scalar(0,255,0),1,1);  //TODODEBUG:
        cv::rectangle(tmp,cv::Rect(m_lastGlintsTL.x, m_lastGlintsTL.y, (m_lastGlintsBR.x)-(m_lastGlintsTL.x), (m_lastGlintsBR.y)-(m_lastGlintsTL.y)),cv::Scalar(0,0,128));
        cv::putText(tmp, "glintsRoi", cv::Rect(m_lastGlintsTL.x, m_lastGlintsTL.y, (m_lastGlintsBR.x)-(m_lastGlintsTL.x), (m_lastGlintsBR.y)-(m_lastGlintsTL.y)).br(), 50, 0.5, cv::Scalar(0,0,128),1,1);//TODODEBUG
        cv::rectangle(tmp,m_searchAgainRoi,cv::Scalar(255,255,255));
        //NOTE: OpenVPN 2.3.10
        //      library versions: OpenSSL 1.0.2g  1 Mar 2016, LZO 2.08
        if(m_errno == 0)
            sprintf(str,"1.0.7 : %d: (%.2lf, %.2lf) -> Startbust: %lu", m_id, m_pupil.x, m_pupil.y, m_edgePoints.size());
        else
            sprintf(str,"1.0.7 : %d: (%d, %d) -> Startbust: %lu", m_id, m_errno, m_errno, m_edgePoints.size());
        cv::putText(tmp, str, cv::Point(10,base), 50, 0.5, cv::Scalar(255,255,255),1,1);
        sprintf(str,"[n|m] blurImg: %d, [i|o] thresholdImg: %.2f", m_blurImg, m_thresholdImg);
        cv::putText(tmp, str, cv::Point(10,base+24*1), 50, 0.5, cv::Scalar(255,255,255),1,1);
        sprintf(str,"[y|u] cannyThreshold1: %d, [h|j] cannyThreshold2: %d", m_cannyThreshold1, m_cannyThreshold2);
        cv::putText(tmp, str, cv::Point(10,base+24*2), 50, 0.5, cv::Scalar(255,255,255),1,1);
        sprintf(str,"[v|b] blurRoi: %d", m_blurRoi);
        cv::putText(tmp, str, cv::Point(10,base+24*3), 50, 0.5, cv::Scalar(255,255,255),1,1);
        sprintf(str,"[k|l] thresholdGlints: %.2f", m_thresholdGlints);
        cv::putText(tmp, str, cv::Point(10,base+24*4), 50, 0.5, cv::Scalar(255,255,255),1,1);
        sprintf(str,"[q|w] glintsRoiPadding: %d", m_glintsRoiPadding);
        cv::putText(tmp, str, cv::Point(10,base+24*5), 50, 0.5, cv::Scalar(255,255,255),1,1);   //v1.0.8
        sprintf(str,"[x|c] glintsDistance: %f", m_glintsDistance);                              //v1.0.8
        cv::putText(tmp, str, cv::Point(10,base+24*6), 50, 0.5, cv::Scalar(255,255,255),1,1);
        sprintf(str,"(a: Accept)");
        cv::putText(tmp, str, cv::Point(10,base+24*7), 50, 0.5, cv::Scalar(255,255,255),1,1);
        sprintf(str,"(f: Insert -1)");
        cv::putText(tmp, str, cv::Point(10,base+24*8), 50, 0.5, cv::Scalar(255,255,255),1,1);
        sprintf(str,"(d: Defaults)");
        cv::putText(tmp, str, cv::Point(10,base+24*9), 50, 0.5, cv::Scalar(255,255,255),1,1);
        sprintf(str,"(r: Repeat)");
        cv::putText(tmp, str, cv::Point(10,base+24*10), 50, 0.5, cv::Scalar(255,255,255),1,1);
        sprintf(str,"(z: Accept fail and process next)");
        cv::putText(tmp, str, cv::Point(10,base+24*11), 50, 0.5, cv::Scalar(255,255,255),1,1);
        //v4.0.11
        if(m_inBlink){
            sprintf(str,"Blinking");
            cv::putText(tmp, str, cv::Point(240,320), 50, 2.5, cv::Scalar(255,255,255),1,8);
        }
        cv::imshow("vdoImg", tmp);
        cv::moveWindow("vdoImg", 650,200);
        cv::setMouseCallback( "vdoImg", OTracker::onMouse, this );
        return (char)cv::waitKey(key);
    }
#endif

//v1.0.12: #if OSCANN == 1
//v1.0.12:     int OTracker::measure(cv::Mat img){
//v1.0.12: #else
    int OTracker::measure(cv::Mat img, unsigned int blurAll, unsigned int blurRoi, float thresholdImg, float thresholdGlints, int glintsRoiPadding, unsigned int cannyThreshold1, unsigned int cannyThreshold2, float glintsDistance/*v1.0.8*/){
        m_blurImg = blurAll;
        m_blurRoi = blurRoi;
        m_thresholdImg = thresholdImg;
        m_thresholdGlints = thresholdGlints;
        m_glintsRoiPadding = glintsRoiPadding;
        m_cannyThreshold1 = cannyThreshold1;
        m_cannyThreshold2 = cannyThreshold2;
        //1.0.8
        m_glintsDistance = glintsDistance;
//v1.0.12: #endif

        int result = 0;
        try{
            m_pupil.x = -1;
            m_pupil.y = -1;
            m_vdoImg = img.clone();
            result = find();
        }
        catch(cv::Exception& e){
            const char* err_msg = e.what();
            std::cout << "OTracker::measure(cv::Mat img) -> exception caught: " << err_msg << std::endl;
            //1.0.8: std::string str("OTracker::measure(cv::Mat img) -> exception caught: " + *err_msg);
            //1.0.8 Logger::instance().log( str, Logger::kLogLevelError);
            return -1;
        }
        return result;
    }
template<typename T>
ConicSection_<T>::ConicSection_(cv::RotatedRect r){
    cv::Point_<T> axis((T)std::cos(CV_PI/180.0 * r.angle), (T)std::sin(CV_PI/180.0 * r.angle));
    cv::Point_<T> centre(r.center);
    T a = r.size.width/2;
    T b = r.size.height/2;
    initFromEllipse(axis, centre, a, b);
}
template<typename T>
T ConicSection_<T>::algebraicDistance(cv::Point_<T> p){
    return A*p.x*p.x + B*p.x*p.y + C*p.y*p.y + D*p.x + E*p.y + F;
}
template<typename T>
cv::Point_<T> ConicSection_<T>::algebraicGradient(cv::Point_<T> p){
    return cv::Point_<T>(2*A*p.x + B*p.y + D, B*p.x + 2*C*p.y + E);
}
template<typename T>
T ConicSection_<T>::distance(cv::Point_<T> p){
    //    dist
    // -----------
    // |grad|^0.45
    T dist = algebraicDistance(p);
    cv::Point_<T> grad = algebraicGradient(p);
    T sqgrad = grad.dot(grad);
    return dist / std::pow(sqgrad, T(0.45/2));
}
template<typename T>
cv::Point_<T> ConicSection_<T>::algebraicGradientDir(cv::Point_<T> p){
    cv::Point_<T> grad = algebraicGradient(p);
    T len = std::sqrt(grad.ddot(grad));
    grad.x /= len;
    grad.y /= len;
    return grad;
}
template<typename T>
void ConicSection_<T>::initFromEllipse(cv::Point_<T> axis, cv::Point_<T> centre, T a, T b){
    T a2 = a * a;
    T b2 = b * b;

    A = axis.x*axis.x / a2 + axis.y*axis.y / b2;
    B = 2*axis.x*axis.y / a2 - 2*axis.x*axis.y / b2;
    C = axis.y*axis.y / a2 + axis.x*axis.x / b2;
    D = (-2*axis.x*axis.y*centre.y - 2*axis.x*axis.x*centre.x) / a2
        + (2*axis.x*axis.y*centre.y - 2*axis.y*axis.y*centre.x) / b2;
    E = (-2*axis.x*axis.y*centre.x - 2*axis.y*axis.y*centre.y) / a2
        + (2*axis.x*axis.y*centre.x - 2*axis.x*axis.x*centre.y) / b2;
    F = (2*axis.x*axis.y*centre.x*centre.y + axis.x*axis.x*centre.x*centre.x + axis.y*axis.y*centre.y*centre.y) / a2
        + (-2*axis.x*axis.y*centre.x*centre.y + axis.y*axis.y*centre.x*centre.x + axis.x*axis.x*centre.y*centre.y) / b2
        - 1;
}
static std::mt19937 static_gen;
int OTracker::random(int min, int max){
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(static_gen);
}
int OTracker::random(int min, int max, unsigned int seed){
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(gen);
}
template<typename T>
std::vector<T> OTracker::randomSubset(const std::vector<T>& src, typename std::vector<T>::size_type size){
    if (size > src.size())
        throw std::range_error("Subset size out of range");

    std::vector<T> ret;
    std::set<size_t> vals;

    for (size_t j = src.size() - size; j < src.size(); ++j)
    {
        size_t idx = random(0, j); // generate a random integer in range [0, j]

        if (vals.find(idx) != vals.end())
            idx = j;

        ret.push_back(src[idx]);
        vals.insert(idx);
    }

    return ret;
}
template<typename T>
std::vector<T> OTracker::randomSubset(const std::vector<T>& src, typename std::vector<T>::size_type size, unsigned int seed){
    if (size > src.size())
        throw std::range_error("Subset size out of range");

    std::vector<T> ret;
    std::set<size_t> vals;

    for (size_t j = src.size() - size; j < src.size(); ++j)
    {
        size_t idx = random(0, j, seed+j); // generate a random integer in range [0, j]

        if (vals.find(idx) != vals.end())
            idx = j;

        ret.push_back(src[idx]);
        vals.insert(idx);
    }

    return ret;
}
template<typename T>
T OTracker::sq(T n){
    return n * n;
}
cv::Scalar OTracker::rgb(double r, double g, double b, double a){
    return cv::Scalar(b,g,r,a);
}
template<typename T>
cv::Rect_<T> OTracker::roiAround(const cv::Point_<T>& centre, T radius){
    return cv::Rect_<T>(centre.x - radius, centre.y - radius, 2*radius + 1, 2*radius + 1);
}
void OTracker::cross(cv::Mat& img, cv::Point2f centre, double radius, const cv::Scalar& colour, int thickness, int lineType, int shift){
    line(img, centre + cv::Point2f(-radius, -radius), centre + cv::Point2f(radius, radius), colour, thickness, lineType, shift);
    line(img, centre + cv::Point2f(-radius, radius), centre + cv::Point2f(radius, -radius), colour, thickness, lineType, shift);
}
cv::Mat& OTracker::line(cv::Mat& dst, cv::Point2f from, cv::Point2f to, cv::Scalar color, int thickness, int linetype, int shift) {
    try{
        auto from_i = cv::Point(from.x * (1<<shift), from.y * (1<<shift));
        auto to_i = cv::Point(to.x * (1<<shift), to.y * (1<<shift));
        cv::line(dst, from_i, to_i, color, thickness, linetype, shift);
    }catch(cv::Exception& e){
        const char* err_msg = e.what();
        printf("exception caught: %s\n", err_msg);
    }
    return dst;
}
cv::Rect OTracker::boundingBox(const cv::Mat& img){
    return cv::Rect(0,0,img.cols,img.rows);
}
void OTracker::getROI(const cv::Mat& src, cv::Mat& dst, const cv::Rect& roi, int borderType){
    cv::Rect bbSrc = boundingBox(src);
    cv::Rect validROI = roi & bbSrc;
    if (validROI == roi){
        dst = cv::Mat(src, validROI);
    }
    else{
        // Figure out how much to add on for top, left, right and bottom
        cv::Point tl = roi.tl() - bbSrc.tl();
        cv::Point br = roi.br() - bbSrc.br();
        int top = std::max(-tl.y, 0);  // Top and left are negated because adding a border
        int left = std::max(-tl.x, 0); // goes "the wrong way"
        int right = std::max(br.x, 0);
        int bottom = std::max(br.y, 0);
        cv::Mat tmp(src, validROI);
        cv::copyMakeBorder(tmp, dst, top, bottom, left, right, borderType);
    }
}
void OTracker::greyAndCrop(){
    // Pick one channel if necessary, and crop it to get rid of borders
    if (m_vdoImg.channels() == 3){
        cv::cvtColor(m_vdoImg, m_vdoImg, cv::COLOR_BGR2GRAY);
    }
    else if (m_vdoImg.channels() == 4){
        cv::cvtColor(m_vdoImg, m_vdoImg, cv::COLOR_BGRA2GRAY);
    }
    if(m_userRoi == cv::Rect(0,0,0,0)){
        if(m_searchAgainRoi == cv::Rect(0,0,0,0)){
            m_eye = m_vdoImg;
        }else{
            getROI(m_vdoImg, m_eye, m_searchAgainRoi, cv::BORDER_REPLICATE);
        }

    }else{
        getROI(m_vdoImg, m_eye, m_userRoi, cv::BORDER_REPLICATE);
    }
    cv::GaussianBlur(m_eye, m_eye,cv::Size(3,3),0);
    cv::resize(m_eye,m_eyeSmall,cv::Size(m_eye.cols/4,m_eye.rows/4),0,0,cv::INTER_NEAREST);
    m_eyeFocus = m_eye.clone();
}


cv::Rect OTracker::roiFromRectangle(cv::Rect rectangle, int maxWidth, int maxHeight){
    if(rectangle.x < 0)
        rectangle.x = 0;
    if(rectangle.y < 0)
        rectangle.y = 0;
    if((rectangle.width + rectangle.x) > maxWidth)
        rectangle.width -= ((rectangle.width + rectangle.x) - maxWidth);
    if((rectangle.height + rectangle.y) > maxHeight)
        rectangle.height -= ((rectangle.height + rectangle.y) - maxHeight);
    return rectangle;
}


void OTracker::thresholding(){
    cv::Mat_<uchar> mEyeThresh;
    cv::Mat mPreThres;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat element;
    cv::medianBlur(m_eyeSmall,mPreThres,m_blurImg); //Como nos interesa solo saber aprox donde esta la pupila podemos hacer un filtrado muy agresivo
    //TODOCOMPARE: cv::GaussianBlur(m_eyeSmall,mPreThres,cv::Size(17,17),0.0, 0.0);   //0.0+++++, 1.0---, 2.0----
    #if OSCANN == 0  //v1.0.6: New
        cv::imshow("mPreThres", mPreThres);                                     //TODODEBUG:
        cv::moveWindow("mPreThres", 100, 200);                                  //TODODEBUG:
    #endif
    cv::threshold(mPreThres,mEyeThresh,255*m_thresholdImg,255,cv::THRESH_BINARY_INV);
    element = cv::getStructuringElement(2,cv::Size(3,3));
    cv::morphologyEx(mEyeThresh,m_morphImg,cv::MORPH_OPEN,element); //Tambien, opening agresivo, elimina pequeñas areas detectadas por el threshold
    cv::morphologyEx(m_morphImg,m_morphImg,cv::MORPH_CLOSE,element); //Closing agresivo, trata de cerrar los circulos negros (Como los que producen los glints en la pupial)
    #if OSCANN == 0  //v1.0.6: New
        cv::imshow("m_morphImg", m_morphImg);                                   //TODODEBUG:
        cv::moveWindow("m_morphImg", 100, 400);                                 //TODODEBUG:
    #endif
    // --------------------------------------------------
    // Try to find pupil region by threshold only
    // --------------------------------------------------
    m_haarRadius=-1;
    //https://riptutorial.com/opencv/example/22518/circular-blob-detection
    //Aqui somos estrictos, si encontramos un blob del tamaño adecuado y muy circular nos saltamos el haar (Que es uno de los puntos lentos del algoritmo)
    cv::findContours(m_morphImg.clone(),contours,hierarchy,cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    m_found=false;
    if(contours.size() > 0){
        float areaMax=900,circMax=1, circularity;
        double scoreCirc, score, scoreArea, area, maxScore=0;
        for(unsigned int i=0;i<contours.size();i++){
            area=cv::contourArea(contours[i]);
            if(area<1000&&area>150){ //FIXED VALUES
                scoreArea=area/areaMax; //Normalizar area
                if(scoreArea>1) scoreArea=1; //Este limite es importante para que un area muy grande no tenga ventaja
                //v1.0.10:circularity=(4*PI*area)/pow(arcLength(contours[i],true),2);
                double arclength = arcLength(contours[i],true);
                circularity=4*CV_PI*area/(arclength*arclength);
                if(circularity>0.80){
                    scoreCirc=circularity/circMax; //Normalizar circularidad
                    if(scoreCirc>1) scoreCirc=1;
                    score=scoreCirc+scoreArea;
                    if (score > maxScore){ //Si tiene una puntacion mayor guardar
                        maxScore=score;
                        m_bestContour = contours[i];
                        if(m_found==false){
                            m_found=true;
                        }
                    }
                }
            }
        }
    }
    mPreThres.release();
    element.release();
}
int OTracker::pupilRegion(){
    cv::Rect bbPupilThresh;
    int incX=0,incY=0;
    thresholding();                                                             //~880 microseconds, 28 std
    if(!m_found){
        // --------------------------------------------------
        // find pupil region using Haarcascade
        // -------------------------------------------------
        // Find best haar response
        // -----------------------
        //             _____________________
        //            |         Haar kernel |
        //            |                     |
        //  __________|______________       |
        // | Image    |      |       |      |
        // |    ______|______|___.-r-|--2r--|
        // |   |      |      |___|___|      |
        // |   |      |          |   |      |
        // |   |      |          |   |      |
        // |   |      |__________|___|______|
        // |   |    Search       |   |
        // |   |    region       |   |
        // |   |                 |   |
        // |   |_________________|   |
        // |                         |
        // |_________________________|
        //
        cv::Mat_<int32_t> mEyeIntegral;
        int padding = 2*params.Radius_Max; //TODO: Automatic radius(?)
        if(padding>200)
            padding=200;
        cv::Mat mEyePad;
        // Need to pad by an additional 1 to get bottom & right edges.
        cv::copyMakeBorder(m_eyeSmall, mEyePad, padding, padding, padding, padding, cv::BORDER_REPLICATE);
        //INFO integral: http://es.mathworks.com/help/vision/ref/integralimage.html?s_tid=gn_loc_drop
        cv::integral(mEyePad, mEyeIntegral);
        mEyePad.release();
        cv::Point2f pHaarPupil;
        const int rstep = 2;
        const int ystep = 4;
        const int xstep = 4;
        double minResponse = std::numeric_limits<double>::infinity();
        for (int r = params.Radius_Min; r < params.Radius_Max; r+=rstep){ //[3, 5, 7 ...32]
            // Get Haar feature
            int r_inner = r;
            int r_outer = 3*r;
            HaarSurroundFeature f(r_inner, r_outer);
            // Use TBB for rows
            std::pair<double,cv::Point2f> minRadiusResponse = tbb::parallel_reduce(
                            tbb::blocked_range<int>(0, (m_eyeSmall.rows-r - r - 1)/ystep + 1, ((m_eyeSmall.rows-r - r - 1)/ystep + 1) / 8),                 //const Range& range
                            std::make_pair(std::numeric_limits<double>::infinity(), UNKNOWN_POSITION),                                          //const Value& identity
                            [&] (tbb::blocked_range<int> range, const std::pair<double,cv::Point2f>& minValIn) -> std::pair<double,cv::Point2f>
            {
                std::pair<double,cv::Point2f> minValOut = minValIn;

                for (int i = range.begin(), y = r + range.begin()*ystep; i < range.end(); i++, y += ystep){
                        //
                        // row1_outer.|         |  p00._____________________.p01
                        //            |         |     |         Haar kernel |
                        //            |         |     |                     |
                        // row1_inner.|         |     |   p00._______.p01   |
                        //            |-padding-|     |      |       |      |
                        //            |         |     |      | (x,y) |      |
                        // row2_inner.|         |     |      |_______|      |
                        //            |         |     |   p10'       'p11   |
                        //            |         |     |                     |
                        // row2_outer.|         |     |_____________________|
                        //            |         |  p10'                     'p11
                        //
                        //padding: 64
                        //r_inner: [3, 5, 7 ...32]
                    int* row1_inner = mEyeIntegral[y+padding - r_inner];
                    int* row2_inner = mEyeIntegral[y+padding + r_inner + 1];
                    int* row1_outer = mEyeIntegral[y+padding - r_outer];
                    int* row2_outer = mEyeIntegral[y+padding + r_outer + 1];
                    //r: [3, 5, 7 ...32]
                    int* p00_inner = row1_inner + r + padding - r_inner;
                    int* p01_inner = row1_inner + r + padding + r_inner + 1;
                    int* p10_inner = row2_inner + r + padding - r_inner;
                    int* p11_inner = row2_inner + r + padding + r_inner + 1;
                    int* p00_outer = row1_outer + r + padding - r_outer;
                    int* p01_outer = row1_outer + r + padding + r_outer + 1;
                    int* p10_outer = row2_outer + r + padding - r_outer;
                    int* p11_outer = row2_outer + r + padding + r_outer + 1;
                    for (int x = r; x < m_eyeSmall.cols - r; x+=xstep){
                        int sumInner = *p00_inner + *p11_inner - *p01_inner - *p10_inner;
                        int sumOuter = *p00_outer + *p11_outer - *p01_outer - *p10_outer - sumInner;
                        double response = f.val_inner * sumInner + f.val_outer * sumOuter;
                        if (response < minValOut.first){
                            minValOut.first = response;
                            minValOut.second = cv::Point(x,y);
                        }
                        p00_inner += xstep;
                        p01_inner += xstep;
                        p10_inner += xstep;
                        p11_inner += xstep;

                        p00_outer += xstep;
                        p01_outer += xstep;
                        p10_outer += xstep;
                        p11_outer += xstep;
                    }
                }
                return minValOut;
            },
            [] (const std::pair<double,cv::Point2f>& x, const std::pair<double,cv::Point2f>& y) -> std::pair<double,cv::Point2f>
            {
                if (x.first < y.first)
                    return x;
                else
                return y;
            }
            );
            if (minRadiusResponse.first < minResponse){
                minResponse = minRadiusResponse.first;
                // Set return values
                pHaarPupil = minRadiusResponse.second;
                m_haarRadius = r;
            }
        }
        m_haarRadius = (int)(m_haarRadius * std::sqrt(2.0)*1.5);
        cv::Rect roiHaarPupil = roiAround(cv::Point(pHaarPupil.x, pHaarPupil.y), m_haarRadius);
        cv::Mat_<uchar> morphImgHaar;
        getROI(m_morphImg,morphImgHaar,roiHaarPupil);
        m_morphImg.release();
        // ---------------------------------------------
        // Find best region in the segmented pupil image
        // ---------------------------------------------
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(morphImgHaar.clone(),          //Source, an 8-bit single-channel image
                         contours,                      //Detected contours.
                         hierarchy,
                         cv::RETR_LIST,                 //retrieves only the extreme outer contours. cv::RETR_EXTERNAL
                         cv::CHAIN_APPROX_NONE          //stores absolutely all the contour points.
                         );
        if (contours.size() == 0){
            m_errorMsg = "ERROR 01: pupilRegion - No contours found";
            return m_errno = -1;
        }
        m_bestContour = contours[0];
        if(contours.size()>1){
            double maxScore=0;
            float areaMax=7000/8,circMax=0.9; //Se usan para normalizar los valores de area y circularidad FIXED VALUES (Eso lo pongo para poder luego buscar por el codigo que está fijo)
            BOOST_FOREACH(std::vector<cv::Point>& c, contours){
                double area = cv::contourArea(c);
                float circularity=(4*PI*area)/(arcLength(c,true)*arcLength(c,true));
                double scoreArea=area/areaMax; //Normalizar area
                if(scoreArea>1){
                    scoreArea=1; //Este limite es importante para que un area muy grande no tenga ventaja
                }
                double scoreCirc=circularity/circMax; //Normalizar circularidad
                if(scoreCirc>1){
                    scoreCirc=1;
                }
                double score=scoreCirc+scoreArea;
                if (score > maxScore) //Si tiene una puntacion mayor guardar
                {
                    maxScore=score;
                    m_bestContour = c;
                }
            }
        }
        incX=roiHaarPupil.x;
        incY=roiHaarPupil.y;
        if(m_bestContour.size()<5){
            m_errorMsg = "ERROR 02: pupilRegion - There are contours but they are not appropiate";
            return m_errno = -2;
        }
    }
    m_elPupilThresh = cv::fitEllipse(cv::Mat(m_bestContour));
    bbPupilThresh = cv::boundingRect(m_bestContour);       //boundingRect: Calculates the up-right bounding rectangle of a point set.
    // Shift best region into eye coords (instead of pupil region coords), and get ROI
    bbPupilThresh.x += incX;
    bbPupilThresh.y += incY;
    m_elPupilThresh.center.x += incX;
    m_elPupilThresh.center.y += incY;
    if(m_haarRadius>0){
        m_roiPupil = roiAround(cv::Point(m_elPupilThresh.center.x, m_elPupilThresh.center.y), m_haarRadius); //Se ha usado Haar
        m_haarRadius = -1;
    }else{
        //No se ha usado Haar, tomar como radio el bounding box mayorado
        int radius=bbPupilThresh.width;
        if(bbPupilThresh.height>radius) radius=bbPupilThresh.height;
        radius=(radius/2)*1.75; //Radio es la mitad del ancho o alto
        m_roiPupil = roiAround(cv::Point(m_elPupilThresh.center.x, m_elPupilThresh.center.y), radius);
    }
    if(m_roiPupil.width<=25){
        m_roiPupil.width=25;
        int cx = m_elPupilThresh.center.x-12.5;
        if(cx<0) cx=0;
        m_roiPupil.x=cx;
    }
    if(m_roiPupil.height<=25){
        m_roiPupil.height=25;
        int cy = m_elPupilThresh.center.y-12.5;
        if(cy<0) cy=0;
        m_roiPupil.y=cy;
    }
    //Aumentar el roi y elipse calculados convenientemente
    m_roiPupil.x=m_roiPupil.x*4;
    m_roiPupil.y=m_roiPupil.y*4;
    m_roiPupil.width=m_roiPupil.width*4;
    m_roiPupil.height=m_roiPupil.height*4;
    m_elPupilThresh.center.x=m_elPupilThresh.center.x*4;
    m_elPupilThresh.center.y=m_elPupilThresh.center.y*4;
    m_elPupilThresh.size.width*=4;
    m_elPupilThresh.size.height*=4;
    m_roiPadded = roiFromRectangle(cv::Rect(m_roiPupil.x-m_paddingValue,
                           m_roiPupil.y-m_paddingValue,
                           m_roiPupil.width+2*m_paddingValue,
                           m_roiPupil.height+2*m_paddingValue));
    m_eyeSmall.release();
    return 0;
}
// ---------------------------------
// Find blobs most similar to glints
// ---------------------------------
//v1.0.9: std::vector<std::vector<cv::Point> > OTracker::getValidContours(std::vector<std::vector<cv::Point> > contours){
std::vector<std::vector<cv::Point> > OTracker::getValidContours(std::vector<std::vector<cv::Point> > contours, bool restrictX){
    std::vector<double> areas;
    std::vector<double> ys;
    //v1.0.9
    std::vector<double> xs;
    double area;
    std::vector<std::vector<cv::Point> > contourAreas;
    std::vector<std::vector<cv::Point> > theTwo;

    cv::Moments M;
    cv::Point2f centroide;

    bool leftDefined = false;
    bool rightDefined = false;
    float padding = 5.0;
    for(unsigned int i = 0; i< contours.size(); i++ ){
        /* IMPORTANT NOTE: Big contour areas are discarted. However, the two glints can produce one of these areas.
         * Specially in blured images (bad focus).
         * 128,140 -> Problem with AURA84/CC9-02262018-094420
         * 155 -> Problem with AURA84/TSLLH-02262018-094452 -> frame 29 -> size 166
         * 170 -> Problem with AURA84/TSLLH-02262018-094452
         * 175 -> Problem with AURA101/TFIX-06152018-092905 VERY BAD QUALITY
         * 260 -> Problem with AURA106/CC9-07032018-095102  VERY BAD QUALITY
         * 300 -> Problem with AURA106/TSLSH-07032018-095310  PARA MATARLA*/
        area = cv::contourArea(contours[i]);
        if(area>0.2 && area<300){
        //if(area>3.0 && area<300){
            M = cv::moments(contours[i]);
            centroide=cv::Point2f(M.m10/M.m00,M.m01/M.m00);
            if(m_lastLeftGlint != cv::Point2f(0.0,0.0) && m_lastRightGlint != cv::Point2f(0.0,0.0)){
                if((centroide.x > (m_lastLeftGlint.x-padding) && centroide.x < (m_lastLeftGlint.x+padding)
                        && centroide.y > (m_lastLeftGlint.y-padding) && centroide.y < (m_lastLeftGlint.y+padding)) && !leftDefined){
                    leftDefined = true;
                    theTwo.push_back(contours[i]);
                }else if((centroide.x > (m_lastRightGlint.x-padding) && centroide.x < (m_lastRightGlint.x+padding)
                         && centroide.y > (m_lastRightGlint.y-padding) && centroide.y < (m_lastRightGlint.y+padding)) && !rightDefined){
                    rightDefined = true;
                    theTwo.push_back(contours[i]);
                }
            }
            areas.push_back(area);
            contourAreas.push_back(contours[i]);
            ys.push_back(centroide.y);
            //v1.0.9
            xs.push_back(centroide.x);
            m_possibleGlints.push_back(contours[i]);
        }
    }
    if(leftDefined && rightDefined)
        return theTwo;
    /*CASE: Two areas. This case is important because if two areas are found, the process stops. Hewever, in this case it is an error
        Similar size: Two glint
        One big (Glued glints) and another small (noise):*/
    /*INTRAOCULAR
     * CASE A (three glints):

                   *(intra)

               *(g1)  *(g2)

       CASE B (four glints):

            *(intra)  *(intra)

              *(g1)  *(g2)*/
    if(ys.size() > 2){
        bool similarY;
        for(unsigned int i=0;i<ys.size();i++){
            similarY = false;
            for(unsigned int j=0;j<ys.size();j++){
                if(i!=j)
                    if(ys[i] < ys[j]+5.0 && ys[i] > ys[j]-5.0){
                        similarY = true;
                        break;
                    }
            }
            if(!similarY){
                contourAreas.erase(contourAreas.begin()+i);
                areas.erase(areas.begin()+i);
                ys.erase(ys.begin()+i);
                //v1.0.9
                xs.erase(xs.begin()+i);
            }
        }
    }
    //v1.0.9: New if statement
    if(restrictX && xs.size() == 2){
        float xd = xs[0] > xs[1] ? xs[0] - xs[1] : xs[1] - xs[0];
        //v1.0.9 H12O -> Controls -> GroupA -> PNC-77362557X -> CC9-05222018-102913 : From 32.0 to 40.0
        //v1.0.13 (New distance for H12O -> Esclerosis -> MCD-50090439G -> CC9-03022018-134726): if(xd > 40.0){
        //v1.0.13 (New distance for H12O -> Esclerosis -> MCD-50090439G -> CC9-03022018-134936): if(xd > 45.0){
        if(xd > 55.0){
            //NOTE: Case Santander -> DFT -> 1050 -> CC9-04182018-125459 -> Frame 44
            //The distance between these glints (two) is big
            //The bigger glint is formed by the two glints and the other glint represents noise
            //In this case, the bigget glints must be ??? for further procces steps
            areas[0] > areas[1] ? contourAreas.erase(contourAreas.begin()+1) : contourAreas.erase(contourAreas.begin());
        }
    }
    if(areas.size() == 2){
        if(areas[0]>areas[1]){
           if(areas[0]-areas[1] > 64)
               contourAreas.erase(contourAreas.begin()+1);
        }else{
            if(areas[1]-areas[0] > 64)
                contourAreas.erase(contourAreas.begin());
        }
    }
    return contourAreas;
}


int OTracker::glintsDetection(){
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat mThresGlints, imgErode;
    cv::Mat element;
    std::vector<std::vector<cv::Point> > validContours;
    //v1.0.8: L1080 bool restore = false;
    int lastValidAreas=-1;
    m_contoursGlintsPos.clear(); //Vectores de contornos y centroides de glints posibles
    m_glintsRect.clear();
    m_glintsCentroides.clear();
    m_glintsContours.clear();
    m_possibleGlints.clear();
    /*        Eye         m_bestcontour   m_elPupilThres    bbPupilTresh
     *  --------------   --------------   --------------   --------------   --------------
     *       ,-""-.
     *      / ,--. \                                              ___
     *     | ( () ) |            o               O               |   |
     *      \ `--' /                                              ---
     *       `-..-'
     *   --------------  --------------   --------------   --------------   --------------
    */
    double w;
    double h;
    if(m_lastGlintsTL == cv::Point(0,0) && m_lastGlintsBR == cv::Point(0,0)){
        //120 -> 120/100: 1.2, 120/10: 12, 132-120: 12/100: 0.12, 132-131:1/100:0.01
        //60 ->   60/100   0.6, 60/10: 6 , 132-60:  72/100: 0.72, 132-30:102/100:1.02
        //1.5 to 2.15  H12O/epilepsia/4608696/CC9-05122017-103256
        //v1.0.9: From 2.15 to 4.0 for Santander -> DFT -> CC9-04182018-125852
        if(m_elPupilThresh.size.width < 132.0 && m_elPupilThresh.size.width > 25.0)
            //NORMAL: 2.15
            //v1.0.9: w =m_elPupilThresh.size.width*(((132-m_elPupilThresh.size.width)/100)+2.15);
            //Santander -> DFT -> 01046 -> CC9-03232018-130106 : from 4750 to 6750
            w =m_elPupilThresh.size.width + (6750*(1/m_elPupilThresh.size.width));
        else
            w = 132;

        if(m_elPupilThresh.size.height < 132.0 && m_elPupilThresh.size.width > 25.0)
            //NORMAL: 1.15
            //¿1.15 to 1.0?  H12O -> epilepsia -> 4608696 -> CC9-05122017-103256
            //v1.0.9: From 1.15 to 1.5 for Santander -> DFT -> CC9-04182018-125852
            //v1.0.9: h = m_elPupilThresh.size.height*(((132-m_elPupilThresh.size.height)/100)+1.15);
            h = m_elPupilThresh.size.height+(2500*(1/m_elPupilThresh.size.height));
        else
            h = 132;
        m_roiGlintsLarge = cv::Rect(roiFromRectangle(cv::Rect(m_elPupilThresh.center.x - (w/2),m_elPupilThresh.center.y - 32.0,w,h)));
        if(m_userRoi != cv::Rect(0,0,0,0))
            getROI(m_vdoImg, m_PupilLarge, roiFromRectangle(cv::Rect(m_roiGlintsLarge.x+m_userRoi.x,m_roiGlintsLarge.y+m_userRoi.y,m_roiGlintsLarge.width,m_roiGlintsLarge.height),m_vdoImg.cols, m_vdoImg.rows) , cv::BORDER_REPLICATE);
        else
            getROI(m_vdoImg, m_PupilLarge, roiFromRectangle(cv::Rect(m_roiGlintsLarge.x+m_searchAgainRoi.x,m_roiGlintsLarge.y+m_searchAgainRoi.y,m_roiGlintsLarge.width,m_roiGlintsLarge.height),m_vdoImg.cols, m_vdoImg.rows) , cv::BORDER_REPLICATE);
    }else{
        m_roiGlintsLarge = cv::Rect(-1,-1,-1,-1);
        if(m_lastGlintsBR.x > m_lastGlintsTL.x)
            w = (m_lastGlintsBR.x)-(m_lastGlintsTL.x);
        else
            w = (m_lastGlintsTL.x)-(m_lastGlintsBR.x);
        if((m_lastGlintsBR.y) > (m_lastGlintsTL.y))
            h = (m_lastGlintsBR.y)-(m_lastGlintsTL.y);
        else
            h = (m_lastGlintsTL.y)-(m_lastGlintsBR.y);
        getROI(m_vdoImg, m_PupilLarge, cv::Rect(m_lastGlintsTL.x, m_lastGlintsTL.y, w, h), cv::BORDER_REPLICATE);
    }
    if(m_PupilLarge.size() == cv::Size(0,0)){
        m_errorMsg = "ERROR 03: Glints not deteced - ROI definition failed";
        return m_errno = -3;
    }
    cv::threshold(m_PupilLarge,mThresGlints,255*m_thresholdGlints,255,cv::THRESH_BINARY);
    cv::findContours(mThresGlints.clone(),contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
    validContours = getValidContours(contours);
    if(validContours.size() != 2){
        /*v1.0.8: if(m_lastErode > 0){
            m_erode = m_lastErode;
            element = cv::getStructuringElement(cv::MORPH_CROSS,cv::Size(m_erode,m_erode));
            cv::erode( mThresGlints.clone(), imgErode, element );
            cv::findContours(imgErode.clone(),contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
            validContours = getValidContours(contours);
        }*/
        if(m_lastErode > 0)         //else, m_erode has an initial value. This is for the first frame
            m_erode = m_lastErode;
        element = cv::getStructuringElement(cv::MORPH_CROSS,cv::Size(m_erode,m_erode));
        cv::erode( mThresGlints.clone(), imgErode, element );
        cv::findContours(imgErode.clone(),contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
        validContours = getValidContours(contours);
        if(validContours.size() != 2){
            bool restore = false;   //v1.0.8 L1080 moved here
            m_erode = 0;
            bool cont = true;
            lastValidAreas = -1;
            do{
                m_erode++;
                /*IMPORTANT NOTE: cv::MORPH_CROSS works perfectly with very bad images (AURA79/TSVV-01152018-095025)
                and normal images as well. Maybe, it is better than cv::MORPH_RECT*/
                element = cv::getStructuringElement(cv::MORPH_CROSS,cv::Size(m_erode,m_erode));
                cv::erode( mThresGlints.clone(), imgErode, element );
                cv::findContours(imgErode.clone(),contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
                validContours = getValidContours(contours);
                if(validContours.size() == 2){ //Case 1: There are two posible glints
                    cont = false;
                }else if(validContours.size() == 1){      // There is one point or the two glints are too close
                    //Can be obtained: A) Two points or B) Zero
                    if(lastValidAreas > 3){     //0: 3,4,5,...,n
                        restore = true;
                        cont = false;
                   }
                }else if(validContours.size() == 0){
                    if(lastValidAreas > 2)     //0: 3,4,5,...,n
                        restore = true;
                    cont = false;
                }
                if(m_erode > 20)
                    cont = false;
                lastValidAreas = validContours.size();
            }while(cont);
            //v1.0.8 B1080 moved to
            if(restore){
                m_erode++;
                element = cv::getStructuringElement(cv::MORPH_ELLIPSE,cv::Size(m_erode,m_erode));
                //v1.0.9: cv::erode( mThresGlints, imgErode, element );
                cv::erode( mThresGlints.clone(), imgErode, element );
                cv::findContours(imgErode.clone(),contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
                validContours = getValidContours(contours);
            }
        }
        //v1.0.8 B1080 moved from
        m_lastErode = m_erode;
#if OSCANN == 0  //v1.0.6: New
        if(imgErode.size() != cv::Size(0,0) ){
            cv::imshow("imgErode", imgErode);       //TODODEBUG
            cv::moveWindow("imgErode", 350, 350);   //TODODEBUG
        }
#endif
    }
    //BLOCKCODE(000)
    /*This block code was programmed to be used with VERY bad quality images.
     * It must not be used in normal state
     * Here, the quality of the image is extremely bad. In such a case, the two glints form a big area because both are too close.
     * In this situation, such area is split vertically from the middle
     *
     *    One Area
     *    *******        *** ***
     *   *********      **** ****
     *   *********  ->  **** ****
     *   *********      **** ****
     *    *******        *** ***
    */
    if(validContours.size() != 2){
        cv::findContours(mThresGlints.clone(),contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
        if(contours.size() != 1){
            float tmp = 0.95;
            do{
                cv::threshold(m_PupilLarge,mThresGlints,255*tmp,255,cv::THRESH_BINARY);
                cv::findContours(mThresGlints.clone(),contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
                tmp-=0.01;
                //v1.0.13: if(contours.size() == 1)
                if(contours.size() == 1 || contours.size() == 2)
                    break;
            }while(tmp>0.3);
        }
        //v4.0.11: if(contours.size() == 1 ){
        if(contours.size() == 1 && m_isCalibration ){
            cv::Moments M = cv::moments(contours[0]);
            cv::Point2f centroide=cv::Point2f(M.m10/M.m00,M.m01/M.m00);
            cv::rectangle(mThresGlints, cv::Rect(centroide.x, 0, 1, mThresGlints.rows), cv::Scalar(0,0,0), cv::FILLED);
            element = cv::getStructuringElement(cv::MORPH_CROSS,cv::Size(4,4));
            //v1.0.9: cv::erode( mThresGlints.clone(), imgErode, element );
            //v1.0.9: cv::findContours(imgErode.clone(),contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
            //COMMENT: At this point, there exist only one contour. Thus, it does not make sense to make an erode operation...
            cv::findContours(mThresGlints.clone(),contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_NONE);
            //COMMENT: These areas are too close. Thus, it is not necessary to check the distance between them
            //v1.0.9: validContours = getValidContours(contours);
            validContours = getValidContours(contours, false);
        }else if(contours.size() == 2){ //v1.0.13
            validContours = getValidContours(contours);
        }
    }
    m_PupilLarge.release();
    //BLOCKCODE(000)
    cv::Moments M;
    cv::Point2f cnt;
#if OSCANN == 0  //v1.0.6: New
    if(mThresGlints.size() != cv::Size(0,0) ){
        cv::imshow("mThresGlints", mThresGlints);           //TODODEBUG:
        cv::moveWindow("mThresGlints", 350, 200);           //TODODEBUG:
    }
#endif
    mThresGlints.release();
    if(validContours.size() == 2){
        for(unsigned int i = 0; i< validContours.size(); i++ ){
            M = cv::moments(validContours[i]);
            cnt=cv::Point2f(M.m10/M.m00,M.m01/M.m00);
            m_glintsContours.push_back(validContours[i]);
            m_glintsCentroides.push_back(cnt);
        }
    }else{
        //v1.0.8
        m_erode = m_initialErode;
        //v1.0.8
        m_lastErode = -1;
        m_errorMsg = "ERROR 03: Glints not deteced";
        return m_errno = -3;
    }
    cv::Mat mPupil;
    cv::Rect r;
    if(m_userRoi == cv::Rect(0,0,0,0))
        getROI(m_eye, mPupil, m_roiPadded, cv::BORDER_REPLICATE);
    else
        mPupil = m_eye.clone();
    m_glintPaired.clear();
    for(unsigned int i=0;i<m_possibleGlints.size();i++){
        m_glintPaired.push_back(false);
        r = cv::boundingRect(m_possibleGlints[i]);
        //NOTA: Glints are detected in m_PupilLarge which is based on m_roiGlintsLarge.
        //      However, they are used in mPupil which is based on m_roiPadded
        //      Therefore, it is neccesary to move the rect of each glint (m_roiGlintsLarge.x-m_roiPadded.x), (m_roiGlintsLarge.y-m_roiPadded.y)
        //      6, 12 are the zoom of each rectangle
        if(m_lastGlintsTL == cv::Point(0,0) && m_lastGlintsBR == cv::Point(0,0)){
            m_glintsRect.push_back(cv::Rect(r.x+(m_roiGlintsLarge.x-m_roiPupil.x)-m_glintPadding,r.y+(m_roiGlintsLarge.y-m_roiPupil.y)-m_glintPadding,r.width+m_glintPadding*2,r.height+m_glintPadding*2) );
        }else{
            //NORMAL:
                    m_glintsRect.push_back(cv::Rect(r.x-m_glintPadding+(m_lastGlintsTL.x-m_userRoi.x),r.y-m_glintPadding+(m_lastGlintsTL.y-m_userRoi.y),r.width+m_glintPadding*2,r.height+m_glintPadding*2) );
            //SMALL:m_glintsRect.push_back(cv::Rect(r.x-1+(m_lastGlintsTL.x-m_userRoi.x),r.y-1+(m_lastGlintsTL.y-m_userRoi.y),r.width+2,r.height+2) );
        }
    }
    //              AURA94
    //              TSVH-05142018-093555    TSVH-12142017-162513
    //MedianBlur -> 793 and 154             1312.2 and 182.86
    //MedianBlur -> 116.22 and 27.022       210.33 and 116.10
    //ERIK:CRITICAL
    cv::medianBlur(mPupil,m_PupilBlurred,m_blurRoi); //TIMECONSUMING
#if OSCANN == 0  //v1.0.6: New
    if(m_PupilBlurred.size() != cv::Size(0,0) ){
        cv::imshow("m_PupilBlurred", m_PupilBlurred);               //TODODEBUG:
        cv::moveWindow("m_PupilBlurred", 750, 50);                  //TODODEBUG:
    }
#endif
    cv::Sobel(m_PupilBlurred, m_PupilSobelX, CV_32F, 1, 0, 3);
    cv::Sobel(m_PupilBlurred, m_PupilSobelY, CV_32F, 0, 1, 3);
    cv::Canny(m_PupilBlurred, m_PupilEdges, m_cannyThreshold1, m_cannyThreshold2);
    if(m_userRoi == cv::Rect(0,0,0,0)){
        //v1.0.7: cv::Rect roiUnpadded(m_paddingValue,m_paddingValue,m_roiPupil.width,m_roiPupil.height);
        cv::Rect roiUnpadded = roiFromRectangle(cv::Rect(m_paddingValue,m_paddingValue,m_roiPupil.width,m_roiPupil.height),
                                                mPupil.cols,
                                                mPupil.rows
                                                );
        mPupil = cv::Mat(mPupil, roiUnpadded);
        m_PupilBlurred = cv::Mat(m_PupilBlurred, roiUnpadded);
        m_PupilSobelX = cv::Mat(m_PupilSobelX, roiUnpadded);
        m_PupilSobelY = cv::Mat(m_PupilSobelY, roiUnpadded);
        m_PupilEdges = cv::Mat(m_PupilEdges, roiUnpadded);
    }
#if OSCANN == 0  //v1.0.6: New
    if(m_PupilEdges.size() != cv::Size(0,0) ){
        cv::imshow("m_PupilEdges",m_PupilEdges);                    //TODODEBUG:
        cv::moveWindow("m_PupilEdges", 1000, 50);                   //TODODEBUG:
    }
#endif
    m_bbPupil = boundingBox(mPupil);
    element.release();
    return 0;
}

int OTracker::starburst(){
    std::vector<double> distances;
    std::vector<cv::Point2f> centres;
    std::vector<cv::Point2f> points_48;
    std::vector<cv::Point2f> points_16;

    if (params.StarburstPoints > 0){
        //CRITICAL: <cv::Point3f> edgePointsConcurrent;
        std::array<cv::Point3f, 64> edgePointsConcurrent;
        //????? ¿What is the rationale of m_roiPupil?
        if(m_userRoi == cv::Rect(0,0,0,0))
            centres.push_back(m_elPupilThresh.center - cv::Point2f(m_roiPupil.tl().x, m_roiPupil.tl().y));
        else
            centres.push_back(m_elPupilThresh.center);
        m_edgePoints.clear();
        BOOST_FOREACH(const cv::Point2f& centre, centres) {
            tbb::parallel_for(size_t(0), size_t(m_ptoDirs.size()),[&] (size_t index){
                int t = 1;
                //cv::Point p = centre + (t * pDir);
                cv::Point p = centre + (t * m_ptoDirs[index]);
                float dx, dy, cdirx, cdiry;
                double dirCheck;
                double distance;
                uchar val;
                bool insideSomeGlint = false;
                m_starburstPtos[index] = false;
                while(p.inside(m_bbPupil)){
                    if(index==20)
                        points_48.push_back(p);
                    if(index==45)
                        points_16.push_back(p);
                    for(unsigned int isg=0;isg<m_glintsRect.size();isg++){
                        insideSomeGlint = false;
                        if(p.inside(m_glintsRect[isg])){
                            insideSomeGlint = true;
                            break;
                        }
                    }
                    if(!insideSomeGlint){
                        val = m_PupilEdges(p);
                        if (val > 0){
                            dx = m_PupilSobelX(p);
                            dy = m_PupilSobelY(p);
                            cdirx = p.x - (m_elPupilThresh.center.x - m_roiPupil.x);
                            cdiry = p.y - (m_elPupilThresh.center.y - m_roiPupil.y);
                            // Check edge direction
                            dirCheck = dx*cdirx + dy*cdiry;
                            if (dirCheck > 0 ){
                                // We've hit an edge
                                p.x +=0.5f;
                                p.y += 0.5f;
                                distance = sqrt(pow(centre.x-p.x,2)+pow(centre.y-p.y,2));
                                //CRITICAL:edgePointsConcurrent.push_back(cv::Point3f(p.x, p.y, distance));
                                edgePointsConcurrent[index] = cv::Point3f(p.x, p.y, distance);
                                m_starburstPtos[index] = true;
                                break;
                            }
                        }
                    }
                    ++t;
                    p = centre + (t * m_ptoDirs[index]);
                }
            });
        }
        /*libDetection 1.0: Starbust points are sorted around the ellipse that they form.
                          Before this sort was based on x and y. However, the points do not follow the ellipse way
                               BEFORE             NOW

                                *  *              *  *
                             *        *        *        *
                            *          *      *          *
                            *          *      *          *
                             *        *        *        *
                                *  *              *  *
                                5  7              5  6
                             3        9        4        7
                            1          *      3          8
                            0          *      2          9
                             2        8        1        *
                                4  6              0  *
        */
        //TODODroopyEyelid IDEA : Nota de 7. Es mejor la IDEA003
        /*double lowerDistance;
        for(int i=0,j=32; i<m_starburstPtos.size();i++,j--){
            if(j<0)
                j=63;
            if(i > 20 && i < 45){
                ////IDEA001(BEGIN)
                //std::cout<<" j: "<<i<<std::endl;
                //if(m_starburstPtos[j]){
                //    std::cout<<" for frame "<<i<<" we are taking frame  "<<j<<" point: "<<edgePointsConcurrent[j]<<" centres[0]: "<<centres[0]<<std::endl;
                //    m_edgePoints.push_back(cv::Point2f(edgePointsConcurrent[j].x,
                //                                       centres[0].y - (edgePointsConcurrent[j].y-centres[0].y)));
                //    distances.push_back(edgePointsConcurrent[j].z);
                //}IDEA001(END)
                 //IDEA002(BEGIN)
                 if(m_starburstPtos[j]){
                     std::cout<<" edgePointsConcurrent[j].x: "<<edgePointsConcurrent[j].x<<std::endl;
                     std::cout<<" lowerDistance: "<<lowerDistance<<std::endl;
                    std::cout<<" centres[0]: "<<centres[0]<<std::endl;
                    std::cout<<" new: "<<centres[0].y - sqrt(pow(lowerDistance,2) - pow(edgePointsConcurrent[j].x-centres[0].x,2))<<std::endl;
                    m_edgePoints.push_back(cv::Point2f(edgePointsConcurrent[j].x,
                                                       centres[0].y - sqrt(pow(lowerDistance,2) - pow(edgePointsConcurrent[j].x-centres[0].x,2))));
                    distances.push_back(edgePointsConcurrent[j].z);
                }//IDEA002(BEGIN)
            }else{
                if(m_starburstPtos[i]){
                    m_edgePoints.push_back(cv::Point2f(edgePointsConcurrent[i].x, edgePointsConcurrent[i].y));
                    distances.push_back(edgePointsConcurrent[i].z);
                    lowerDistance = edgePointsConcurrent[i].z;
                }
            }
        }*/
        /*//TODODroopyEyelid IDEA003(Begin)
        int lower=22,upper=42;
        double lowerDistance=0.0, upperDistance=0.0;
        bool upperDefined = false;
        for(int i=0; i<m_starburstPtos.size();i++){
            if(i < lower || i > upper){
                if(m_starburstPtos[i]){
                    m_edgePoints.push_back(cv::Point2f(edgePointsConcurrent[i].x, edgePointsConcurrent[i].y));
                    distances.push_back(edgePointsConcurrent[i].z);
                    if(i<lower)
                        lowerDistance = edgePointsConcurrent[i].z;
                    if(i>upper && !upperDefined){
                        upperDistance = edgePointsConcurrent[i].z;
                        upperDefined = true;
                    }
                }
            }
        }
        double distance = (lowerDistance+upperDistance)/2;
        for(int j=lower+32, i=0; i<(upper-lower);j++, i++){
            if(j>63)
                j = 0;
            if(m_starburstPtos[j]){
                m_edgePoints.push_back(cv::Point2f(edgePointsConcurrent[j].x,
                                                   centres[0].y - sqrt(pow(distance,2) - pow(edgePointsConcurrent[j].x-centres[0].x,2))));
                distances.push_back(edgePointsConcurrent[j].z);
            }

        }//TODODroopyEyelid IDEA003(End)*/

        for(unsigned int i=0;i<m_starburstPtos.size();i++){
            if(m_starburstPtos[i]){
                m_edgePoints.push_back(cv::Point2f(edgePointsConcurrent[i].x, edgePointsConcurrent[i].y));
                distances.push_back(edgePointsConcurrent[i].z);
            }
        }
        if (m_edgePoints.size() < (unsigned int) params.StarburstPoints/2){
            std::ostringstream oss;
            oss << "ERROR 04: starburst - Only "<< m_edgePoints.size()<< " points were found. However, "<<params.StarburstPoints/2<<" are nedded";
            m_errorMsg = oss.str();
            return m_errno = -4;
        }
    }
    else{
        //BEGIN(Non-zero value finder)
        for(int y = 0; y < m_PupilEdges.rows; y++){
            uchar* val = m_PupilEdges[y];
            for(int x = 0; x < m_PupilEdges.cols; x++, val++){
                if(*val == 0)
                    continue;
                m_edgePoints.push_back(cv::Point2f(x + 0.5f, y + 0.5f));
            }
        }
        //END(Non-zero value finder)
    }
    /*libDetection 1.0: Remove outlier starburst points
                      Before this sort was based on x and y. However, the points do not follow the ellipse way
                           BEFORE                NOW

                            *  *                *  *
                         *        *          *        *
                        *          *  ->    *          *
                        *          *        *          *
                         *      *            *
                            *  *                *  *
                            *  *                *  *
                         *        *          *        *
                        *          *  ->    *          *
                        *     *    *        *          *
                                  *                   *
                            *  *                *  *

                        The implemented method calculates the error between consecutive points in both clockwise and counterclockwise
                        That is, counterclockwise: 1-0, 2-1, 3-2, 4-3, 5-4, 6-5, ...
                                        cloclwise: 10-11, 9-10, 9-8, 8-7, ...
                        This method uses the last position checked. In the counterclockwise option, this variable takes de values 0, 1, 2, 3, 4, 5, 6, ...
                        Whereas, in the cloclwise options this variable takes the values n, n-1, n-2, n-3.
                        This method considers that an outlier is found when the error is greter that 4.0
                        When an outlier is found, the last position is not updated. Thus, the last position is compared to the next positions.
                        For example, consider an outliar un position 4 (4-3). Therefore, next operations calculate 5-3, 6-3, 7-3, 8-3, etc.
                        The last position is updated when the error is lower that 4.0

                                5  6              8  9
                             4        7        7        *
                            3          8      6          *
                            2          9      5          0
                             1       10        4        1
                                0 11              3  2

                        IMPORTANT: Several methods have been implemented. For example,
                        A) the described method but only cloclwise and only consecutive positions.
                        B) calculating counterclockwise and cloclwise without abs. That is, verifying both error > 4.0 or error < -4.0
                        C) Consecutive and cloclwise. When an outlier is found, +/- 4 elements are analized too. If 3 aoutliers are found within this range,
                           the element is deleted.*/
    double error = 0.0;
    unsigned int last;
#if OSCANN == 0  //v1.0.6: New
    cv::Mat mStar=m_PupilBlurred.clone();
    if(m_PupilBlurred.size() != cv::Size(0,0)){
        cv::cvtColor(mStar,mStar,cv::COLOR_GRAY2BGR);
        //TODODEBUGBLOCK000
        cv::Mat all=m_PupilBlurred.clone();
        cv::cvtColor(all,all,cv::COLOR_GRAY2BGR);
        for(unsigned int i=0;i<m_glintsRect.size();i++){
            cv::rectangle(all,m_glintsRect[i].tl(),m_glintsRect[i].br(), cv::Scalar(255,0,255), 1, 8, 0);
        }
        for(unsigned int i=0;i<m_edgePoints.size();i++){
            cv::circle(all,m_edgePoints[i],1,cv::Scalar(255,0,255));
        }
        for(unsigned int i=0;i<points_48.size();i++){
            cv::circle(all,points_48[i],1,cv::Scalar(255,0,0));
        }
        for(unsigned int i=0;i<points_16.size();i++){
            cv::circle(all,points_16[i],1,cv::Scalar(128,0,0));
        }
        cv::imshow("All",all);
        cv::moveWindow("All", 1300, 200);
        all.release();
    }
#endif
    unsigned int l = m_edgePoints.size(), j=0, k=1, weird;
    last = j;
    for(unsigned int i=1;i<l;i++){
        error = std::abs(distances[k]-distances[last]);
        if(error > 4.0){
            weird = 0;
            for(unsigned int w=k+1;w<k+4;w++){
                if(w<distances.size())
                    if(std::abs(distances[k]-distances[w]) > 4.0)
                        weird++;
            }
            for(unsigned int w=k-1;w>k-4;w--){
                if(std::abs(distances[k]-distances[w]) > 4.0)
                    weird++;
            }
            if(weird > 3){
#if OSCANN == 0  //v1.0.6: New
                cv::circle(mStar,m_edgePoints[k],5,cv::Scalar(255,0,0));            //TODODEBUG
#endif
                m_edgePoints.erase(m_edgePoints.begin()+k);
                distances.erase(distances.begin()+k);
            }
        }else{
            j++;k++;last = j;
        }
    }
#if OSCANN == 0  //v1.0.6: New
    for(unsigned int i=0;i<centres.size();i++){                                 //TODODEBUGBLOCK001
        cv::circle(mStar,centres[i],5,cv::Scalar(0,255,0));}
    for(unsigned int i=0;i<m_edgePoints.size();i++){
        if(i == 0)          cv::circle(mStar,m_edgePoints[i],5,cv::Scalar(255,255,255));
        else if(i == 10)    cv::circle(mStar,m_edgePoints[i],1,cv::Scalar(0,64,0));
        else if(i == 20)    cv::circle(mStar,m_edgePoints[i],1,cv::Scalar(0,128,0));
        else if(i == 30)    cv::circle(mStar,m_edgePoints[i],1,cv::Scalar(0,255,0));
        else                cv::circle(mStar,m_edgePoints[i],1,cv::Scalar(0,0,128+i));}
    cv::imshow("Valid",mStar);
    cv::moveWindow("Valid", 1300, 500);
    mStar.release();                                                            //TODODEBUGBLOCK001
#endif
    return 0;
}

int OTracker::ellipseFitting(){
    m_centroidesGlintsPos.clear();
    cv::RotatedRect elPupil;                    //ERIK: para que crear nuevas variables?????. Se puede trabajar con out???
    std::vector<cv::Point2f> inliers;
    const double p = 0.99;//999;                // Desired probability that only inliers are selected
    double w = params.PercentageInliers/100.0;  // Probability that a point is an inlier: 0.3
    //ORIGINAL: const unsigned int n = 5;                   // Number of points needed for a model: Why 5?????
    const unsigned int n = 20;                   // Number of points needed for a model
    if (m_edgePoints.size() >= n){ // Minimum points for ellipse
        // RANSAC!!!
        double wToN = std::pow(w,n);
        int k = static_cast<int>(std::log(1-p)/std::log(1 - wToN)  + 2*std::sqrt(1 - wToN)/wToN);
        // Use TBB for RANSAC
        struct EllipseRansac_out {
            std::vector<cv::Point2f> bestInliers;
            cv::RotatedRect bestEllipse;
            double bestEllipseGoodness;
            int earlyRejections;
            bool earlyTermination;
            unsigned int attempts;
            EllipseRansac_out() : bestEllipseGoodness(-std::numeric_limits<double>::infinity()), earlyRejections(0), earlyTermination(false), attempts(0) {}
        };
        struct EllipseRansac {
            const parameters& params;
            const std::vector<cv::Point2f>& edgePoints;
            unsigned int n;
            const cv::Rect& bb;
            const cv::Mat_<float>& mDX;
            const cv::Mat_<float>& mDY;
            int earlyRejections;
            bool earlyTermination;
            unsigned int attempts;
            EllipseRansac_out out;
            EllipseRansac(
                        const parameters& params,
                        const std::vector<cv::Point2f>& edgePoints,
                        int n,
                        const cv::Rect& bb,
                        const cv::Mat_<float>& mDX,
                        const cv::Mat_<float>& mDY) : params(params), edgePoints(edgePoints), n(n), bb(bb), mDX(mDX), mDY(mDY), earlyRejections(0), earlyTermination(false), attempts(0){}
            EllipseRansac(EllipseRansac& other, tbb::split) : params(other.params), edgePoints(other.edgePoints), n(other.n), bb(other.bb), mDX(other.mDX), mDY(other.mDY), earlyRejections(other.earlyRejections), earlyTermination(other.earlyTermination), attempts(other.attempts){}
            void operator()(const tbb::blocked_range<size_t>& r){
                if (out.earlyTermination){
                    return;
                }
                cv::RotatedRect ellipseInlierFit;
                cv::Point2f grad;
                float dx;
                float dy;
                float dotProd;
                bool gradientCorrect;
                std::vector<cv::Point2f> sample;
                std::vector<cv::Point2f> inliers;
                double ellipseGoodness;
                double edgeStrength;
                cv::RotatedRect ellipseSampleFit;
                cv::Size_<double> s;
                double eccentricity;
                double eccMax;
                float errOf1px;
                float errorScale;
                float widthErr;
                float heightErr;
                for( size_t i=r.begin(); i!=r.end(); ++i ){
                    //?????
                    if(i>256){
                        out.attempts = 256;
                        return;
                    }
                    // Ransac Iteration
                    if (params.Seed >= 0)
                        sample = randomSubset(edgePoints, n, static_cast<unsigned int>(i + params.Seed));
                    else
                        sample = randomSubset(edgePoints, n);   //ALWAYS THIS
                    ellipseSampleFit = cv::fitEllipse(sample);
                    // Normalise ellipse to have width as the major axis.
                    if (ellipseSampleFit.size.height > ellipseSampleFit.size.width){
                        ellipseSampleFit.angle = std::fmod(ellipseSampleFit.angle + 90, 180);
                        std::swap(ellipseSampleFit.size.height, ellipseSampleFit.size.width);
                    }
                    s = ellipseSampleFit.size;
                    if(m_lastEllipse != cv::Size2f(-1,-1)){
                        if(s.width > m_lastEllipse.width)
                            widthErr = s.width - m_lastEllipse.width;
                        else
                            widthErr = m_lastEllipse.width-s.width;
                        if(s.height > m_lastEllipse.height)
                            heightErr = s.height - m_lastEllipse.height;
                        else
                            heightErr = m_lastEllipse.height-s.height;
                    }else{
                        widthErr = 0.0;
                        heightErr = 0.0;
                    }
                    attempts++;
                    eccentricity=sqrt(1-(pow(s.height,2)/pow(s.width,2)));
                    //ORIGINAL: eccMax=0.65; //FIXED VALUE (0=Circulo, 1=Linea)
                    //NOTE: Changed to 0.7 for AURA83/CC9-02192018-095103 -> first calibration point <-
                    //              to 0.75 for 1060/CC9-05102018-134023  -> first calibration point <-
                    eccMax=0.75; //FIXED VALUE (0=Circulo, 1=Linea)
                    // Discard useless ellipses early
                    if (!ellipseSampleFit.center.inside(bb)
                            || s.height > params.Radius_Max*2
                            || s.width > params.Radius_Max*2
                            || (s.height < params.Radius_Min*2 && s.width < params.Radius_Min*2)
                            || s.height > 4*s.width
                            || s.width > 4*s.height
                            || eccentricity > eccMax
                            || widthErr > 1.0
                            || heightErr > 1.0
                            ) {
                        // Bad ellipse
                        continue;
                    }
                    // Use conic section's algebraic distance as an error measure
                    ConicSection conicSampleFit(ellipseSampleFit);
                    // Check if sample's gradients are correctly oriented
                    if (params.EarlyRejection){
                        gradientCorrect = true;
                        BOOST_FOREACH(const cv::Point2f& p, sample){
                            grad = conicSampleFit.algebraicGradientDir(p);
                            dx = mDX(cv::Point(p.x, p.y));
                            dy = mDY(cv::Point(p.x, p.y));
                            dotProd = dx*grad.x + dy*grad.y;
                            gradientCorrect &= dotProd > 0;
                        }
                        if (!gradientCorrect){
                            continue;
                        }
                    }
                    // Assume that the sample is the only inliers
                    ellipseInlierFit = ellipseSampleFit;
                    ConicSection conicInlierFit = conicSampleFit;
                    // Iteratively find inliers, and re-fit the ellipse
                    for (int i = 0; i < params.InlierIterations; ++i){
                        // Get error scale for 1px out on the minor axis
                        cv::Point2f minorAxis(-std::sin(PI/180.0*ellipseInlierFit.angle), std::cos(PI/180.0*ellipseInlierFit.angle));
                        cv::Point2f minorAxisPlus1px = ellipseInlierFit.center + (ellipseInlierFit.size.height/2 + 1)*minorAxis;
                        errOf1px = conicInlierFit.distance(minorAxisPlus1px);
                        errorScale = 1.0f/errOf1px;
                        // Find inliers
                        inliers.reserve(edgePoints.size());
                        const float MAX_ERR = 2;
                        BOOST_FOREACH(const cv::Point2f& p, edgePoints){
                            float err = errorScale*conicInlierFit.distance(p);
                            if (err*err < MAX_ERR*MAX_ERR)
                                inliers.push_back(p);
                        }
                        if (inliers.size() < n) {
                            inliers.clear();
                            continue;
                        }
                        // Refit ellipse to inliers
                        ellipseInlierFit = cv::fitEllipse(inliers);
                        conicInlierFit = ConicSection(ellipseInlierFit);
                        // Normalise ellipse to have width as the major axis.
                        if (ellipseInlierFit.size.height > ellipseInlierFit.size.width){
                            ellipseInlierFit.angle = std::fmod(ellipseInlierFit.angle + 90, 180);
                            std::swap(ellipseInlierFit.size.height, ellipseInlierFit.size.width);
                        }
                    }
                    if (inliers.empty())
                        continue;
                    // Discard useless ellipses again
                    s = ellipseInlierFit.size;
                    eccentricity=sqrt(1-(pow(s.height,2)/pow(s.width,2)));
                    if (!ellipseInlierFit.center.inside(bb)
                            || s.height > params.Radius_Max*2
                            || s.width > params.Radius_Max*2
                            || (s.height < params.Radius_Min*2 && s.width < params.Radius_Min*2)
                            || s.height > 4*s.width
                            || s.width > 4*s.height
                            || eccentricity > eccMax
                            ){
                        // Bad ellipse!
                        continue;
                    }
                    // Calculate ellipse goodness
                    ellipseGoodness = 0;
                    if (params.ImageAwareSupport){
                        BOOST_FOREACH(cv::Point2f& p, inliers){
                            grad = conicInlierFit.algebraicGradientDir(p);
                            dx = mDX(p);
                            dy = mDY(p);
                            edgeStrength = dx*grad.x + dy*grad.y;
                            ellipseGoodness += edgeStrength;
                        }
                    }
                    else{
                        ellipseGoodness = inliers.size();
                    }
                    if (ellipseGoodness > out.bestEllipseGoodness){
                        std::swap(out.bestEllipseGoodness, ellipseGoodness);
                        std::swap(out.bestInliers, inliers);
                        std::swap(out.bestEllipse, ellipseInlierFit);
                        // Early termination, if 90% of points match
                        if (params.EarlyTerminationPercentage > 0   //Erik: Always true
                                && out.bestInliers.size() > params.EarlyTerminationPercentage*edgePoints.size()/100){
                            earlyTermination = true;
                            out.attempts = attempts;
                            break;
                        }
                    }

                }
            }
            void join(EllipseRansac& other){
                if (other.out.bestEllipseGoodness > out.bestEllipseGoodness){
                    std::swap(out.bestEllipseGoodness, other.out.bestEllipseGoodness);
                    std::swap(out.bestInliers, other.out.bestInliers);
                    std::swap(out.bestEllipse, other.out.bestEllipse);
                }
                earlyTermination |= other.earlyTermination;
                out.earlyTermination = earlyTermination;
                out.attempts += other.attempts;
            }
        };
        EllipseRansac ransac(params, m_edgePoints, n, m_bbPupil, m_PupilSobelX, m_PupilSobelY);
        try{
            tbb::parallel_reduce(tbb::blocked_range<size_t>(0,k,k/8), ransac);
        }
        catch (std::exception& e){
            std::cerr << e.what() << std::endl;
        }
        m_PupilSobelX.release();
        m_PupilSobelY.release();
        inliers = ransac.out.bestInliers;
        m_earlyTermination = ransac.out.earlyTermination;
        m_fittingAttempts += ransac.out.attempts;
        cv::RotatedRect ellipseBestFit = ransac.out.bestEllipse;
        ConicSection conicBestFit(ellipseBestFit);
        cv::Point2f grad;
        BOOST_FOREACH(const cv::Point2f& p, m_edgePoints){
            grad = conicBestFit.algebraicGradientDir(p);
        }
        elPupil = ellipseBestFit;
        elPupil.center.x += m_roiPupil.x;
        elPupil.center.y += m_roiPupil.y;
    }
    int glint1=-1, glint2=-1;
    if(m_glintsContours.size() == 2){
        /*NOTE: Even when we know that they are only two. We must be sure that they are glints*/
        //v1.0.8: if((m_glintsCentroides[0].y > (m_glintsCentroides[1].y - 10.0)) && (m_glintsCentroides[0].y < (m_glintsCentroides[1].y + 10.0)) ){
        if((m_glintsCentroides[0].y > (m_glintsCentroides[1].y - m_glintsDistance)) && (m_glintsCentroides[0].y < (m_glintsCentroides[1].y + m_glintsDistance)) ){
            glint1 = 0;
            glint2 = 1;
        }
    }else if(m_glintsContours.size() > 2){
        for(unsigned int i = 0; i< m_glintsContours.size(); i++ ){
            if(m_glintPaired[i])
                continue;
            for(unsigned int j = 0; j< m_glintsContours.size(); j++ ){
                if(m_glintPaired[i])
                    continue;
                //                          A-0.5                                             A+0.5
                // ------------------------------------------B---------A----------------------------------------------------------------------------
                //  0.0  0.1  0.2  0.3  0.4  0.5  0.6  0.7  0.8  0.9  1.0  1.1  1.2  1.3  1.4  1.5  1.6  1.7  1.8  1.9  2.0  2.1  2.2  2.3  2.4  2.5
                if(i != j){
                    if((m_glintsCentroides[j].y > (m_glintsCentroides[i].y -4.0)) && (m_glintsCentroides[j].y < (m_glintsCentroides[i].y +4.0)) ){
                        m_glintPaired[i]=true;
                        m_glintPaired[j]=true;
                        if(glint1 == -1 && glint2 == -1){
                            glint1 = i;
                            glint2 = j;
                        }else{
                            if((m_glintsCentroides[i].y+m_glintsCentroides[j].y)/2 > (m_glintsCentroides[glint1].y+m_glintsCentroides[glint2].y)/2){
                                glint1 = i;
                                glint2 = j;
                            }

                        }
                        break;
                    }
                }

            }
        }
    }
    if (inliers.size() == 0 || (glint1 == -1)){
        std::ostringstream oss;
        if(glint1 == -1){
            //v1.0.8
            m_erode = m_initialErode;
            //v1.0.8
            m_lastErode = -1;
            oss << "ERROR 05 ellipseFitting: Only "<< inliers.size()<< " inliers and "<<m_glintsCentroides.size()<<" glints centroides were found"<<". However, glints are very far apart. glint1.y: "<<m_glintsCentroides[0].y<<", glint2.y "<<m_glintsCentroides[1].y;
            m_errorMsg = oss.str();
            return m_errno = -5;
        }else{
            oss << "ERROR 06 ellipseFitting: Only "<< inliers.size()<< " inliers and "<<m_glintsCentroides.size()<<" glints centroides were found";
            m_errorMsg = oss.str();
            return m_errno = -6;
        }
    }else{
        m_pupil = elPupil.center;
        m_ellipse = elPupil;
        if(m_userRoi != cv::Rect(0,0,0,0)){
            m_pupil.x += m_userRoi.x - m_roiPupil.x;
            m_pupil.y += m_userRoi.y - m_roiPupil.y;
            m_ellipse.center.x += m_userRoi.x - m_roiPupil.x;
            m_ellipse.center.y += m_userRoi.y - m_roiPupil.y;
        }
        if(m_searchAgainRoi != cv::Rect(0,0,0,0)){
            m_pupil.x += m_searchAgainRoi.x;
            m_pupil.y += m_searchAgainRoi.y;
            m_ellipse.center.x += m_searchAgainRoi.x;
            m_ellipse.center.y += m_searchAgainRoi.y;
        }
        if(m_lastGlintsTL == cv::Point(0,0) && m_lastGlintsBR == cv::Point(0,0)){
            m_centroidesGlintsPos.push_back(m_glintsCentroides[glint1]+cv::Point2f(m_roiGlintsLarge.tl()+m_userRoi.tl() + m_searchAgainRoi.tl())); //Ojo, se le suma el top-left del roi usado (mPupil)
            m_centroidesGlintsPos.push_back(m_glintsCentroides[glint2]+cv::Point2f(m_roiGlintsLarge.tl()+m_userRoi.tl() + m_searchAgainRoi.tl())); //Ojo, se le suma el top-left del roi usado (mPupil)
        }else{
            m_centroidesGlintsPos.push_back(m_glintsCentroides[glint1]+cv::Point2f(m_userRoi.tl().x+(m_lastGlintsTL.x-m_userRoi.tl().x), m_userRoi.tl().y+( m_lastGlintsTL.y-m_userRoi.tl().y)));
            m_centroidesGlintsPos.push_back(m_glintsCentroides[glint2]+cv::Point2f(m_userRoi.tl().x+(m_lastGlintsTL.x-m_userRoi.tl().x), m_userRoi.tl().y+( m_lastGlintsTL.y-m_userRoi.tl().y)));
        }
        if(m_centroidesGlintsPos[0].x<m_centroidesGlintsPos[1].x){
            m_leftGlint = m_centroidesGlintsPos[0];
            m_rightGlint = m_centroidesGlintsPos[1];
            m_lastLeftGlint = m_glintsCentroides[0];
            m_lastRightGlint = m_glintsCentroides[1];
        }else{
            m_leftGlint = m_centroidesGlintsPos[1];
            m_rightGlint = m_centroidesGlintsPos[0];
            m_lastLeftGlint = m_glintsCentroides[1];
            m_lastRightGlint = m_glintsCentroides[0];
        }
    }
    return 0;
}
void OTracker::config(){
    m_errorMsg = "";
    m_debug =   false;
    m_searchAgainRoi = cv::Rect(0,0,0,0);
#if OSCANN == 0  //v1.0.8
    m_again = false;
#endif
}

std::vector<std::pair<int, int>> OTracker::getBlinks(){return m_blinks;}
void OTracker::addBlink(){
    int blinkLenght = m_blinkEnd-m_blinkBegin;
    if(m_inBlink){
        if((m_blinkBegin > -1 && m_blinkEnd > -1)
            //v1.0.3: 3 for fast blinks
            //v1.0.5: && (blinkLenght>3 && blinkLenght<92)
            && (blinkLenght >= 3 && blinkLenght<92)
            //v1.0.3: && m_fails > 4
            //v1.0.5: && m_fails >= 4
            && m_fails >= 3){
            //v1.0.3: && m_framesKo >= 2
                m_blinks.push_back(std::make_pair(m_blinkBegin,m_blinkEnd));
        }
    }
}
//v4.0.11:
void OTracker::isCalibration(bool value){
    m_isCalibration = value;
}
void OTracker::clearBlinks(){
    m_blinks.clear();
    resetBlinkVars();
}
void OTracker::checkFails(){
    if(m_fails == m_lastFails && m_fails != 0){
        m_equal++;
    }
    if(m_equal > 4 && m_fails > 4){
        addBlink();
        resetBlinkVars();
    }
    m_lastFails = m_fails;
}
void OTracker::resetBlinkVars(){
    m_blinkBegin = -1;
    m_blinkEnd = -1;
    m_withoutAttempts = 0;
    m_framesKo = 0;
    blk_suddenBegin = -1;
    m_inBlink = false;
    m_fails = 0;
    m_equal = 0;
}

int OTracker::find(){
    int result;
    int times = 0;
    double w;
    double h;
    double err;
    cv::Rect roiBck;
    config();                                                                           //~1 microseconds
    if(m_userRoi != cv::Rect(0,0,0,0))
        roiBck = m_userRoi;
    do{
        result = 0;
        m_errno = 0;
        greyAndCrop();                                                                  //~200 microseconds
        if(pupilRegion() >= 0){                                                         //~247 microseconds, 52 std
            if(glintsDetection()>=0){
                if(starburst() >= 0){                                                   //1 -> 55:25, 2 -> 60:37, 3 -> 79:68
                    if(ellipseFitting() < 0){result = -4;}                              //1 -> 1705:14240-218888:228, 2 -> 2132:12828-476774:200    3 -> 996:15469-911429:199
                 }else{result = -3;}
            }else{result = -2;}
        }else{result = -1;}
        if(result < 0){
#if OSCANN == 0  //v1.0.6: New
            if(!m_withMouse){
#endif
                if(m_userRoi != cv::Rect(0,0,0,0)){
                    //v1.0.9: BUG COMMENT:
                    //v1.0.9: w = m_userRoi.width/(double)(4/(times+3));
                    //2.0 for Santander -> DFT -> 01056 -> CC9-05032018-111115
                    //1.0 for Santander -> DFT -> 01056 -> CC9-05032018-112423
                    w = m_userRoi.width/(1.0/((float)times+3.0));
                    //h = m_userRoi.height/(double)(6/(times+3));
                    //4.0 for Santander -> DFT -> 01056 -> CC9-05032018-111115
                    //2.0 for Santander -> DFT -> 01056 -> CC9-05032018-112423
                    h = m_userRoi.height/(2.0/((float)times+3));
                    m_searchAgainRoi = roiFromRectangle(cv::Rect( m_userRoi.x-w,m_userRoi.y-h,m_userRoi.width+w*2,m_userRoi.height+h*2));
                    m_userRoi = cv::Rect(0,0,0,0);
                }
                m_lastGlintsTL      =   cv::Point(0,0);
                m_lastGlintsBR      =   cv::Point(0,0);
                m_bestContour.clear();
                m_lastEllipse = cv::Size2f(-1,-1);
                m_eye.release();
                m_eyeFocus.release();
#if OSCANN == 0  //v1.0.6: New
            }
            //v1.0.8 : PABLO2
            m_again = true;
#endif
        }
        times++;
        //v1.0.11: if(times == 2 || m_inBlink)
        if(times == 2 )
            break;
    }while(result < 0);
    if(result < 0){
        if(result > -4){    //v1.0.4: Statement added
            m_fails++;
            m_withoutAttempts = 0;
            m_framesKo = 0;
            if(m_blinkBegin > 0){
                m_inBlink = true;
                result = -99;                                               //Blink
            }else{
                //v1.0.4: if(blk_suddenBegin < 0)
                if(blk_suddenBegin < 0){
                    blk_suddenBegin = m_id;
                    //v1.0.4: New
                    m_fails = 0;
                }
                //v1.0.5: if(m_fails > 4){ //For fast blinks
                if(m_fails >= 3){
                    m_inBlink = true;
                    //v1.0.3: m_blinkBegin = blk_suddenBegin;
                    //v1.0.4: if(((blk_suddenBegin - 4) > -1))
                    if(((blk_suddenBegin - 4) > -1) && ((m_id - blk_suddenBegin - 4) < 8)){
                        m_blinkBegin = blk_suddenBegin-4;
                    }else{//v1.0.4: New else ETO
                        resetBlinkVars();
                    }
                    blk_suddenBegin = -1;
                }
            }
        }
        m_userRoi = roiBck;
        //?????
        m_lastEllipse = cv::Size2f(-1,-1);
        checkFails();
        return result;
    }
    //IMPORTANT NOTE: JUST TO SHOW  Yellow Rect. It can be removed
    if(m_roiGlintsLarge != cv::Rect(-1,-1,-1,-1)){
        //v1.0.9: Changed to draw correctly the yellow rectangle
        //m_roiGlintsLarge = roiFromRectangle(cv::Rect(m_roiGlintsLarge.x + m_userRoi.x,
        //                            m_roiGlintsLarge.y + m_userRoi.y,
        //                            m_roiGlintsLarge.width,
        //                            m_roiGlintsLarge.height));
        if(m_userRoi != cv::Rect(0,0,0,0))
            m_roiGlintsLarge = roiFromRectangle(cv::Rect(m_roiGlintsLarge.x+m_userRoi.x,m_roiGlintsLarge.y+m_userRoi.y,m_roiGlintsLarge.width,m_roiGlintsLarge.height));
        else
            m_roiGlintsLarge = roiFromRectangle(cv::Rect(m_roiGlintsLarge.x+m_searchAgainRoi.x,m_roiGlintsLarge.y+m_searchAgainRoi.y,m_roiGlintsLarge.width,m_roiGlintsLarge.height));
    }
    unsigned int paddingW = 20;
    unsigned int paddingH = 20;
#if OSCANN == 0  //v1.0.6: New
    	m_withMouse = false;
#endif
    m_userRoi = roiFromRectangle( cv::Rect(m_ellipse.center.x - (m_ellipse.size.width/2) - paddingW,
                         m_ellipse.center.y- (m_ellipse.size.height/2) - paddingH,
                         m_ellipse.size.width + paddingW*2,
                         m_ellipse.size.height + paddingH*2));
    /*IMPORTANT NOTE: Next lines define a region around the glint in order to track it.
     * An small region (-4) is good to avoid loss the glints when noise is presented (AURA81-TSLLV:INTRAOCULAR)
     * However, using small regions glints had a higher probability of being lost, speccilly in fast movements of the eye.
     * 10 ok*/
    m_lastGlintsTL = cv::Point(m_leftGlint.x-m_glintsRoiPadding,
                               m_leftGlint.y-m_glintsRoiPadding);
    m_lastGlintsBR = cv::Point(m_rightGlint.x+m_glintsRoiPadding,
                               m_rightGlint.y+m_glintsRoiPadding);
    m_lastPupil     =   m_pupil;
    if(m_lastEllipse != cv::Size2f(-1,-1)){
        if(m_lastEllipse.height > m_ellipse.size.height)
            err  = m_lastEllipse.height-m_ellipse.size.height;
        else
            err = m_ellipse.size.height-m_lastEllipse.height;
        if(err > 1.3){
            if(!m_inBlink){
                //if(m_id - m_blinkBegin > 10){
                //    m_blinkBegin = m_id;
                //v1.0.4: if((m_id - m_blinkBegin - m_fails - 4) > 10){
                if((m_blinkBegin > -1) && ((m_id - m_blinkBegin - m_fails - 4) > 10)){
                    m_blinkBegin = m_id - m_fails - 4;
                    m_blinkEnd = -1;
                    m_withoutAttempts = 0;
                }else{
                    m_withoutAttempts++;
                }
            }else{
                m_blinkEnd = m_id;
                m_withoutAttempts = 0;
            }
        }
    }
    //Last 1: This value is too sensible. In some cases, several frames after blink performs more than 1 attempts.
    if(m_fittingAttempts > 3){
        if(!m_inBlink){
            //v1.0.3: if(m_id - m_blinkBegin - m_fails > 10){
            //v1.0.3:     m_blinkBegin = m_id - m_fails;
            //v1.0.4: if((m_id - m_blinkBegin - m_fails - 4) > 10){
            if((m_blinkBegin > -1) && ((m_id - m_blinkBegin - m_fails - 4) > 10)){
                m_blinkBegin = m_id - m_fails - 4;
                m_blinkEnd = -1;
                //v1.0.4: m_withAttempts = 0;
            }
        }else{
            m_blinkEnd = m_id;
            //v1.0.4: m_withAttempts = 0;
            m_framesKo++;
            m_errno = -99;
        }
        m_withoutAttempts = 0;
    }else{
        m_withoutAttempts++;
    }
    if(m_withoutAttempts > 4){
        addBlink();
        resetBlinkVars();
    }
    //NOTE: Changed from 18 to ¿24? for AURA96-TSVH-Frames 2262-2303
    if(m_framesKo > 18){
        addBlink();
        resetBlinkVars();
    }
    m_fittingAttempts = 0;
    m_lastEllipse   =   m_ellipse.size;
    checkFails();
    return m_errno;
}
