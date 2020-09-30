#ifndef CAMERAVIEWER_H
#define CAMERAVIEWER_H


#include <QQuickItem>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>


//#include <QQuickPaintedItem>
//#include <QPen>
//#include <QPainter>



#include <QtCore/QMutexLocker>

//DBus
#include "oscann_adaptor.h"
#include "oscann_interface.h"
#include <QDBusConnection>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

//openCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/opencv.hpp"

#include "qutils.h"
#include "otracker.h"


using namespace boost::interprocess;
class cameraViewer  : public QQuickItem{
//class cameraViewer : public QQuickPaintedItem{
    Q_OBJECT
    Q_PROPERTY(int cameraWidth READ cameraWidth WRITE setCameraWidth NOTIFY cameraWidthChanged)
    Q_PROPERTY(int cameraHeight READ cameraHeight WRITE setCameraHeight NOTIFY cameraHeightChanged)
    //Camera: brt: brightness, exp: exposure
    //Q_PROPERTY(QString cameraName READ cameraName WRITE setCameraName NOTIFY cameraNameChange)
    Q_PROPERTY(int brtCtrlId READ brtCtrlId WRITE setBrtCtrlId)
    Q_PROPERTY(int brtMaxValue READ brtMaxValue WRITE setBrtMaxValue NOTIFY brtMaxValueChange)
    Q_PROPERTY(int brtMinValue READ brtMinValue WRITE setBrtMinValue NOTIFY brtMinValueChange)
    Q_PROPERTY(int brtValue READ brtValue WRITE setBrtValue NOTIFY brtValueChange)

    /*Q_PROPERTY(int expCtrlId READ expCtrlId WRITE setExpCtrlId)
    Q_PROPERTY(int expMaxValue READ expMaxValue WRITE setExpMaxValue NOTIFY expMaxValueChange)
    Q_PROPERTY(int expMinValue READ expMinValue WRITE setExpMinValue NOTIFY expMinValueChange)
    Q_PROPERTY(int expValue READ expValue WRITE setExpValue NOTIFY expValueChange)*/

    Q_PROPERTY(int gainCtrlId READ gainCtrlId WRITE setGainCtrlId)
    Q_PROPERTY(int gainMaxValue READ gainMaxValue WRITE setGainMaxValue NOTIFY gainMaxValueChanged)
    Q_PROPERTY(int gainMinValue READ gainMinValue WRITE setGainMinValue NOTIFY gainMinValueChanged)
    Q_PROPERTY(int gainValue READ gainValue WRITE setGainValue NOTIFY gainValueChanged)

    Q_PROPERTY(bool displayImagesFlag READ displayImagesFlag WRITE setDisplayImagesFlag NOTIFY displayImagesFlagChanged)


    public:
    //explicit cameraViewer(QWidget *parent = 0);
    cameraViewer();

    int cameraWidth(){return m_cameraWidth;}
    int cameraHeight(){return m_cameraHeight;}

    //Camera
    int brtCtrlId(){return m_brtCtrlId;}
    //int expCtrlId(){return m_expCtrlId;}
    int gainCtrlId(){return m_gainCtrlId;}
    int brtMaxValue(){return m_brtMaxValue;}
    //int expMaxValue(){return m_expMaxValue;}
    int gainMaxValue(){return m_gainMaxValue;}
    int brtMinValue(){return m_brtMinValue;}
    //int expMinValue(){return m_expMinValue;}
    int gainMinValue(){return m_gainMinValue;}
    //QString cameraName(){return m_cameraName;}
    int brtValue(){return m_brtValue;}
    //int expValue(){return m_expValue;}
    int gainValue(){return m_gainValue;}

    bool displayImagesFlag(){return m_displayImagesFlag;}


//protected:
//    void paint(QPainter *painter);

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

private:
    OTracker *oTracker;

    bool m_drawStimuli;

    cv::Point m_stimulusPoint;
    float m_widthFactor;
    float m_heightFactor;

    cameraType CT;


    bool m_updating;
    bool m_displayImagesFlag;

    cv::Mat m_roiImg;
    cv::Mat m_tmpImg;
    unsigned int m_displayFreq;
    unsigned int m_displayConst;


    bool m_fromMemory;
    bool m_geometryChanged;
    QImage m_img;
    QImage m_logo;
    uchar *m_data;
    aura::CapturerInterface *capturerIface;
    aura::DisplayCTInterface *displayCTIface;

    mapped_region *m_region;
    QPoint m_imgPos;
    QMutex m_mutex;
    QSGSimpleTextureNode *m_node;
    QSGTexture *m_texture;

    boost::posix_time::ptime m_start;
    boost::posix_time::time_duration m_dur;

    //camera size
    int m_cameraWidth;
    int m_cameraHeight;

    //Camera
    //QString m_cameraName;
    int m_cameraType;
    int m_brtCtrlId;
    int m_brtMaxValue;
    int m_brtMinValue;
    int m_brtValue;

    //int m_expCtrlId;
    //int m_expMaxValue;
    //int m_expMinValue;
    //int m_expValue;
    int m_gainCtrlId;
    int m_gainMaxValue;
    int m_gainMinValue;
    int m_gainValue;



    void setCameraWidth(const int newValue){m_cameraWidth = newValue;       emit cameraWidthChanged();   /*emit cameraWDbus(newValue);TODO: ?????*/}
    void setCameraHeight(const int newValue){m_cameraHeight = newValue;       emit cameraHeightChanged();   /*emit cameraHDbus(newValue);TODO: ?????*/}



    //Camera
    //void setCameraName(const QString newValue){m_cameraName = newValue; emit cameraNameChange();}
    void setBrtCtrlId(const int newValue){m_brtCtrlId = newValue;}
    //void setExpCtrlId(const int newValue){m_expCtrlId = newValue;}
    void setGainCtrlId(const int newValue){m_gainCtrlId = newValue;}
    void setBrtMaxValue(const int newValue){m_brtMaxValue = newValue; emit brtMaxValueChange();}
    //void setExpMaxValue(const int newValue){m_expMaxValue = newValue; emit expMaxValueChange();}
    void setGainMaxValue(const int newValue){m_gainMaxValue = newValue; emit gainMaxValueChanged();}
    void setBrtMinValue(const int newValue){m_brtMinValue = newValue; emit brtMinValueChange();}
    //void setExpMinValue(const int newValue){m_expMinValue = newValue; emit expMinValueChange();}
    void setGainMinValue(const int newValue){m_gainMinValue = newValue; emit gainMinValueChanged();}
    void setBrtValue(const int newValue){m_brtValue = newValue; emit brtValueChange();}
    //void setExpValue(const int newValue){m_expValue = newValue;emit expValueChange();}
    void setGainValue(const int newValue){m_gainValue = newValue;emit gainValueChanged();}

    void setDisplayImagesFlag(const bool newValue){m_displayImagesFlag = newValue; emit displayImagesFlagChanged();emit displayImagesDbus(newValue);}


    bool m_showPupilDetection;

public slots:
    void updateImageSlot(int x, int y, int width, int height);
    //void mapSharedMemory(const QString cameraName, const int width, const int height);
    void mapSharedMemory();
    //void capturerReady(int cameraName, int width, int height);
    void capturerReady(int cameraName, int width, int height, int fps);
    void setupDbus();
    void loadLogo();
    void newControlAddedSlot(QString,int,int,int, int);
    //void updateHeaderSlot(QString value){m_header = value;}
    void changeSettings(QString ctrlName, int value);
    void setShowPupilDetection(bool value){m_showPupilDetection = value;}
    void setDisplayImages(bool value){m_displayImagesFlag = value; emit displayImagesFlagChanged();emit displayImagesDbus(value);}
    void setProcessing(bool value){emit processingDbus(value);}
    void stimulus2SaveSlot(const int x, const int y);
    void stimuliOnViewerSlot(const bool flag);

signals:
    //Nunca se emite
    //void removeRect(bool rectVisibility);
    //void statusChanged(QString cameraName, int s_width, int s_height);
    void statusChanged(int cameraType, int s_width, int s_height);
    //void defaultFrameSize(unsigned int outputIndexValue, unsigned int  defaultWidth, unsigned int defaultHeight);
    void cameraWidthChanged();
    void cameraHeightChanged();
    void brtMaxValueChange();
    void brtMinValueChange();
    void brtValueChange();
    //void expMaxValueChange();
    //void expMinValueChange();
    //void expValueChange();
    void gainMaxValueChanged();
    void gainMinValueChanged();
    void gainValueChanged();
    //Camera
    void cameraNameChange();
    void displayImagesFlagChanged();


Q_SIGNALS:

    void changeSettingsDBus(int value, int id);
    void displayImagesDbus(bool value);
    void processingDbus(bool value);


};

#endif // CAMERAVIEWER_H
