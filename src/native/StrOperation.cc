#include <node.h>
#include <v8.h>

void Method(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();
  args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "world"));
}

#define CONCAT(a, b) CONCAT_HELPER(a, b)
#define CONCAT_HELPER(a, b) a##b
#define INITIALIZER CONCAT(node_register_module_v, NODE_MODULE_VERSION)

extern "C" NODE_MODULE_EXPORT void INITIALIZER(v8::Local<v8::Object> exports,
                                               v8::Local<v8::Value> module,
                                               v8::Local<v8::Context> context)
{
  NODE_SET_METHOD(exports, "hello", Method);
}

static void FakeInit(v8::Local<v8::Object> exports,
                     v8::Local<v8::Value> module,
                     v8::Local<v8::Context> context)
{
  auto isolate = context->GetIsolate();
  auto exception = v8::Exception::Error(v8::String::NewFromUtf8(isolate,
                                                                "FakeInit should never run!", v8::NewStringType::kNormal)
                                            .ToLocalChecked());
  isolate->ThrowException(exception);
}

// Define a Node.js module, but with the wrong version. Node.js should still be
// able to load this module, multiple times even, because it exposes the
// specially named initializer above.
// #undef NODE_MODULE_VERSION
// #define NODE_MODULE_VERSION 70
NODE_MODULE(NODE_GYP_MODULE_NAME, FakeInit)