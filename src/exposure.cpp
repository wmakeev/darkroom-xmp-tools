#include <napi.h>
#include <string>

#include "exposure.h"
#include "tools.h"

Napi::Value decode_exposure_params(const Napi::CallbackInfo &info)
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

  std::string encoded_params_str = info[0].ToString().Utf8Value();
  const char *encoded_params = encoded_params_str.c_str();

  if (strlen(encoded_params) == 0)
  {
    Napi::TypeError::New(env, "Wrong arguments (empty params string)")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

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

Napi::Value encode_exposure_params(const Napi::CallbackInfo &info)
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

  const Napi::Object exposure_params_object = info[0].As<Napi::Object>();

  dt_iop_exposure_params_t exposure_params = {EXPOSURE_MODE_DEFLICKER, 0.0f, 0.0f, 50.0f, -4.0f};

  // mode
  if (exposure_params_object.Has("mode")) {
    std::string exposure_mode_str =
        exposure_params_object.Get("mode").As<Napi::String>().Utf8Value();

    if (exposure_mode_str == "EXPOSURE_MODE_MANUAL") {
      exposure_params.mode = EXPOSURE_MODE_MANUAL;
    }
    else if (exposure_mode_str == "EXPOSURE_MODE_DEFLICKER")
    {
      exposure_params.mode = EXPOSURE_MODE_DEFLICKER;
    }
    else
    {
      Napi::TypeError::New(env, "Unknown exposure mode name").ThrowAsJavaScriptException();
      return env.Null();
    }
  }

  // black
  if (exposure_params_object.Has("black"))
  {
    exposure_params.black = exposure_params_object.Get("black").ToNumber().FloatValue();
  }

  // exposure
  if (exposure_params_object.Has("exposure"))
  {
    exposure_params.exposure = exposure_params_object.Get("exposure").ToNumber().FloatValue();
  }

  // deflicker_percentile
  if (exposure_params_object.Has("deflickerPercentile"))
  {
    exposure_params.deflicker_percentile =
        exposure_params_object.Get("deflickerPercentile").ToNumber().FloatValue();
  }

  // deflicker_target_level
  if (exposure_params_object.Has("deflickerTargetLevel"))
  {
    exposure_params.deflicker_target_level =
        exposure_params_object.Get("deflickerTargetLevel").ToNumber().FloatValue();
  }

  const char *encoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&exposure_params, sizeof(dt_iop_exposure_params_t), NULL);

  return Napi::String::New(env, encoded_params);
}
