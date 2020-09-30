#ifndef VIDEOSTREAMINGWRAP_H
#define VIDEOSTREAMINGWRAP_H

#include <node.h>
#include <node_object_wrap.h>
#include "videostreaming.h"

class videostreamingWrap : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit videostreamingWrap(double value = 0);
  ~videostreamingWrap();

  double value_;
  Videostreaming VS;

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void PlusOne(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void ServiceSlot(const v8::FunctionCallbackInfo<v8::Value>& args);
};


#endif