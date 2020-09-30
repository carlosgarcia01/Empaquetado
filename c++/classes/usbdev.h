#ifndef USBDEV_H
#define USBDEV_H

#include <QtCore/QString>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QtCore/QThread>
#include <stdio.h>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
//#include <QtCore/QObject>

//#include <node.h> //new
//#include <node_object_wrap.h> //new

//NOTE: Create a file 70-imu-device.rules in /etc/dev/dules.d with this line:
//#SUBSYSTEMS=="usb", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", NAME="ttyUSB0", MODE="0666", OWNER="eritski"
//
//SUBSYSTEMS=="usb", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", SYMLINK+="ttyIMU0", MODE="0666", OWNER="eritski"



class usbdev  : public QObject/*, public node::ObjectWrap new*/{
    Q_OBJECT
private:
    QString data;
    int fd;
    QString deviceName;
    int speed;
    int Configure(int speed, int parity);
    void SetBlocking (int shouldBlock);
    bool oscannLightReady;

    //static void New(const v8::FunctionCallbackInfo<v8::Value>& args); //new
    //static void Node_Open_Device(const v8::FunctionCallbackInfo<v8::Value>& args); //new

public:
    Q_INVOKABLE explicit usbdev(QObject *parent = 0)  : QObject(parent), deviceName("/dev/ttyOSCANN"), speed(57600){}
    ~usbdev();
    Q_INVOKABLE void setDeviceName(const QString &f);
    Q_INVOKABLE void setSpeed(const int speed);
    Q_INVOKABLE bool getOscannLightReady(){return oscannLightReady;}
    Q_INVOKABLE bool setOscannLightReady(const bool value){oscannLightReady = value;}

    //static void Init(v8::Local<v8::Object> exports); //new

public slots:
    void writeData(const QString data);
    bool openDevice();
    void closeDevice();

signals:
    void deviceReady();
    void deviceError(const int errId);
};

#endif // USBDEV_H
