#ifndef USBDEVWRAP_H
#define USBDEVWRAP_H

#include <node.h>
#include <node_object_wrap.h>
#include "usbdev.h"

#include "videostreaming.h"
#include "cameraviewer.h"

#include <QApplication>
#include <QCoreApplication>

class usbdevWrap : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit usbdevWrap(double value = 0);
  ~usbdevWrap();

  double value_;
  usbdev* oscannlight;

  Videostreaming* VS;
  cameraViewer* CV;
  QApplication* app;

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void plusOne(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void openDevice(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void serviceSlot(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void mainWrap(const v8::FunctionCallbackInfo<v8::Value>& args);

  int main();
};


#endif