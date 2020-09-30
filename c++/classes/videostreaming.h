 /*
 * videostreaming.h -- preview the camera buffer
 * Copyright © 2015  e-con Systems India Pvt. Limited
 *
 * This file is part of Qtcam.
 *
 * Qtcam is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * Qtcam is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Qtcam. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef VIDEOSTREAMING_H
#define VIDEOSTREAMING_H

#include <QQuickPaintedItem>
#include <QPixmap>
#include <QGuiApplication>
#include <QScreen>
#include <QMessageBox>
#include <usbdev.h>

#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
//DBus
#include "oscann_adaptor.h"
#include "oscann_interface.h"

#include <QDBusConnection>

//openCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/opencv.hpp"

#include "utilsprocess.h"
#include "qutils.h"

using namespace std;
using namespace boost::interprocess;


#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/exception/exception.hpp>

#include <iostream>
#include <fstream>



#define ESC 0
#define NO 1


class clbtstItem{
public:
    clbtstItem(){}
    ~clbtstItem(){}
    int task(){return m_task;}
    int numberOfPts(){return m_numberOfPts;}
    double deg2Px(){return m_deg2px;}
    double sDist(){return m_sDist;}
    double sWidth(){return m_sWidth;}
    QPoint resolution(){return m_resolution;}
    int stmSize(){return m_stmSize;}
    int clb(){return m_clb;}
    int tst(){return m_tst;}
    int variant(){return m_variant;}
    int time(){return m_time;}
    int laps(){return m_laps;}
    int frequency(){return m_frequency;}
    QString imgName(){return m_imgName;}
    QString directoryName(){return m_directoryName;}
    QString prefix(){return m_prefix;}
    QString session(){return m_session;}

    void setTask(const int value){m_task = value;}
    void setNumberOfPts(const int value){m_numberOfPts = value;}
    void setDeg2Px(const double value){m_deg2px = value;}
    void setSDist(const double value){m_sDist = value;}
    void setSWidth(const double value){m_sWidth = value;}
    void setResolution(const QPoint value){m_resolution = value;}
    void setStmSize(const int value){m_stmSize = value;}
    void setClb(const int value){m_clb = value;}
    void setTst(const int value){m_tst = value;}
    void setVariant(const int value){m_variant = value;}
    void setTime(const int value){m_time = value;}
    void setLaps(const int value){m_laps = value;}
    void setFrequency(const int value){m_frequency = value;}
    void setImgName(const QString value){m_imgName = value;}
    void setDirectoryName(const QString value){m_directoryName = value;}
    void setPrefix(const QString value){m_prefix = value;}
    void setSession(const QString value){m_session = value;}
private:
    int m_task;
    int m_numberOfPts;
    double m_deg2px;
    double m_sDist,m_sWidth;
    QPoint m_resolution;
    int m_stmSize;
    int m_clb;
    int m_tst;
    int m_variant;
    int m_time;
    int m_laps;
    int m_frequency;
    QString m_imgName;
    QString m_directoryName;
    QString m_prefix;
    QString m_session;
};


//class Videostreaming : public QGLWidget, public v4l2 -> Cannot assign object to property
//class Videostreaming : public QQuickPaintedItem {
class Videostreaming : public QObject{
    Q_OBJECT
    Q_PROPERTY(bool killbgPupilDetectorFlag READ killbgPupilDetectorFlag WRITE setKillbgPupilDetectorFlag NOTIFY killbgPupilDetectorFlagChanged)
    Q_PROPERTY(double monitorDistance READ monitorDistance WRITE setMonitorDistance NOTIFY monitorDistanceChange)
    Q_PROPERTY(double monitorWidth READ monitorWidth WRITE setMonitorWidth NOTIFY monitorWidthChange)
    Q_PROPERTY(double degreeRatio READ degreeRatio WRITE setDegreeRatio NOTIFY degreeRatioChange)
    Q_PROPERTY(int validationPtos MEMBER m_validationPts)
    Q_PROPERTY(bool validating MEMBER m_validating)
    Q_PROPERTY(bool onClb MEMBER m_onClb)
    Q_PROPERTY(int frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged)
    Q_PROPERTY(int laps READ laps WRITE setLaps NOTIFY lapsChanged)
    Q_PROPERTY(bool clb READ clb WRITE setClb NOTIFY clbChanged)
    Q_PROPERTY(QString tableTitle READ tableTitle WRITE setTableTitle NOTIFY tableTitleChanged)
public:
    typedef std::chrono::milliseconds Interval;
    Videostreaming();
    ~Videostreaming();
    aura::CapturerInterface *capturerIface;
    aura::DisplayCTInterface *displayCTIface;
    aura::WriterInterface *writerIface;
    //aura::CapturerInterface *capturerIface;

    static QStringListModel modelCam;
    bool killbgPupilDetectorFlag(){return m_killbgPupilDetectorFlag;}
    double monitorDistance(){return m_monitorDistance;}
    double monitorWidth(){return m_monitorWidth;}
    double degreeRatio(){return m_degreeRatio;}
    int frequency(){return m_frequency;}
    int laps(){return m_laps;}
    bool clb(){return m_isClb;}
    QString tableTitle(){return m_tableTitle;}
    void killDisplayCT();
    int getCameraType(){return m_cameraType;}

    char memoryName[255];
    QString linuxCommand;

    QString dataFileName;
    QString m_d1FileName;

    //E171120161634
    int m_freq;


    qint64 fileInc;


    bool m_validating;

    unsigned int m_nosm;    //Number Of Saccadic movements

private:

    QString m_mongoUrl;
    unsigned int m_mongoPort;


    bool m_startTimer;

    mongocxx::database m_db;

    cameraType CT;


    int m_cameraType;

    QRect m_imgSize;


    QFile *m_xmlFileName;
    QXmlStreamWriter *m_xmlWriter;
    QXmlStreamReader *m_xmlReader;


    unsigned int m_xmlIndex;

    int m_prevTask;

    bool m_isClb;
    bool m_onClb;

    unsigned int m_totalFramesToProcess;
    unsigned int m_totalProcessed;

    QPoint m_imgPos;



    QVector<QString> m_vector2Process;
    int m_frequency;
    int m_laps;
    QString m_tableTitle;


    const char *m_buffers;



    //Monitor
    double m_monitorDistance;
    double m_monitorWidth;
    double m_degreeRatio;




    int m_validationPts;

    bool m_offline;

    double progressPercent;

    OTimer *m_testTimer;

    unsigned int m_testProgress;
    QString m_directoryName;
    QString directoryName; //Paso de char [255] a QString

    aura::DetectorInterface *detectorIface;

    bool m_killbgPupilDetectorFlag;
    int numberOfFrames;


    void setMonitorWidth(const double newValue){m_monitorWidth = newValue;      emit monitorWidthChange();   }
    void setDegreeRatio(const double newValue){ m_degreeRatio = newValue;       emit degreeRatioChange();    }
    void setMonitorDistance(const double newValue){ m_monitorDistance = newValue;   emit monitorDistanceChange();   }


    void setKillbgPupilDetectorFlag(const bool newValue){m_killbgPupilDetectorFlag = newValue; emit killbgPupilDetectorFlagChanged();}


    void setFrequency(const int value){
        m_frequency = value;
        emit frequencyChanged();
        emit frequencyDbus(m_frequency);
    }
    void setTableTitle(const QString title){
        m_tableTitle = title;
        emit tableTitleChanged();

    }
    void setLaps(const int value){
        m_laps = value;
        emit lapsChanged();
        emit lapsDbus(m_laps);
    }
    void setClb(const bool value){m_isClb = value;}
    void createTimer();
    Interval m_timeInterval;


    boost::posix_time::ptime m_start;
public slots:
    void setup(unsigned int fps);
    void serviceSlot(const unsigned int type, const QString name, const bool run, const QString cores, const unsigned int fps);
    void validateSlot();
    void start_bgPupilDetection(unsigned int fps);
    void setupDbus();
    QString createFileSystem(const QString, const QString, const QString, const QString);
    void callOffline(int freq, unsigned int fps);
    QStringList processQueue();
    int processQueueAdd();
    int queueLength();
    void stop();
    void processReady();
    bool checkCameraIni(QString path){return QFile(path+QString("/camera.ini")).exists();}
    void setDirectoryName(QString value);
    void setTotalFramesToProcess(const unsigned int value );
    //void deleteFilesSlot(const int);
    void deleteFilesSlot();
    void destruir();
    void killbgPupilDetector();
    void normalStateSlot();
    double getProcessingProgress();
    QString returnDefaultDir();
    void openPatientDataFile(QString);
    void configPatientDataTemplate();
    void clrVector2Process(){m_vector2Process.clear();}
    void sendMessageToServer(const QString sessionName);
    Q_INVOKABLE void setM_offline(bool value){this->m_offline = value;}

    QStringList searchLists(){
        QDirIterator mainFolder(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0], QStringList() << "tln*.xml", QDir::Files);
        QStringList list;
        QString name;
        while(mainFolder.hasNext()){
            name = mainFolder.next();
            name = name.split("tln")[1];
            name = name.split(".")[0];
            list.push_back(name);
        }
        return list;
    }

    void setMongoInfo(const QString url, const unsigned int port){
        m_mongoUrl = url;
        m_mongoPort = port;
    }


    QStringList dbCollections(){
        QStringList list;
        mongocxx::client client(mongocxx::uri(QString("mongodb://oscann:CuevaErikSilviaPablo@%1:%2/?authSource=admin&authMechanism=SCRAM-SHA-1").arg(m_mongoUrl).arg(m_mongoPort).toLatin1().data()));
        m_db = client["datos"];
        try{
            auto cursor1 = m_db.list_collections();
            for (const bsoncxx::document::view& doc : cursor1){
                if(     doc["name"].get_utf8().value.to_string().compare("Atrofia Cortical") != 0 &&
                        doc["name"].get_utf8().value.to_string().compare("APP") != 0 &&
                        doc["name"].get_utf8().value.to_string().compare("EGeneralizada") != 0 &&
                        doc["name"].get_utf8().value.to_string().compare("EFocal") != 0){
                    list.push_back(doc["name"].get_utf8().value.to_string().c_str());
                }
            }
        }catch (mongocxx::exception &e) {
            std::cerr << "MONGO ERROR: "<<e.what()<<"\n";
        }
        return list;
    }





    bool deleteXml(QString listName){
        QString fileName = QString("%1/tln%2.xml").arg(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).arg(listName);
        QFile file (fileName);
        qDebug()<<Q_FUNC_INFO<<" -> fileName: "<<fileName;
        file.remove();
    }
    bool openXmlReader(QString listName){
        QString fileName = QString("%1/tln%2.xml").arg(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).arg(listName);
        if(!QDir(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).exists())
            QDir().mkpath(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]);
        m_xmlFileName = new QFile(fileName);
        if(m_xmlFileName->open(QIODevice::ReadOnly)){
            m_xmlReader = new QXmlStreamReader(m_xmlFileName);
            return true;
        }
        return false;
    }
    void readXmlElements(){
        QString testType;
        QString testTypeCode;
        QString variant;
        QString variantCode;
        QString points;
        QString random;
        QString ptsCode;
        QString stmTime;
        QString testDuration;
        QString laps;
        QString frequency;
        QString prefix;
        while(m_xmlReader->readNextStartElement()){
            if(m_xmlReader->name() == "Test"){
                while(m_xmlReader->readNextStartElement()){
                    if(m_xmlReader->name() == "testType"){
                        testType = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "testTypeCode"){
                        testTypeCode = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "variant"){
                        variant = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "variantCode"){
                        variantCode = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "points"){
                        points = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "random"){
                        random = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "ptsCode"){
                        ptsCode = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "stmTime"){
                        stmTime = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "testDuration"){
                        testDuration = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "laps"){
                        laps = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "frequency"){
                        frequency = m_xmlReader->readElementText();
                    }
                    else if(m_xmlReader->name() == "prefix"){
                        prefix = m_xmlReader->readElementText();
                    }
                }
                emit addXmlItem(testType,
                        testTypeCode,
                        variant,
                        variantCode,
                        points,
                        random,
                        ptsCode,
                        stmTime,
                        testDuration,
                        laps,
                        frequency,
                        prefix);


            }
        }
        m_xmlFileName->close();
    }
    bool xmlExists(QString listName){
        return QFile(QString("%1/tln%2.xml").arg(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).arg(listName)).exists();
    }

    bool openXmlWriter(QString listName){
        //QString fileName = QString("%1/%2").arg(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).arg("lists.xml");
        QString fileName = QString("%1/tln%2.xml").arg(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).arg(listName);
        qDebug()<<Q_FUNC_INFO<<" ----- ----- ----- ---- ----- ------ ------ ------ fileName: "<<fileName;
        if(!QDir(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).exists())
            QDir().mkpath(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]);
        m_xmlFileName = new QFile(fileName);
        // INFO: case sensitive
        qDebug()<<Q_FUNC_INFO<<" ----- ----- ----- ---- ----- ------ ------ ------ exists: "<<m_xmlFileName->exists();
        if(m_xmlFileName->open(QIODevice::WriteOnly)){
            m_xmlWriter = new QXmlStreamWriter(m_xmlFileName);
            m_xmlWriter->setAutoFormatting(true);
            m_xmlWriter->writeStartDocument();
            m_xmlWriter->writeStartElement("Set");
            m_xmlIndex = 0;
            return true;
        }
        return false;
    }
    void xmlAddElement(const QString testType
                    ,const QString testTypeCode
                    ,const QString variant
                    ,const QString variantCode
                    ,const QString points
                    ,const QString random
                    ,const QString ptsCode
                    ,const QString stmTime
                    ,const QString testDuration
                    ,const QString laps
                    ,const QString frequency
                    ,const QString prefix){
        m_xmlWriter->writeStartElement("Test");
        m_xmlWriter->writeAttribute("id", QString::number(m_xmlIndex));
        m_xmlWriter->writeTextElement("testType", testType);
        m_xmlWriter->writeTextElement("testTypeCode", testTypeCode);
        m_xmlWriter->writeTextElement("variant", variant);
        m_xmlWriter->writeTextElement("variantCode", variantCode);
        m_xmlWriter->writeTextElement("points", points);
        m_xmlWriter->writeTextElement("random", random);
        m_xmlWriter->writeTextElement("ptsCode", ptsCode);
        m_xmlWriter->writeTextElement("stmTime", stmTime);
        m_xmlWriter->writeTextElement("testDuration", testDuration);
        m_xmlWriter->writeTextElement("laps", laps);
        m_xmlWriter->writeTextElement("frequency", frequency);
        m_xmlWriter->writeTextElement("prefix", prefix);
        m_xmlWriter->writeEndElement(); // Test
        m_xmlIndex++;
    }
    void closeXmlWriter(){
        m_xmlWriter->writeEndElement(); // Set
        m_xmlWriter->writeEndDocument();
        m_xmlFileName->close();
    }

    void print(){
    }
    void updateTestProgressSlot();
    void finishDemoSlot();
    /*
        This method starts a session. One session always includes >one< calibration and can includes non or several test
    */
    void startCalibration(unsigned int fps){
        qDebug() << Q_FUNC_INFO;
        m_validating = true;
        m_offline = false;
        start_bgPupilDetection(fps);               //Lanzar el plugin de deteccion de pupila
        m_killbgPupilDetectorFlag = true;       //Indicar que se debe cerrar al acabar el procesado
        m_onClb = true;
    }
//AQUI: validar que la lista de tareas tiene clb test* clb test* clb test*
    bool validateTaskList(const QString value){
        //QRegExp mailREX("0[0-1]{1,5}");OK
        QRegExp mailREX("(0[0-1]{0,4})+");  //RULE: Mandatory one calibration before a maximum of four tests
        mailREX.setPatternSyntax(QRegExp::RegExp);
        return mailREX.exactMatch(value);
        //qDebug() << mailREX.exactMatch("011");  //TRUE
        //qDebug() << mailREX.exactMatch("111");
        //qDebug() << mailREX.exactMatch("1");
        //qDebug() << mailREX.exactMatch("000");//TRUE
        //qDebug() << mailREX.exactMatch("0101010101");  //TRUE
        //qDebug() << mailREX.exactMatch("011011011011011");  //TRUE
        //qDebug() << mailREX.exactMatch("010100011101");  //TRUE
        //qDebug() << mailREX.exactMatch("10100011101");  //FALSE
    }


    //TODO: Call emitDbusConfig from qml using modelLibrary and sending parameters
    void emitDbusConfig(const int task
                        ,const int numberOfPts
                        ,const int screenDistance
                        ,const int screenWidth
                        ,const QPoint resolution
                        ,const int stmSize
                        ,const int clb
                        ,const int tst
                        ,const int variant
                        ,const int time
                        ,const int laps
                        ,const int frequency
                        ,const QString imgName
                        ,const QString prefix
                        ,const QString directoryName
                        ,const bool fromRun
                        ,const QString codec
                        ,const QString extension
                        ){
    m_isClb = task == 0;
    QString fullDirectoryName;
    if(fromRun)
        fullDirectoryName = createFileSystem(prefix, directoryName, codec, extension);
    emit configDbus(task,
                        numberOfPts,
                        screenDistance,
                        screenWidth,
                        resolution.x(),
                        resolution.y(),
                        stmSize,
                        clb,
                        tst,
                        variant,
                        time,
                        laps,
                        frequency,
                        imgName,
                        fullDirectoryName,
                        fromRun);
    }

    void nextClbTst(){    //Signal from displayCT(Dbus) and QML (from video Corrupted L192 (videocapturerfilter_qml.qml))
        qDebug()<<"ENTRA EN ESTA FUNCION RARA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<Q_FUNC_INFO;
        emit nextTest();                         //Signal to QML: videostreamingproperty onNextTest
        if(m_testTimer && !m_isClb){
            if(m_testTimer->isActive()){
                emit testProgress(m_testProgress = 101, Q_FUNC_INFO);
                m_testTimer->stop();
                m_startTimer = true;
                qDebug()<<Q_FUNC_INFO<<" ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### m_startTimer: "<<m_startTimer;
            }
        }
    }
    void keyHandler(const int key, const bool fromRun);
    void pendingEvents(){QCoreApplication::processEvents();}

Q_SIGNALS:
    void saveImagesDbus(bool);
    void newSettingsDBus(QString name, QString dataFile, bool isTst, QString codec);
    void newD1FileDBus(QString dataFile);
    void configTrackerDBus(int width, int height);
    void sharedMemoryDbus();
    void normalStateDbus();
    void closeVideo();
    void shutdownDBus(unsigned int type);
    void processDBus(QString folder, int freq, int width, int height, unsigned int totalFramesToProcess);
    void stopDBus();
    void config(int rmin, int rmax, double cannyBlur, double cannyThld1, double cannyThld2, int StarburstPoints, bool online);
    void configDbus(const int task, const int numberOfPoints, const double sDist, const double sWidth, const int resolutionX, const int resolutionY, const int stimulusSize, const int clb, const int tst, const int variant, const int time, const int laps, const int frequency, const QString imgName, const QString directoryName, const bool fromRun);
    void keyPressedDbus(const int key);
    void frequencyDbus(const int value);
    void lapsDbus(const int value);
    void validate();

public Q_SLOTS:
    void methodName();
    void processingProgress(double porcent, double totalPercent);
    void testDurationSlot(unsigned int time);
    void capturerReady(int, int, int, int);


signals:
    void clbFinished();
    void nextTest();
    void defaultOutputFormat(unsigned int formatIndexValue);
    void processed(double percent, double totalPercent);
    void testProgress(unsigned int progress, QString from );
    void finishDemo();
    void calibration();
    void calibrationChange();
    void killbgPupilDetectorFlagChanged();


    void frequencyChanged();
    void lapsChanged();
    void clbChanged();
    void tableTitleChanged();

    void monitorDistanceChange();
    void monitorWidthChange();
    void degreeRatioChange();

    void corruptVideo();


    void addXmlItem(const QString testType
                    ,const QString testTypeCode
                    ,const QString variant
                    ,const QString variantCode
                    ,const QString points
                    ,const QString random
                    ,const QString ptsCode
                    ,const QString stmTime
                    ,const QString testDuration
                    ,const QString laps
                    ,const QString frequency
                    ,const QString prefix);
};
#endif // VIDEOSTREAMING_H
