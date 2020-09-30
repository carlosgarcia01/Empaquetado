#ifndef OTRACKER_H
#define OTRACKER_H

//openCV
#include <opencv2/core/ocl.hpp>
#include <opencv2/opencv.hpp>
#include <tbb/tbb.h>
#include <boost/foreach.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <random>
//#include "../oscann/gui/logger.h"

#define PUPIL 0
#define LEDS 1

const double PI = CV_PI;
const cv::Point2f UNKNOWN_POSITION = cv::Point2f(-1,-1);


using namespace std;

struct parameters{
    int Radius_Min;
    int Radius_Max;
    double CannyBlur;
    int StarburstPoints;
    int PercentageInliers;
    int InlierIterations;
    bool ImageAwareSupport;
    int EarlyTerminationPercentage;
    bool EarlyRejection;
    int Seed;
    bool defaultValues = true;
};
struct EdgePoint{
    cv::Point2f point;
    double edgeStrength;
    EdgePoint(const cv::Point2f& p, double s) : point(p), edgeStrength(s) {}
    EdgePoint(float x, float y, double s) : point(x,y), edgeStrength(s) {}
    bool operator== (const EdgePoint& other){
        return point == other.point;
    }
};
template<class T> T constrain(T input, T min, T max){
    //Limita la variable input a valores entre min y max
    T aux=std::max(min,input);
    return std::min(aux, max);
}

class HaarSurroundFeature{
public:
    HaarSurroundFeature(int r1, int r2);
    double val_inner, val_outer;
    int r_inner, r_outer;
};

template<typename T>
class ConicSection_{
public:
    T A,B,C,D,E,F;
    ConicSection_(cv::RotatedRect r);
    T algebraicDistance(cv::Point_<T> p);
    T distance(cv::Point_<T> p);
    cv::Point_<T> algebraicGradient(cv::Point_<T> p);
    cv::Point_<T> algebraicGradientDir(cv::Point_<T> p);
protected:
    void initFromEllipse(cv::Point_<T> axis, cv::Point_<T> centre, T a, T b);
};
typedef ConicSection_<float> ConicSection;

class OTracker{
private:

    //v4.0.11:
    bool m_isCalibration;

    std::array<cv::Point2f, 64> m_ptoDirs;
    std::array<bool, 64> m_starburstPtos;

    int m_fails;
    int m_lastFails;
    int m_equal;

    //1.0.8: cv::Point2f m_pupil;
    cv::Point2d m_pupil;

    //1.0.8: cv::Point2f m_leftGlint;
    cv::Point2d m_leftGlint;
    //1.0.8: cv::Point2f m_rightGlint;
    cv::Point2d m_rightGlint;

    cv::RotatedRect m_ellipse;
    static cv::Size2f m_lastEllipse;


    bool m_earlyTermination;
    unsigned int m_fittingAttempts;

    //Blink Detecttion
    //Numbre of frame where detection is not normal
    int blk_suddenBegin;
    int m_blinkBegin;
    int m_blinkEnd;
    unsigned int m_withoutAttempts;
    unsigned int m_framesKo;
    bool m_inBlink;
    std::vector<std::pair<int, int>> m_blinks;


    unsigned int m_cannyThreshold1;
    unsigned int m_cannyThreshold2;

    unsigned int m_erode;
    //v1.0.8
    unsigned int m_initialErode;
    int m_lastErode;

    cv::Point m_upperLeft;
    //Roi defined around the pupil. It can be defined authomatically or using mouse events.
    cv::Rect m_userRoi;
    cv::Rect m_searchAgainRoi;
#if OSCANN == 0
    bool m_withMouse;
    unsigned int m_mouseR;
    //v1.0.8
    bool m_again;
#endif

    int m_blurImg;
    int m_blurRoi;

    int m_paddingValue;
    int m_glintsRoiPadding;
    int m_glintPadding;



    std::vector<cv::Point2f> m_glintsCentroides;
    std::vector<std::vector<cv::Point> > m_glintsContours;
    std::vector<std::vector<cv::Point> > m_possibleGlints;
    std::vector<bool > m_glintPaired;

    //v1.0.8
    float m_glintsDistance;


    std::vector<cv::Rect> m_glintsRect;


    float m_thresholdImg;
    float m_thresholdGlints;


    cv::Point2f m_lastRightGlint;
    cv::Point2f m_lastLeftGlint;
    cv::Point m_lastGlintsBR;
    cv::Point m_lastGlintsTL;
    cv::Point m_mouseGlintsTL;

    cv::Point2f m_lastPupil;


    cv::Mat m_eyeFocus;
    int m_id;
    std::string m_errorMsg;
    int m_errno;


    boost::posix_time::ptime m_startT;
    boost::posix_time::ptime m_start;
    boost::posix_time::time_duration m_dur;

    std::vector<cv::Point2f> m_edgePoints;

    cv::Rect m_bbPupil;
    cv::Mat_<float> m_PupilSobelX, m_PupilSobelY;
    cv::Mat_<uchar> m_PupilBlurred, m_PupilEdges;


    cv::Mat m_PupilLarge;
    cv::Rect m_roiPadded;



    cv::RotatedRect m_elPupilThresh;
    cv::Rect m_roiPupil;

    cv::Rect m_roiGlintsLarge;


    std::vector<cv::Point2f> m_centroidesGlintsPos;
    std::vector<std::vector<cv::Point> > m_contoursGlintsPos; //Vectores de contornos y centroides de glints posibles


    cv::Mat_<uchar> m_eye;
    cv::Mat m_eyeSmall;
    //thresholding
    bool m_found;
    int m_haarRadius;
    cv::Mat m_morphImg;

    //pupilRegion or maybe pupilROI
    std::vector<cv::Point> m_bestContour;

    //debug
    bool m_debug;

    cv::Mat m_vdoImg;
    cv::Mat m_imgMouse;
    unsigned int m_totalProcessed;
    parameters params;



    int find();
    int measure();
    // -----
    void config();
    void greyAndCrop();
    void thresholding();
    int pupilRegion();
    //int bestRegion(const cv::Mat img, const cv::Rect roiHaar);
    //void setRoi();
    int glintsDetection();
    //v1.0.9: std::vector<std::vector<cv::Point> > getValidContours(std::vector<std::vector<cv::Point> > contours);
    std::vector<std::vector<cv::Point> > getValidContours(std::vector<std::vector<cv::Point> > contours, bool restrictX=true);
    //void pupilRoiWithoutGlints();
    int starburst();
    int ellipseFitting();
    cv::Rect roiFromRectangle(const cv::Rect rectangle, const int maxWidth=640, const int maxHeight=480);
    // -----


    template<typename T>
    inline cv::Rect_<T> roiAround(const cv::Point_<T>& centre, T radius);
    inline cv::Scalar rgb(double r, double g, double b, double a = 0);
    inline void cross(cv::Mat& img, cv::Point2f centre, double radius, const cv::Scalar& colour, int thickness = 1, int lineType=cv::LINE_AA, int shift = 8);
    inline void plus(cv::Mat& img, cv::Point2f centre, double radius, const cv::Scalar& colour, int thickness = 1, int lineType=cv::LINE_AA, int shift = 8);
    inline cv::Mat& line(cv::Mat& dst, cv::Point2f from, cv::Point2f to, cv::Scalar color, int thickness=1, int linetype=cv::LINE_AA, int shift=8);
    inline cv::Rect boundingBox(const cv::Mat& img);
    inline cv::Mat resize(const cv::Mat& src, cv::Size size, int interpolation=cv::INTER_LINEAR);
    inline cv::Mat resize(const cv::Mat& src, double fx, double fy=0, int interpolation=cv::INTER_LINEAR);
    inline cv::Mat GaussianBlur(const cv::Mat& src, cv::Size ksize, double sigmax, double sigmay=0, int borderType=cv::BORDER_DEFAULT);
    inline cv::Mat GaussianBlur(cv::Mat&& src, cv::Size ksize, double sigmax, double sigmay=0, int borderType=cv::BORDER_DEFAULT);
    inline cv::Mat GaussianBlur(const cv::Mat& src, double sigmax, double sigmay=0, int borderType=cv::BORDER_DEFAULT);
    inline cv::Mat GaussianBlur(cv::Mat&& src, double sigmax, double sigmay=0, int borderType=cv::BORDER_DEFAULT);
    inline cv::Mat convert(const cv::Mat& src, int rtype, double alpha=1, double beta=0);
    inline cv::Mat cvtColor(const cv::Mat& src, int code, int dstCn=0);
    inline cv::Mat extractChannel(const cv::Mat& src, int coi);
    void getROI(const cv::Mat& src, cv::Mat& dst, const cv::Rect& roi, int borderType = cv::BORDER_REPLICATE);
    float histKmeans(const cv::Mat_<float>& hist, int bin_min, int bin_max, int K, float init_centres[], cv::Mat_<uchar>& labels, cv::TermCriteria termCriteria);
    cv::RotatedRect fitEllipse(const cv::Moments& m);
    template<typename T>
    inline T sq(T n);
    template<typename T>
    static std::vector<T> randomSubset(const std::vector<T>& src, typename std::vector<T>::size_type size);
    template<typename T>
    static std::vector<T> randomSubset(const std::vector<T>& src, typename std::vector<T>::size_type size, unsigned int seed);
    static int random(int min, int max);
    static int random(int min, int max, unsigned int seed);
    void resetBlinkVars();
    void addBlink();
    void checkFails();
protected:
    template<typename T>
    void initFromEllipse(cv::Point_<T> axis, cv::Point_<T> centre, T a, T b);
public:
    explicit OTracker();
    ~OTracker();
    int measure(cv::Mat,unsigned int blurAll=9, unsigned int blurRoi=9, float thresholdImg=0.29, float thresholdGlints=0.75, int glintsRoiPadding=10, unsigned int cannyThreshold1 = 30, unsigned int cannyThreshold2=90, float glintsDistance=10.0/*v1.0.8*/);
    //v1.0.12: #if OSCANN == 1
    #if OSCANN != 1
        //v1.0.12: int measure(cv::Mat);
    //#else
        //v1.0.12: int measure(cv::Mat,unsigned int blurAll=9, unsigned int blurRoi=9, float thresholdImg=0.29, float thresholdGlints=0.75, int glintsRoiPadding=10, unsigned int cannyThreshold1 = 30, unsigned int cannyThreshold2=90, float glintsDistance=10.0/*v1.0.8*/);
        char drawResult(unsigned int key, cv::Mat img);
        static void onMouse( int event, int x, int y, int, void* );
        void onMouse(int event, int x, int y);
        bool again(){return m_again;}
    #endif
    std::string getLastError();
    void setID(unsigned int id);
    float calcBlurriness(const cv::Mat &frame);
    cv::Point2d pupilPoint(){return m_pupil;}
    cv::RotatedRect ellipse(){return m_ellipse;}
    //1.0.8: std::pair<cv::Point2f,cv::Point2f> glints(){return std::pair<cv::Point2f,cv::Point2f>(m_leftGlint, m_rightGlint);}
    std::pair<cv::Point2d,cv::Point2d> glints(){return std::pair<cv::Point2d,cv::Point2d>(m_leftGlint, m_rightGlint);}
    std::vector<std::pair<int, int>> getBlinks();
    void clearBlinks();
    //v4.0.11:
    void isCalibration(const bool value);
};

#endif // OTRACKER_H
