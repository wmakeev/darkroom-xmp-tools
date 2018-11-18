#include <napi.h>
#include <string>

#include "expose.hpp"
#include "tools.hpp"

Napi::Value decode_expose_params(const Napi::CallbackInfo &info)
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

  dt_iop_exposure_params_t *params = (dt_iop_exposure_params_t *)dt_exif_xmp_decode(
      encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  Napi::String mode_string;

  switch (params->mode)
  {
  case EXPOSURE_MODE_MANUAL:
    mode_string = Napi::String::New(env, "EXPOSURE_MODE_MANUAL");
    break;

  case EXPOSURE_MODE_DEFLICKER:
    mode_string = Napi::String::New(env, "EXPOSURE_MODE_DEFLICKER");
    break;
  };

  params_obj.Set(Napi::String::New(env, "mode"), mode_string);

  params_obj.Set(
      Napi::String::New(env, "black"),
      Napi::Number::New(env, params->black));

  params_obj.Set(
      Napi::String::New(env, "exposure"),
      Napi::Number::New(env, params->exposure));

  params_obj.Set(
      Napi::String::New(env, "deflickerPercentile"),
      Napi::Number::New(env, params->deflicker_percentile));

  params_obj.Set(
      Napi::String::New(env, "deflickerTargetLevel"),
      Napi::Number::New(env, params->deflicker_target_level));

  return params_obj;
}

Napi::Value encode_expose_params(const Napi::CallbackInfo &info)
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

  const Napi::Object expose_params_object = info[0].As<Napi::Object>();

  dt_iop_exposure_params_t expose_params = {EXPOSURE_MODE_DEFLICKER, 0.0f, 0.0f, 50.0f, -4.0f};

  // mode
  if (expose_params_object.Has("mode")) {
    std::string expose_mode_str =
        expose_params_object.Get("mode").As<Napi::String>().Utf8Value();

    if (expose_mode_str == "EXPOSURE_MODE_MANUAL") {
      expose_params.mode = EXPOSURE_MODE_MANUAL;
    }
    else if (expose_mode_str == "EXPOSURE_MODE_DEFLICKER")
    {
      expose_params.mode = EXPOSURE_MODE_DEFLICKER;
    }
    else
    {
      Napi::TypeError::New(env, "Unknown expose mode name").ThrowAsJavaScriptException();
      return env.Null();
    }
  }

  // black
  if (expose_params_object.Has("black"))
  {
    expose_params.black = expose_params_object.Get("black").ToNumber().FloatValue();
  }

  // exposure
  if (expose_params_object.Has("exposure"))
  {
    expose_params.exposure = expose_params_object.Get("exposure").ToNumber().FloatValue();
  }

  // deflicker_percentile
  if (expose_params_object.Has("deflickerPercentile"))
  {
    expose_params.deflicker_percentile =
        expose_params_object.Get("deflickerPercentile").ToNumber().FloatValue();
  }

  // deflicker_target_level
  if (expose_params_object.Has("deflickerTargetLevel"))
  {
    expose_params.deflicker_target_level =
        expose_params_object.Get("deflickerTargetLevel").ToNumber().FloatValue();
  }

  const char *decoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&expose_params, sizeof(expose_params), NULL);

  return Napi::String::New(env, decoded_params);
}
