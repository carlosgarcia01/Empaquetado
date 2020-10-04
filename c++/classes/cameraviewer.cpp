#include "cameraviewer.h"

/* All in microseconds
Texture -> mean:  61.341, std:   20.572
Pixmap  -> mean: 816.780, std:  254.450
%CPU(Pixmap)
30,0 bgVideoCapturer
 3,7 oscann
*/


cameraViewer::cameraViewer() : m_texture(NULL){
    qDebug() << "Entrando en el constructor de CV";
    setFlag(QQuickItem::ItemHasContents);
    m_logo = QImage(":qml/qtcam/videocapturefilter_QML/images/oscannblue.png");
    m_fromMemory = false;
    m_showPupilDetection = false;
    m_displayFreq = 0;
    setDisplayImagesFlag(false);
    setDisplayImages(true);
    m_updating = false;
    oTracker = new OTracker();
    qDebug() << "Saliendo del constructor de CV";
}

void cameraViewer::setupDbus() {
    //TODO DEBUG: dbus-monitor type='signal' | grep aura.GUIInterface
    new CVInterfaceAdaptor(this);      // ----- ----- ----- ----- ----- To emit aura.GUIInterface signals: changeSettingsDBus
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/main", this);
    connection.registerService("org.oscann.cv");


    capturerIface = new aura::CapturerInterface("org.oscann.video",               //Service Name
                                         "/capturer",                   //Path
                                         connection, //Connection
                                         this);
    connect(capturerIface, SIGNAL(newControlAddedDBus(QString, int, int, int, int)), this, SLOT(newControlAddedSlot(QString, int, int, int, int)));
    connect(capturerIface, SIGNAL(statusChangedDBus(int, int, int, int)), this, SLOT(capturerReady(int, int, int, int)));
    connect(capturerIface, SIGNAL(updateImageDBus(int, int, int, int)), this, SLOT(updateImageSlot(int, int, int, int)));


    displayCTIface = new aura::DisplayCTInterface("org.oscann.dct",
                                       "/main",
                                       QDBusConnection::sessionBus(),
                                      this);
    connect(displayCTIface, SIGNAL(stimulus2SaveDbus(int, int)), this, SLOT(stimulus2SaveSlot(int, int)));
    connect(displayCTIface, SIGNAL(stimuliOnViewerDBus(bool)), this, SLOT(stimuliOnViewerSlot(bool)));

    m_drawStimuli = false;

    m_widthFactor = (double) 640/QGuiApplication::primaryScreen()->geometry().width();
    m_heightFactor = (double) 480/QGuiApplication::primaryScreen()->geometry().height();
    qDebug()<<Q_FUNC_INFO<<" m_widthFactor: "<<m_widthFactor;
    qDebug()<<Q_FUNC_INFO<<" m_heightFactor: "<<m_heightFactor;
    m_stimulusPoint = cv::Point(QGuiApplication::primaryScreen()->geometry().width()/2*m_widthFactor, QGuiApplication::primaryScreen()->geometry().height()/2*m_heightFactor);
}

void cameraViewer::stimuliOnViewerSlot(const bool flag){
    m_drawStimuli = flag;
}
void cameraViewer::stimulus2SaveSlot(const int x, const int y){
    m_stimulusPoint = cv::Point(x*m_widthFactor, y*m_heightFactor);
}

void cameraViewer::capturerReady(const int cameraType, const int width, const int height, int fps){
    qDebug()<<Q_FUNC_INFO<<" cameraType: "<<cameraType<<" width: "<<width<<" height: "<<height<<", fps: "<<fps;
    setCameraWidth(width);
    setCameraHeight(height);
    qDebug()<<"statusChanged(cameraType, width, height); camera type:    "<<cameraType;
    emit statusChanged(cameraType, width, height);   //Send to videocapturerfilter_qml -> vidstreamproperty.onStatusChanged
    if(cameraType == -1)
        return;
    m_cameraType = cameraType;
    m_img = m_cameraType == CT.USB_20 ? QImage(QSize(640, cameraHeight()), QImage::Format_RGB888) : m_img = QImage(QSize(640, cameraHeight()), QImage::Format_Grayscale8);
    switch (fps) {
    case 30:
        m_displayConst = 1; //25FPS
        break;
    case 60:
        m_displayConst = 2; //25FPS
        break;
    case 100:
        m_displayConst = 4; //25FPS
        break;
    case 120:
        m_displayConst = 5; //24FPS
        break;
    case 240:
        m_displayConst = 10;//24FPS
        break;
    case 480:
        m_displayConst = 20;//24FPS
        break;
    case 520:
        m_displayConst = 21;//24FPS
        break;
    }
    //TODOFPS: m_img = m_img = QImage(QSize(640, cameraHeight()), QImage::Format_Grayscale8);
    mapSharedMemory();
    setDisplayImages(true);
}

void cameraViewer::changeSettings(QString ctrlName, int value){
    if(ctrlName.compare("Brightness") == 0){
        setBrtValue(value);
        emit changeSettingsDBus(value, brtCtrlId());
    }
    else if(ctrlName.compare("Gain") == 0){
        setGainValue(value);
        emit changeSettingsDBus(value, gainCtrlId());
    }
}


void cameraViewer::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry){
    m_geometryChanged = true;
    update();
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

//void cameraViewer::mapSharedMemory(const QString cameraName, const int width, const int height){
void cameraViewer::mapSharedMemory(){
    try {
        m_region = new mapped_region(new shared_memory_object(open_only, "m_shared", read_only), read_only);
    }
    catch (interprocess_exception& e) {
        qDebug()<<Q_FUNC_INFO<<"e.what: "<< e.what();
    }
}

void cameraViewer::updateImageSlot(int x, int y, int width, int height){
    try {
        if(width > 0){
            m_displayImagesFlag = true;
            m_imgPos.setX(x);
            m_imgPos.setY(y);
            m_fromMemory = true;
            update();
        }
        else{
            QTimer::singleShot(32, this, SLOT(loadLogo()));
        }
    }
    catch (interprocess_exception& e){
        qDebug()<<Q_FUNC_INFO<<"Oscann Desk 100 ERROR000: : "<<e.what();
    }
}
QSGNode *cameraViewer::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *){
    QMutexLocker lock(&m_mutex);
    Q_UNUSED(lock);
    if(m_region && m_fromMemory){
        m_displayFreq++;
        if(m_displayFreq == m_displayConst){ //240FPS
            if(m_showPupilDetection){
                m_roiImg = cv::Mat(cv::Size(640, cameraHeight()), m_cameraType == CT.USB_20 ? CV_8UC3 : CV_8UC1, m_region->get_address(), cv::Mat::AUTO_STEP);
                m_tmpImg = m_roiImg.clone();
                if(oTracker->measure(m_tmpImg) == 0){
                    cv::ellipse(m_tmpImg,oTracker->ellipse(),cv::Scalar(0,255,0));
                    cv::circle(m_tmpImg,oTracker->pupilPoint(),2,cv::Scalar(0,0,255),2);
                    cv::circle(m_tmpImg,oTracker->glints().first,2,cv::Scalar(255,0,0),2);
                    cv::circle(m_tmpImg,oTracker->glints().second,2,cv::Scalar(255,0,0),2);
                }


                m_img = QImage((const uchar *) m_tmpImg.data, m_tmpImg.cols, m_tmpImg.rows, m_tmpImg.step, m_cameraType == CT.USB_20 ? QImage::Format_RGB888 : QImage::Format_Grayscale8);
                m_img.bits();    // enforce deep copy, see documentation
                m_roiImg.release();
                m_tmpImg.release();
            }else{
                if(!m_drawStimuli){
                    m_cameraType == CT.USB_20 ? memmove(m_img.bits(), m_region->get_address(), cameraWidth()*cameraHeight()*3) : memmove(m_img.bits(), m_region->get_address(), cameraWidth()*cameraHeight());
                }else{
                    m_roiImg = cv::Mat(cv::Size(640, cameraHeight()), m_cameraType == CT.USB_20 ? CV_8UC3 : CV_8UC1, m_region->get_address(), cv::Mat::AUTO_STEP);
                    m_tmpImg = m_roiImg.clone();
                    cv::circle(m_tmpImg,m_stimulusPoint,8, m_cameraType == CT.USB_20 ? cv::Scalar(0,255,0) : cv::Scalar(255),-1,8);
                    m_img = QImage((const uchar *) m_tmpImg.data, m_tmpImg.cols, m_tmpImg.rows, m_tmpImg.step, m_cameraType == CT.USB_20 ? QImage::Format_RGB888 : QImage::Format_Grayscale8);
                }
            }
            m_displayFreq = 0;
        }else{
            m_node = static_cast<QSGSimpleTextureNode *>(oldNode);
            return m_node;
        }
    }
    m_node = static_cast<QSGSimpleTextureNode *>(oldNode);
    if (!m_node) {
        m_node = new QSGSimpleTextureNode();
    }
    if(m_texture)
        delete m_texture;
    if(m_fromMemory){
        m_texture = window()->createTextureFromImage(m_img, QQuickWindow::TextureCanUseAtlas);
    }
    else{
        m_texture = window()->createTextureFromImage(m_logo);
    }
    m_node->setTexture(m_texture);
    m_node->setRect(boundingRect());
    return m_node;
}
void cameraViewer::loadLogo(){
    m_fromMemory = false;
    m_imgPos = QPoint(0,0);
    update();
}

void cameraViewer::newControlAddedSlot(QString ctrlName,int ctrlID,int ctrlMinValue, int ctrlMaxValue, int ctrlValue){
    if(ctrlName.compare("Brightness") == 0) {
        m_brtCtrlId = ctrlID;
        m_brtMaxValue = ctrlMaxValue;
        m_brtMinValue = ctrlMinValue;
        m_brtValue = ctrlValue;
    }else if(ctrlName.compare("Gain") == 0) {
        m_gainCtrlId = ctrlID;
        m_gainMinValue = ctrlMinValue;
        m_gainMaxValue = ctrlMaxValue;
        m_gainValue = ctrlValue;
    }
}

