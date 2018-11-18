#include <napi.h>

#include <iostream>
#include <string>

#include "blend.hpp"
#include "expose.hpp"
#include "clipping.hpp"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(
      Napi::String::New(env, "decodeExposeParams"),
      Napi::Function::New(env, decode_expose_params));

  exports.Set(
      Napi::String::New(env, "encodeExposeParams"),
      Napi::Function::New(env, encode_expose_params));

  exports.Set(
      Napi::String::New(env, "decodeBlendParams"),
      Napi::Function::New(env, decode_blend_params));

  exports.Set(
      Napi::String::New(env, "encodeBlendParams"),
      Napi::Function::New(env, encode_blend_params));

  exports.Set(
      Napi::String::New(env, "decodeClippingParams"),
      Napi::Function::New(env, decode_clipping_params));

  exports.Set(
      Napi::String::New(env, "encodeClippingParams"),
      Napi::Function::New(env, encode_clipping_params));

  return exports;
};

NODE_API_MODULE(init, Init);
