#include <napi.h>
#include <string>

#include "crop.h"
#include "tools.h"

Napi::Value decode_crop_params(const Napi::CallbackInfo &info)
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

  dt_iop_crop_params_t *params =
      (dt_iop_crop_params_t *)dt_exif_xmp_decode(
          encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  params_obj.Set(
      Napi::String::New(env, "cx"),
      Napi::Number::New(env, params->cx));

  params_obj.Set(
      Napi::String::New(env, "cy"),
      Napi::Number::New(env, params->cy));

  params_obj.Set(
      Napi::String::New(env, "cw"),
      Napi::Number::New(env, params->cw));

  params_obj.Set(
      Napi::String::New(env, "ch"),
      Napi::Number::New(env, params->ch));

  params_obj.Set(
      Napi::String::New(env, "ratioN"),
      Napi::Number::New(env, params->ratio_n));

  params_obj.Set(
      Napi::String::New(env, "ratioD"),
      Napi::Number::New(env, params->ratio_d));

  return params_obj;
}

Napi::Value encode_crop_params(const Napi::CallbackInfo &info)
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

  const Napi::Object crop_params_object = info[0].As<Napi::Object>();

  dt_iop_crop_params_t crop_params = {
    0.0f, 0.0f, 1.0f, 1.0f, -1, -1
  };

  // cx
  if (crop_params_object.Has("cx"))
  {
    crop_params.cx = crop_params_object.Get("cx").ToNumber().FloatValue();
  }

  // cy
  if (crop_params_object.Has("cy"))
  {
    crop_params.cy = crop_params_object.Get("cy").ToNumber().FloatValue();
  }

  // cw
  if (crop_params_object.Has("cw"))
  {
    crop_params.cw = crop_params_object.Get("cw").ToNumber().FloatValue();
  }

  // ch
  if (crop_params_object.Has("ch"))
  {
    crop_params.ch = crop_params_object.Get("ch").ToNumber().FloatValue();
  }

  // ratio_n
  if (crop_params_object.Has("ratioN"))
  {
    crop_params.ratio_n = crop_params_object.Get("ratioN").ToNumber().Int32Value();
  }

  // ratio_d
  if (crop_params_object.Has("ratioD"))
  {
    crop_params.ratio_d = crop_params_object.Get("ratioD").ToNumber().Int32Value();
  }

  const char *decoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&crop_params, sizeof(dt_iop_crop_params_t), NULL);

  return Napi::String::New(env, decoded_params);
}

