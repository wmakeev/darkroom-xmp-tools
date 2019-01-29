#include <napi.h>
#include <string>

#include "sharpen.h"
#include "tools.h"

Napi::Value decode_sharpen_params(const Napi::CallbackInfo &info)
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

  const char *encoded_params = info[0].As<Napi::String>().Utf8Value().c_str();

  int params_len;

  dt_iop_sharpen_params_t *params =
      (dt_iop_sharpen_params_t *)dt_exif_xmp_decode(
          encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  // radius
  params_obj.Set("radius", params->radius);

  // amount
  params_obj.Set("amount", params->amount);

  // threshold
  params_obj.Set("threshold", params->threshold);

  return params_obj;
}

Napi::Value encode_sharpen_params(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsObject())
  {
    Napi::TypeError::New(env, "Wrong arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  const Napi::Object sharpen_params_object = info[0].As<Napi::Object>();

  dt_iop_sharpen_params_t sharpen_params = {2.0, 0.5, 0.5};

  // radius
  if (sharpen_params_object.Has("radius"))
  {
    sharpen_params.radius =
        sharpen_params_object.Get("radius").ToNumber().FloatValue();
  }

  // amount
  if (sharpen_params_object.Has("amount"))
  {
    sharpen_params.amount =
        sharpen_params_object.Get("amount").ToNumber().FloatValue();
  }

  // threshold
  if (sharpen_params_object.Has("threshold"))
  {
    sharpen_params.threshold =
        sharpen_params_object.Get("threshold").ToNumber().FloatValue();
  }

  const char *encoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&sharpen_params, sizeof(dt_iop_sharpen_params_t), NULL);

  return Napi::String::New(env, encoded_params);
}
