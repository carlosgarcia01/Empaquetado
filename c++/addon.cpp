#include <node.h>
#include "usbdevWrap.h"

using namespace v8;

void InitAll(Local<Object> exports) {
  usbdevWrap::Init(exports);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll);
