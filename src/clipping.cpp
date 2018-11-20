#include <napi.h>
#include <string>

#include "common.h"
#include "clipping.h"
#include "tools.h"

Napi::Value decode_clipping_params(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  const char *encoded_params = info[0].As<Napi::String>().Utf8Value().c_str();

  int params_len;

  dt_iop_clipping_params_t *params = (dt_iop_clipping_params_t *)dt_exif_xmp_decode(
      encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  params_obj.Set(
      Napi::String::New(env, "angle"),
      Napi::Number::New(env, params->angle));

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
      Napi::String::New(env, "kH"),
      Napi::Number::New(env, params->k_h));

  params_obj.Set(
      Napi::String::New(env, "kV"),
      Napi::Number::New(env, params->k_v));

  params_obj.Set(
      Napi::String::New(env, "kxa"),
      Napi::Number::New(env, params->kxa));

  params_obj.Set(
      Napi::String::New(env, "kya"),
      Napi::Number::New(env, params->kya));

  params_obj.Set(
      Napi::String::New(env, "kxb"),
      Napi::Number::New(env, params->kxb));

  params_obj.Set(
      Napi::String::New(env, "kyb"),
      Napi::Number::New(env, params->kyb));

  params_obj.Set(
      Napi::String::New(env, "kxc"),
      Napi::Number::New(env, params->kxc));

  params_obj.Set(
      Napi::String::New(env, "kyc"),
      Napi::Number::New(env, params->kyc));

  params_obj.Set(
      Napi::String::New(env, "kxd"),
      Napi::Number::New(env, params->kxd));

  params_obj.Set(
      Napi::String::New(env, "kyd"),
      Napi::Number::New(env, params->kyd));

  params_obj.Set(
      Napi::String::New(env, "kType"),
      Napi::Number::New(env, params->k_type));

  params_obj.Set(
      Napi::String::New(env, "kSym"),
      Napi::Number::New(env, params->k_sym));

  params_obj.Set(
      Napi::String::New(env, "kApply"),
      Napi::Boolean::New(env, params->k_apply));

  params_obj.Set(
      Napi::String::New(env, "cropAuto"),
      Napi::Boolean::New(env, params->crop_auto));

  params_obj.Set(
      Napi::String::New(env, "ratioN"),
      Napi::Number::New(env, params->ratio_n));

  params_obj.Set(
      Napi::String::New(env, "ratioD"),
      Napi::Number::New(env, params->ratio_d));

  return params_obj;
}

Napi::Value encode_clipping_params(const Napi::CallbackInfo &info)
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

  const Napi::Object clipping_params_object = info[0].As<Napi::Object>();

  dt_iop_clipping_params_t clipping_params = {
      0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.2f, 0.2f, 0.8f, 0.2f,
      0.8f, 0.8f, 0.2f, 0.8f, 0, 0, FALSE, TRUE, -1, -1};

  // __
  if (clipping_params_object.Has("angle"))
  {
    clipping_params.angle = clipping_params_object.Get("angle").ToNumber().FloatValue();
  }

  // cx
  if (clipping_params_object.Has("cx"))
  {
    clipping_params.cx = clipping_params_object.Get("cx").ToNumber().FloatValue();
  }

  // cy
  if (clipping_params_object.Has("cy"))
  {
    clipping_params.cy = clipping_params_object.Get("cy").ToNumber().FloatValue();
  }

  // cw
  if (clipping_params_object.Has("cw"))
  {
    clipping_params.cw = clipping_params_object.Get("cw").ToNumber().FloatValue();
  }

  // ch
  if (clipping_params_object.Has("ch"))
  {
    clipping_params.ch = clipping_params_object.Get("ch").ToNumber().FloatValue();
  }

  // k_h
  if (clipping_params_object.Has("kH"))
  {
    clipping_params.k_h = clipping_params_object.Get("kH").ToNumber().FloatValue();
  }

  // k_v
  if (clipping_params_object.Has("kV"))
  {
    clipping_params.k_v = clipping_params_object.Get("kV").ToNumber().FloatValue();
  }

  // kxa
  if (clipping_params_object.Has("kxa"))
  {
    clipping_params.kxa = clipping_params_object.Get("kxa").ToNumber().FloatValue();
  }

  // kya
  if (clipping_params_object.Has("kya"))
  {
    clipping_params.kya = clipping_params_object.Get("kya").ToNumber().FloatValue();
  }

  // kxb
  if (clipping_params_object.Has("kxb"))
  {
    clipping_params.kxb = clipping_params_object.Get("kxb").ToNumber().FloatValue();
  }

  // kyb
  if (clipping_params_object.Has("kyb"))
  {
    clipping_params.kyb = clipping_params_object.Get("kyb").ToNumber().FloatValue();
  }

  // kxc
  if (clipping_params_object.Has("kxc"))
  {
    clipping_params.kxc = clipping_params_object.Get("kxc").ToNumber().FloatValue();
  }

  // kyc
  if (clipping_params_object.Has("kyc"))
  {
    clipping_params.kyc = clipping_params_object.Get("kyc").ToNumber().FloatValue();
  }

  // kxd
  if (clipping_params_object.Has("kxd"))
  {
    clipping_params.kxd = clipping_params_object.Get("kxd").ToNumber().FloatValue();
  }

  // kyd
  if (clipping_params_object.Has("kyd"))
  {
    clipping_params.kyd = clipping_params_object.Get("kyd").ToNumber().FloatValue();
  }

  // k_type
  if (clipping_params_object.Has("kType"))
  {
    clipping_params.k_type = clipping_params_object.Get("kType").ToNumber().Int32Value();
  }

  // k_sym
  if (clipping_params_object.Has("kSym"))
  {
    clipping_params.k_sym = clipping_params_object.Get("kSym").ToNumber().Int32Value();
  }

  // k_apply
  if (clipping_params_object.Has("kApply"))
  {
    clipping_params.k_apply = clipping_params_object.Get("kApply").ToBoolean().Value()
                                  ? TRUE
                                  : FALSE;
  }

  // crop_auto
  if (clipping_params_object.Has("cropAuto"))
  {
    clipping_params.crop_auto = clipping_params_object.Get("cropAuto").ToBoolean().Value()
                                    ? TRUE
                                    : FALSE;
  }

  // ratio_n
  if (clipping_params_object.Has("ratioN"))
  {
    clipping_params.ratio_n = clipping_params_object.Get("ratioN").ToNumber().Int32Value();
  }

  // ratio_d
  if (clipping_params_object.Has("ratioD"))
  {
    clipping_params.ratio_d = clipping_params_object.Get("ratioD").ToNumber().Int32Value();
  }

  const char *decoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&clipping_params, sizeof(dt_iop_clipping_params_t), NULL);

  return Napi::String::New(env, decoded_params);
}
