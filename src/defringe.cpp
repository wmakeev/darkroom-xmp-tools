#include <napi.h>
#include <string>

#include "defringe.h"
#include "tools.h"

Napi::Value decode_defringe_params(const Napi::CallbackInfo &info)
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

  dt_iop_defringe_params_t *params = (dt_iop_defringe_params_t *)dt_exif_xmp_decode(
      encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  // radius
  params_obj.Set("radius", params->radius);

  // thresh
  params_obj.Set("thresh", params->thresh);

  // op_mode
  std::string op_mode_str;

  switch (params->op_mode)
  {
  case MODE_GLOBAL_AVERAGE:
    op_mode_str = "MODE_GLOBAL_AVERAGE";
    break;

  case MODE_LOCAL_AVERAGE:
    op_mode_str = "MODE_LOCAL_AVERAGE";
    break;

  case MODE_STATIC:
    op_mode_str = "MODE_STATIC";
    break;
  };

  params_obj.Set("op_mode", op_mode_str);

  return params_obj;
}

Napi::Value encode_defringe_params(const Napi::CallbackInfo &info)
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

  const Napi::Object defringe_params_object = info[0].As<Napi::Object>();

  dt_iop_defringe_params_t defringe_params = {4.0, 20.0, MODE_GLOBAL_AVERAGE};

  // mode
  if (defringe_params_object.Has("op_mode"))
  {
    std::string exposure_mode_str =
        defringe_params_object.Get("op_mode").As<Napi::String>().Utf8Value();

    if (exposure_mode_str == "MODE_GLOBAL_AVERAGE")
    {
      defringe_params.op_mode = MODE_GLOBAL_AVERAGE;
    }
    else if (exposure_mode_str == "MODE_LOCAL_AVERAGE")
    {
      defringe_params.op_mode = MODE_LOCAL_AVERAGE;
    }
    else if (exposure_mode_str == "MODE_STATIC")
    {
      defringe_params.op_mode = MODE_STATIC;
    }
    else
    {
      Napi::TypeError::New(env, "Unknown defringe op_mode type")
          .ThrowAsJavaScriptException();
      return env.Null();
    }
  }

  // radius
  if (defringe_params_object.Has("radius"))
  {
    defringe_params.radius = defringe_params_object.Get("radius").ToNumber().FloatValue();
  }

  // thresh
  if (defringe_params_object.Has("thresh"))
  {
    defringe_params.thresh = defringe_params_object.Get("thresh").ToNumber().FloatValue();
  }

  const char *encoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&defringe_params, sizeof(dt_iop_defringe_params_t), NULL);

  return Napi::String::New(env, encoded_params);
}
