#include "usbdevWrap.h"

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::ObjectTemplate;
using v8::String;
using v8::Value;

usbdevWrap::usbdevWrap(double value) : value_(value) {
}

usbdevWrap::~usbdevWrap() {
}

void usbdevWrap::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<ObjectTemplate> addon_data_tpl = ObjectTemplate::New(isolate);
  addon_data_tpl->SetInternalFieldCount(1);  // 1 field for the usbdevWrap::New()
  Local<Object> addon_data =
      addon_data_tpl->NewInstance(context).ToLocalChecked();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New, addon_data);
  tpl->SetClassName(String::NewFromUtf8(isolate, "usbdevWrap").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "plusOneWrap", plusOne);
  NODE_SET_PROTOTYPE_METHOD(tpl, "openDeviceWrap", openDevice);
  NODE_SET_PROTOTYPE_METHOD(tpl, "serviceSlotWrap", serviceSlot);
  NODE_SET_PROTOTYPE_METHOD(tpl, "MainWrap", mainWrap);

  Local<Function> constructor = tpl->GetFunction(context).ToLocalChecked();
  addon_data->SetInternalField(0, constructor);
  exports->Set(context, String::NewFromUtf8(
      isolate, "usbdevWrap").ToLocalChecked(),
      constructor).FromJust();
}

void usbdevWrap::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new usbdevWrap(...)`
    double value = args[0]->IsUndefined() ?
        0 : args[0]->NumberValue(context).FromMaybe(0);
    usbdevWrap* obj = new usbdevWrap(value);
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `usbdevWrap(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Function> cons =
        args.Data().As<Object>()->GetInternalField(0).As<Function>();
    Local<Object> result =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(result);
  }
}

void usbdevWrap::plusOne(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  usbdevWrap* obj = ObjectWrap::Unwrap<usbdevWrap>(args.Holder());
  obj->value_ += 1;

  args.GetReturnValue().Set(Number::New(isolate, obj->value_));
}

void usbdevWrap::openDevice(const FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = args.GetIsolate();

  usbdevWrap* obj = ObjectWrap::Unwrap<usbdevWrap>(args.Holder());
  bool res = obj->oscannlight->openDevice();

  args.GetReturnValue().Set(Number::New(isolate, res));
}

void usbdevWrap::serviceSlot(const FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = args.GetIsolate();

  usbdevWrap* obj = ObjectWrap::Unwrap<usbdevWrap>(args.Holder());
  bool res = 0;

  qDebug() << "cameraType: " << obj->VS->getCameraType();

  obj->VS->serviceSlot(1, "bgVideoCapturer", 1, "", 120);
  //obj->VS.serviceSlot(1, "bgVideoCapturer", 0, "", 120);

  usleep(5000000);

  qDebug() << "cameraType: " << obj->VS->getCameraType();

  obj->VS->serviceSlot(1, "bgVideoCapturer", 0, "", 120);

  args.GetReturnValue().Set(Number::New(isolate, res));
}

void usbdevWrap::mainWrap(const FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = args.GetIsolate();

  usbdevWrap* obj = ObjectWrap::Unwrap<usbdevWrap>(args.Holder());
  qDebug() << "Entramos en mainWrap";

  int res = obj->main();
      qDebug() << "Despues de res main: "<< res;
  args.GetReturnValue().Set(Number::New(isolate, res));
  qDebug() << "Salimos del mainWrap";
}

int usbdevWrap::main(){

  //QApplication app(int argc, char *argv[]);
  qDebug() << "Entramos en main";
  char **argv = NULL;
  int argc = 0;
  app = new QApplication(argc,  argv);

  VS = new Videostreaming();
  CV = new cameraViewer();
  oscannlight = new usbdev();

  VS->setupDbus();
  CV->setupDbus();
    qDebug() << "Despues de setup";

  //VS->serviceSlot(1, "bgVideoCapturer", 1, "", 120);

  return app->exec();
  //return 20;
}


