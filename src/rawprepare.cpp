#include <napi.h>
#include <string>

#include "rawprepare.h"
#include "tools.h"

Napi::Value decode_rawprepare_params(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "Wrong arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  std::string encoded_params_str = info[0].ToString().Utf8Value();
  const char *encoded_params = encoded_params_str.c_str();

  if (strlen(encoded_params) == 0)
  {
    Napi::TypeError::New(env, "Wrong arguments (empty params string)")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  int params_len;

  dt_iop_rawprepare_params_t *params =
      (dt_iop_rawprepare_params_t *)dt_exif_xmp_decode(
          encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  params_obj.Set(
      Napi::String::New(env, "x"),
      Napi::Number::New(env, params->x));

  params_obj.Set(
      Napi::String::New(env, "y"),
      Napi::Number::New(env, params->y));

  params_obj.Set(
      Napi::String::New(env, "width"),
      Napi::Number::New(env, params->width));

  params_obj.Set(
      Napi::String::New(env, "height"),
      Napi::Number::New(env, params->height));

  // raw_black_level_separate
  Napi::Array raw_black_level_separate_array = Napi::Array::New(env, 4);
  for (int i = 0; i < 4; i++)
  {
    raw_black_level_separate_array.Set(i, params->raw_black_level_separate[i]);
  }
  params_obj.Set(
    Napi::String::New(env, "rawBlackLevelSeparate"),
    raw_black_level_separate_array);

  params_obj.Set(
    Napi::String::New(env, "rawWhitePoint"),
    Napi::Number::New(env, params->raw_white_point));

  return params_obj;
}

Napi::Value encode_rawprepare_params(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsObject())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  const Napi::Object rawprepare_params_object = info[0].As<Napi::Object>();

  dt_iop_rawprepare_params_t rawprepare_params = {
    0, 0, 0, 0, {0, 0, 0, 0}, 0
  };

  // x
  if (rawprepare_params_object.Has("x"))
  {
    rawprepare_params.x = rawprepare_params_object.Get("x").ToNumber().Int32Value();
  }

  // y
  if (rawprepare_params_object.Has("y"))
  {
    rawprepare_params.y = rawprepare_params_object.Get("y").ToNumber().Int32Value();
  }

  // width
  if (rawprepare_params_object.Has("width"))
  {
    rawprepare_params.width = rawprepare_params_object.Get("width").ToNumber().Int32Value();
  }

  // height
  if (rawprepare_params_object.Has("height"))
  {
    rawprepare_params.height = rawprepare_params_object.Get("height").ToNumber().Int32Value();
  }

  // raw_black_level_separate
  if (rawprepare_params_object.Has("rawBlackLevelSeparate"))
  {
    Napi::Value raw_black_level_separate_value =
        rawprepare_params_object.Get("rawBlackLevelSeparate");
    if (!raw_black_level_separate_value.IsArray())
    {
      Napi::TypeError::New(env, "rawprepare rawBlackLevelSeparate field expected to be Array")
          .ThrowAsJavaScriptException();
      return env.Null();
    };

    Napi::Array raw_black_level_separate_object = raw_black_level_separate_value.ToObject().As<Napi::Array>();

    if (raw_black_level_separate_object.Length() != 4) {
      Napi::TypeError::New(env, "rawprepare rawBlackLevelSeparate expect length 4")
          .ThrowAsJavaScriptException();
      return env.Null();
    }

    for (int i = 0; i < 4; i++)
    {
      Napi::Value black_level_separate = raw_black_level_separate_object.Get(i);
      if (!black_level_separate.IsNumber())
      {
        Napi::TypeError::New(env, "rawprepare rawBlackLevelSeparate values expected to be Number")
            .ThrowAsJavaScriptException();
        return env.Null();
      };

      uint32_t value = black_level_separate.ToNumber().Uint32Value();
      if (value > UINT16_MAX) {
        Napi::TypeError::New(env, "rawprepare rawBlackLevelSeparate value is above the maximum")
            .ThrowAsJavaScriptException();
        return env.Null();
      }

      rawprepare_params.raw_black_level_separate[i] = value;
    }
  }

  // raw_white_point
  if (rawprepare_params_object.Has("rawWhitePoint"))
  {
    uint32_t value = rawprepare_params_object.Get("rawWhitePoint").ToNumber().Uint32Value();
    if (value > UINT16_MAX) {
      Napi::TypeError::New(env, "rawprepare rawWhitePoint value is above the maximum")
          .ThrowAsJavaScriptException();
      return env.Null();
    }

    rawprepare_params.raw_white_point = value;
  }

  const char *decoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&rawprepare_params, sizeof(dt_iop_rawprepare_params_t), NULL);

  return Napi::String::New(env, decoded_params);
}
