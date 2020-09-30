#include "videostreaming.h"
#include <QtCore/QCoreApplication>
#include <QtGui/QGuiApplication>
#include <QtWidgets>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QLabel>
#include <QMessageBox>
#include <QRectF>
#include <fcntl.h>

QStringListModel Videostreaming::modelCam;

#define CLEAR(x) memset(&(x), 0, sizeof(x))

/* Jpeg-decode */
#define HEADERFRAME1 0xaf

#ifndef min
 #define min(a,b) ((a)<(b)?(a):(b))
#endif

Videostreaming::~Videostreaming(){}

Videostreaming::Videostreaming(){
    numberOfFrames = 0;
    fileInc = 0;
    m_killbgPupilDetectorFlag = false;
    m_validationPts = 3; //Se procesa en la validacion 1 de cada m_val... imagenes
    m_validating = false;
    setFrequency(8); //Cambio de -1 a 8. No debería iniciarse en 8?
    setLaps(3); //Inicializar la variable de Laps
    setTableTitle("Task List");
    //m_testTimer = new OTimer(this);
    //connect(m_testTimer, SIGNAL(timeoutSignal()), this, SLOT(updateTestProgressSlot()));
    //createTimer();
    mongocxx::instance instance{}; // This should be done only once.
    m_testTimer = NULL;
    m_startTimer = true;
}
void Videostreaming::createTimer(){
    m_testTimer = new OTimer(this);
    connect(m_testTimer, SIGNAL(timeoutSignal()), this, SLOT(updateTestProgressSlot()));
    m_testTimer->start(m_timeInterval);
}
void Videostreaming::setupDbus() {
    //TODO DEBUG: dbus-monitor type='signal' | grep aura.GUIInterface
    new GUIInterfaceAdaptor(this);      // ----- ----- ----- ----- ----- To emit aura.GUIInterface signals: shutdownDBus
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerService("org.oscann.gui");
    connection.registerObject("/gui", this);
    displayCTIface = new aura::DisplayCTInterface("org.oscann.dct",
                                       "/main",
                                       QDBusConnection::sessionBus(),
                                      this);
    //connect(displayCTIface, SIGNAL(deleteFilesDbus(int)), this, SLOT(deleteFilesSlot(int)));
    connect(displayCTIface, SIGNAL(deleteFilesDbus()), this, SLOT(deleteFilesSlot()));
    connect(displayCTIface, SIGNAL(validateDBus()), this, SLOT(validateSlot()));
    connect(displayCTIface, SIGNAL(testDurationDBus(unsigned int)), this, SLOT(testDurationSlot(unsigned int)));
    connect(displayCTIface, SIGNAL(finishDemoDbus()), this, SLOT(finishDemoSlot()));
    detectorIface = new aura::DetectorInterface("aura.oscann.pupil", "/Detector", QDBusConnection::sessionBus(), this);
    connect(detectorIface, SIGNAL(progressDBus(double, double)), this, SLOT(processingProgress(double, double)));
    connect(detectorIface, SIGNAL(ready()), this, SLOT(processReady()));

    writerIface = new aura::WriterInterface("org.oscann.writer",
                                       "/main",
                                       QDBusConnection::sessionBus(),
                                      this);
    connect(writerIface, SIGNAL(nextTestDbus()), this, SLOT(nextClbTst()));
    capturerIface = new aura::CapturerInterface("org.oscann.video",
                                           "/capturer",
                                           QDBusConnection::sessionBus(),
                                                this);
    connect(capturerIface, SIGNAL(statusChangedDBus(int, int, int, int)), this, SLOT(capturerReady(int, int, int, int)));
}


void Videostreaming::capturerReady(const int cameraType, const int width, const int height, int fps){
    qDebug() << "Entrando en Videostreaming::capturerReady con las variables: " << cameraType << ", " << width << ", " << height << ", " << fps;
    Q_UNUSED(width);
    Q_UNUSED(height);
    Q_UNUSED(fps);
    if(cameraType == -1)
        return;
    m_cameraType = cameraType;
    qDebug()<<Q_FUNC_INFO<<" +++++ +++++ +++++ +++++ +++++ +++++ +++++ +++++  m_cameraType: "<<m_cameraType;
}



void Videostreaming::processingProgress(double percent, double totalPercent){
    emit processed(percent, totalPercent);
}
void Videostreaming::testDurationSlot(unsigned int time){
    m_timeInterval = std::chrono::milliseconds(time/100);
    if(!m_isClb){
        m_testProgress = 0;
        emit testProgress(m_testProgress, Q_FUNC_INFO);
    }
}

void Videostreaming::finishDemoSlot(){
    normalStateSlot();
    emit finishDemo();
}
void Videostreaming::updateTestProgressSlot(){
    if(!m_isClb){
        emit testProgress(m_testProgress++, Q_FUNC_INFO);
    }
}

double Videostreaming::getProcessingProgress(){
    return progressPercent;
}

QString Videostreaming::createFileSystem(const QString prefix, const QString sessionName, const QString codec, const QString extension){
    QString currentDate = QDateTime::currentDateTime().toString("-MMddyyyy-hhmmss");        //Use dash to create a separation, easier to read
    QString filename=  prefix+currentDate;
    m_directoryName=sessionName+"/"+filename;
    linuxCommand="mkdir -p \""+m_directoryName+"/raw\" ";
    system(linuxCommand.toLatin1().data());
    m_d1FileName=m_directoryName+"/."+filename;
    //TODO:
    //This signal is used by writer which opens D1.dat
    //Use another signal for pupil to create D1.dat
    // ONLY 1. pupilDetection
    //      2. onCalibration
    //      3. IMPORTANT: CLOSE IT ¿When or where?
    emit newSettingsDBus(m_directoryName, m_d1FileName, !m_isClb, codec);
    emit sharedMemoryDbus();
    dataFileName=m_directoryName+"/camera.ini";
    QSettings *cameraSettings = new QSettings(dataFileName, QSettings::IniFormat);
    cameraSettings->setValue("image/width", m_imgSize.width());
    cameraSettings->setValue("image/height", m_imgSize.height());
    //TODOFPSCRITICAL:
    cameraSettings->setValue("image/size", m_imgSize.width()*m_imgSize.height()*3);
    //cameraSettings->setValue("image/size", m_imgSize.width()*m_imgSize.height());
    cameraSettings->setValue("screenWidth", QApplication::desktop()->screenGeometry().width());
    cameraSettings->setValue("screenHeight", QApplication::desktop()->screenGeometry().height());
    cameraSettings->setValue("monitorDistance",m_monitorDistance);
    cameraSettings->setValue("monitorWidth",m_monitorWidth);
    cameraSettings->setValue("degreeRatio",m_degreeRatio);
    qDebug()<<QString("%1%2 = [").arg(prefix).arg(codec).toLatin1().data();
    return m_directoryName;
}


void Videostreaming::sendMessageToServer(const QString sessionName){
    mongocxx::client client(mongocxx::uri(QString("mongodb://oscann:CuevaErikSilviaPablo@%1:%2/?authSource=admin&authMechanism=SCRAM-SHA-1").arg(m_mongoUrl).arg(m_mongoPort).toLatin1().data()));
    m_db = client["hist"];
    QString currentDate = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    qDebug()<<Q_FUNC_INFO<<" ====== ====== ====== ====== ====== ====== ====== ====== ====== ====== ====== "<< getenv("AURAID")<<", currentDate: "<<currentDate;
    try{
        mongocxx::collection coll = m_db[getenv("AURAID")];
        auto builder = bsoncxx::builder::stream::document{};
        bsoncxx::document::value doc_value = builder
                << "ID" << getenv("AURAID")
                << "Date" << currentDate.toLatin1().data()
                << "Patient" << sessionName.toLatin1().data()
                << bsoncxx::builder::stream::finalize;
        bsoncxx::document::view view = doc_value.view();
        bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
        coll.insert_one(view);
    }catch (mongocxx::exception &e) {
        std::cerr << "MONGO ERROR: "<<e.what()<<"\n";
    }
}

void Videostreaming::deleteFilesSlot(){
    linuxCommand="rm -rf \""+m_directoryName+"\" &";
    system(linuxCommand.toLatin1().data());
}

void Videostreaming::destruir(){
    if(memoryName){
        shared_memory_object::remove(memoryName);
    }
    emit shutdownDBus(99);
}

void Videostreaming::serviceSlot(const unsigned int type, const QString name, const bool run, const QString cores, const unsigned int fps){
    if(run){
        if(!name.compare("bgImageWriter")){
            system(QString("./%2 0 %3 &").arg(name).arg(fps).toLatin1().data());
            system(QString("./%2 1 %3 &").arg(name).arg(fps).toLatin1().data());
            //system(QString("gdb -ex run ./%2 &").arg(name).toLatin1().data());
        }else{
            system(QString("./%2 %3 &").arg(name).arg(fps).toLatin1().data());
        }
    }else{
        emit shutdownDBus(type);
    }
}
void Videostreaming::validateSlot(){
    if(m_validating){
        emit validate();
    }
}




void Videostreaming::setup(unsigned int fps) {
    //Check if bgImageWriter exists before loading it (To show an error)
    QDir runPath = QDir::currentPath();
    QStringList nameFilter;
    nameFilter << "bgImageWriter";
    QFileInfoList pluginList = runPath.entryInfoList( nameFilter,QDir::Files|QDir::Executable); //Returns an empty list if it does not exist in the path
    if(pluginList.size()==0){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","The plugin bgImageWriter can not be loaded because is not in the same folder as this program. Images will not be saved");
    }
    serviceSlot(3, "bgImageWriter", true, "1", fps);



}
void Videostreaming::start_bgPupilDetection(unsigned int fps){
    //Check if bgPupilDetection exists before loading it (To show an error)
    qDebug()<<Q_FUNC_INFO<<" ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ";
    QDir runPath = QDir::currentPath();
    QStringList nameFilter;
    nameFilter << "bgPupilDetection";
    QFileInfoList pluginList = runPath.entryInfoList( nameFilter,QDir::Files|QDir::Executable); //Returns an empty list if it does not exist in the path
    if(pluginList.size()==0){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","The plugin bgPupilDetection can not be loaded because is not in the same folder as this program. Images will not be processed");
    }
    qDebug()<<Q_FUNC_INFO<<" ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ";
    system(QString("./bgPupilDetection %2 &").arg(fps).toLatin1().data());
    qDebug()<<Q_FUNC_INFO<<" ===== ===== ===== ===== ===== ";
}


void Videostreaming::processReady(){
    qDebug()<<Q_FUNC_INFO<<" -*-*- -*-*- -*-*- -*-*- -*-*- -*-*- -*-*- -*-*- m_offline: "<<m_offline<<", m_freq: "<<m_freq;
    if(m_offline){
        if(m_freq == -1){ //procesamiento offline
            QSettings *m_settings = new QSettings( m_directoryName + QString("/camera.ini"), QSettings::IniFormat);
            m_imgSize.setSize(QSize(m_settings->value("image/width",QString(m_imgSize.width())).toInt(), m_settings->value("image/height",QString(m_imgSize.height())).toInt()));
        }
        else{ //nunca entra en esta opción ya que m_freq se establece en callOflline y siempre se llama a callOffline con -1 en freq
            emit closeVideo();
        }
        cv::VideoCapture tryAvi;
        //se crean dos "handlers" de archivos para gestionar los .avi y los .dat ocultos que contienen la posición del ojo en cada momento
        QFileInfoList aviCheck=QDir(QString(QString(m_directoryName)+"/raw")).entryInfoList((QStringList("*.avi"),QDir::Files));
        QFileInfoList datCheck=QDir(m_directoryName).entryInfoList(QStringList("*d1.dat"),QDir::Files|QDir::Hidden);
        qDebug()<<Q_FUNC_INFO<<" aviCheck.size(): "<<aviCheck.size();//se imprime el numero de archivos avi y .dat oculto del directorio m_directoryName
        qDebug()<<Q_FUNC_INFO<<" datCheck.size(): "<<datCheck.size();
        if(aviCheck.size()<=0 || datCheck.size()<=0){ //error en el video
            qDebug()<<Q_FUNC_INFO<<" emit corruptVideo() -> -> -> -> -> -> -> -> -> -> -> -> -> ";
            emit corruptVideo(); //ejecuta onCorruptVideo de vidstreamproperty en tabcapturerfilter_qml.qml
        }
        else if(!tryAvi.open(aviCheck.at(0).absoluteFilePath().toLatin1().data())){ // si da problema al abrir el primer .avi
            qDebug()<<Q_FUNC_INFO<<" emit corruptVideo() -> -> -> -> -> -> -> -> -> -> -> -> -> ";
            emit corruptVideo(); //ejecuta onCorruptVideo de vidstreamproperty en tabcapturerfilter_qml.qml
        }
        else{
            qDebug()<<Q_FUNC_INFO<<" emit processDBus() -> -> -> -> -> -> -> -> -> -> -> -> -> frames: " << m_totalFramesToProcess;
            emit processDBus(m_directoryName, m_freq, m_imgSize.width(), m_imgSize.height(), m_totalFramesToProcess);
        }
    }
    else{
        emit configTrackerDBus(m_imgSize.width(), m_imgSize.height());
        if(m_isClb){
            emit newD1FileDBus(m_d1FileName+"d1.dat");
        }

    }
}


//NOTE: This method is defined in src/dbus/oscann.xml
//      By now, it is not needed. However, It is left for future updates
//TODO: Use this method to shutdown bgImageWriter process as well as bgPupilDetection
void Videostreaming::methodName(){
    //emit newImage("From erix", "test", "test");
}

void Videostreaming::setDirectoryName(QString value){
    qDebug()<<Q_FUNC_INFO<<" <><><><><><> <><><><><><> <><><><><><> <><><><><><> <><><><><><> <><><><><><> <><><><><><> m_directoryName: "<<m_directoryName;
    m_directoryName=value;
}
void Videostreaming::setTotalFramesToProcess(const unsigned int value){
    m_totalFramesToProcess = value;
}
void Videostreaming::keyHandler(const int key, const bool fromRun=false){//Signal to displayCT
    emit keyPressedDbus(key);
    qDebug()<<Q_FUNC_INFO<<" fromRun: "<<fromRun
           //<<", m_testTimer: "<<m_testTimer
          <<", m_isClb: "<<m_isClb
         //<<", m_testTimer->isActive(): "<<m_testTimer->isActive()
        <<", m_startTimer: "<<m_startTimer;

    if(fromRun &&
            //m_testTimer &&
            !m_isClb &&
            //!m_testTimer->isActive() &&
            key == Qt::Key_Space &&
            m_startTimer
            ){
        //m_testTimer->start();
        createTimer();
        m_startTimer = false;
    }
}
void Videostreaming::killbgPupilDetector(){ //Esta función es llamada cuando la barra de porcentaje alcanza el 100%
    if(m_killbgPupilDetectorFlag){
        emit shutdownDBus(2);
        m_killbgPupilDetectorFlag         =   false;
    }
}
void Videostreaming::normalStateSlot(){
    emit saveImagesDbus(false);  //signal of aura.GUIInterface
    emit normalStateDbus();
    killbgPupilDetector();
    m_offline = false;
    if(m_testTimer && !m_isClb){
        if(m_testTimer->isActive()){
            emit testProgress(m_testProgress = 101, Q_FUNC_INFO);
            m_testTimer->stop();
            m_startTimer = true;
            qDebug()<<Q_FUNC_INFO<<" ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### m_startTimer: "<<m_startTimer;
        }
    }
}
void Videostreaming::stop(){
    emit stopDBus();
}

void Videostreaming::callOffline(int freq, unsigned int fps){
    m_offline = true;
    start_bgPupilDetection(fps);           //Lanzar el plugin de deteccion de pupila
    m_killbgPupilDetectorFlag = true;     //Indicar que se debe cerrar al acabar el procesado
    m_freq = freq;
}

int Videostreaming::processQueueAdd(){
    m_vector2Process.push_back(m_directoryName);
}

int Videostreaming::queueLength(){
    return m_vector2Process.length();
}

QStringList Videostreaming::processQueue(){
    QStringList directories;
    QVector<QString> tmp = m_vector2Process;
    cv::VideoCapture vc;
    QFileInfoList aviFileName; //nombre de los archivos de video
    QFileInfoList avis; //archivos de video
    unsigned int tftp = 0; //total frames to process
    QString textName;
    bool hasClb = false;
    while(!tmp.isEmpty()){ //mientras haya videos que procesar en la cola
        textName = tmp.front(); //nombre del primer Test en el vector de test a procesar
        if(textName.contains("CC") || textName.contains("CA"))//significa que son calibraciones
            hasClb = true;
        //TODO: Add _0.avi, _1.avi
        //aviFileName    =   QDir(QString("%1/raw").arg(textName)).entryInfoList(QStringList("*.avi"),QDir::Files);

        avis=QDir(QString("%1/raw").arg(textName)).entryInfoList(QStringList("*.avi"),QDir::Files);
        qDebug()<<Q_FUNC_INFO<<" m_NOV: "<<avis.length(); //imprimimos el nombre de la función y el numero de archivos de video que contiene
        switch(avis.length()){ //si en la lista hay uno o dos archivos de video se capturan los videos y se contabiliza el número de frames totales
        case 1:
            vc = cv::VideoCapture(QString(textName+"/raw/"+textName.split("/").last()+"_0.avi").toLatin1().data());
            tftp += vc.get(cv::CAP_PROP_FRAME_COUNT);
            break;
        case 2:
            qDebug()<<Q_FUNC_INFO<<" 1: "<<QString(textName+"/raw/"+textName.split("/").last()+"_0.avi");
            vc = cv::VideoCapture(QString(textName+"/raw/"+textName.split("/").last()+"_0.avi").toLatin1().data());
            tftp += vc.get(cv::CAP_PROP_FRAME_COUNT);
            qDebug()<<Q_FUNC_INFO<<" 1: "<<QString(textName+"/raw/"+textName.split("/").last()+"_1.avi");
            vc = cv::VideoCapture(QString(textName+"/raw/"+textName.split("/").last()+"_1.avi").toLatin1().data());
            tftp += vc.get(cv::CAP_PROP_FRAME_COUNT);
            break;
        }
        avis.clear();
        directories.push_back(textName);//guardamos la info en el QStringList
        tmp.pop_front(); //borramos el primero tras sacar los tftp
    }
    if(tftp != 0 && hasClb){ //hay calibración y los videos tenian frames
        setTotalFramesToProcess(tftp); //indicamos el número total de frames a procesar
    }
    if(!hasClb) //si no hay calibración
        directories.clear();
    return directories;
}


QString Videostreaming::returnDefaultDir(){ //función que devuelve la ruta donde se guardan los pacientes
    return QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first()+"/Default";
}

void Videostreaming::openPatientDataFile(QString sessionPath){
    QStringList sessionPathSplit = sessionPath.split("/"); //Obtener el nombre de la sesión como el ultimo directorio de la ruta
    QString patientDataFilename = sessionPathSplit[sessionPathSplit.length()-1]+"DataFile.csv"; //Generar un QFile con la ruta deseada del fichero
    QFile patientDataFile(sessionPath+"/"+patientDataFilename);

    qDebug()<<"abriendo patient data file en "<<sessionPath<<" con nombre "<<patientDataFilename;
    if(!patientDataFile.exists()){ //Comprobar si ya exisite un fichero de datos
        //Si no hay, es necesario crearlo
        //Se copia un template guardado en bin para no empezarlo en blanco
        QFile templateDataFile("./templateDataFile.csv");
        if(templateDataFile.exists()){
            //Se hace la copia solo si el template existe
            QDir dir(sessionPath);
            if (!dir.exists()){
              dir.mkpath("."); //Crear la ruta de directortios si no exisiten para poder copiar el fichero de datos del paciente
            }
            QFile::copy("./templateDataFile.csv", patientDataFile.fileName());

        }else{
            //En caso de no exisitir un template se ha de generar uno
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("Template not found. Create it and try again.\nDo you want to create it now?");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret=msgBox.exec();
            if(ret==QMessageBox::Ok)
                configPatientDataTemplate();
            return;
        }
    }

    //Si ya exisitia o acaba de ser creado se realizan los siguientes pasos
    QDesktopServices::openUrl(QUrl(patientDataFile.fileName())); //Abrir el archivo (Como si se pulsara) para editarlo en excel
}
void Videostreaming::configPatientDataTemplate(){
    QFile templateDataFile("./templateDataFile.csv");
    if(!templateDataFile.exists()){
        templateDataFile.open(QIODevice::WriteOnly);
        templateDataFile.write(",");
    }
    QDesktopServices::openUrl(QUrl(templateDataFile.fileName()));
}

void Videostreaming::killDisplayCT(){emit shutdownDBus(0);}
