#include <napi.h>

#include <iostream>
#include <string>

#include "blend.h"
#include "sharpen.h"
#include "levels.h"
#include "shadhi.h"
#include "exposure.h"
#include "clipping.h"
#include "masks.h"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  // sharpen
  exports.Set(
      Napi::String::New(env, "decodeSharpenParams"),
      Napi::Function::New(env, decode_sharpen_params));

  exports.Set(
      Napi::String::New(env, "encodeSharpenParams"),
      Napi::Function::New(env, encode_sharpen_params));

  // levels
  exports.Set(
      Napi::String::New(env, "decodeLevelsParams"),
      Napi::Function::New(env, decode_levels_params));

  exports.Set(
      Napi::String::New(env, "encodeLevelsParams"),
      Napi::Function::New(env, encode_levels_params));

  // shadhi
  exports.Set(
      Napi::String::New(env, "decodeShadhiParams"),
      Napi::Function::New(env, decode_shadhi_params));

  exports.Set(
      Napi::String::New(env, "encodeShadhiParams"),
      Napi::Function::New(env, encode_shadhi_params));

  // exposure
  exports.Set(
      Napi::String::New(env, "decodeExposureParams"),
      Napi::Function::New(env, decode_exposure_params));

  exports.Set(
      Napi::String::New(env, "encodeExposureParams"),
      Napi::Function::New(env, encode_exposure_params));

  // blend
  exports.Set(
      Napi::String::New(env, "decodeBlendParams"),
      Napi::Function::New(env, decode_blend_params));

  exports.Set(
      Napi::String::New(env, "encodeBlendParams"),
      Napi::Function::New(env, encode_blend_params));

  // clipping
  exports.Set(
      Napi::String::New(env, "decodeClippingParams"),
      Napi::Function::New(env, decode_clipping_params));

  exports.Set(
      Napi::String::New(env, "encodeClippingParams"),
      Napi::Function::New(env, encode_clipping_params));

  // mask
  exports.Set(
      Napi::String::New(env, "decodeMaskPoints"),
      Napi::Function::New(env, decode_mask_points));

  exports.Set(
      Napi::String::New(env, "encodeMaskPoints"),
      Napi::Function::New(env, encode_mask_points));

  return exports;
};

NODE_API_MODULE(init, Init);
