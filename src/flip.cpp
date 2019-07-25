#include <napi.h>
#include <string>

#include "flip.h"
#include "tools.h"

Napi::Value decode_flip_params(const Napi::CallbackInfo &info)
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

  dt_iop_flip_params_t *params =
      (dt_iop_flip_params_t *)dt_exif_xmp_decode(
          encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  // orientation
  std::string orientation_string;

  switch (params->orientation)
  {
  case ORIENTATION_NULL:
    orientation_string = "ORIENTATION_NULL";
    break;

  case ORIENTATION_NONE:
    orientation_string = "ORIENTATION_NONE";
    break;

  case ORIENTATION_FLIP_Y:
    orientation_string = "ORIENTATION_FLIP_Y";
    break;

  case ORIENTATION_FLIP_X:
    orientation_string = "ORIENTATION_FLIP_X";
    break;

  case ORIENTATION_SWAP_XY:
    orientation_string = "ORIENTATION_SWAP_XY";
    break;

  case ORIENTATION_ROTATE_180_DEG:
    orientation_string = "ORIENTATION_ROTATE_180_DEG";
    break;

  case ORIENTATION_ROTATE_CCW_90_DEG:
    orientation_string = "ORIENTATION_ROTATE_CCW_90_DEG";
    break;

  case ORIENTATION_ROTATE_CW_90_DEG:
    orientation_string = "ORIENTATION_ROTATE_CW_90_DEG";
    break;

  case ORIENTATION_421:
    orientation_string = "ORIENTATION_421";
    break;

  default:
    Napi::TypeError::New(env, "Unknown orientation")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  params_obj.Set("orientation", orientation_string);

  return params_obj;
}

Napi::Value encode_flip_params(const Napi::CallbackInfo &info)
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

  const Napi::Object params_object = info[0].As<Napi::Object>();

  dt_iop_flip_params_t params = (dt_iop_flip_params_t){ORIENTATION_NONE};

  // orientation
  if (params_object.Has("orientation"))
  {
    std::string orientation_str =
        params_object.Get("orientation").As<Napi::String>().Utf8Value();

    if (orientation_str == "ORIENTATION_NULL")
    {
      params.orientation = ORIENTATION_NULL;
    }
    else if (orientation_str == "ORIENTATION_NONE")
    {
      params.orientation = ORIENTATION_NONE;
    }
    else if (orientation_str == "ORIENTATION_FLIP_Y")
    {
      params.orientation = ORIENTATION_FLIP_Y;
    }
    else if (orientation_str == "ORIENTATION_SWAP_XY")
    {
      params.orientation = ORIENTATION_SWAP_XY;
    }
    else if (orientation_str == "ORIENTATION_ROTATE_180_DEG")
    {
      params.orientation = ORIENTATION_ROTATE_180_DEG;
    }
    else if (orientation_str == "ORIENTATION_ROTATE_CCW_90_DEG")
    {
      params.orientation = ORIENTATION_ROTATE_CCW_90_DEG;
    }
    else if (orientation_str == "ORIENTATION_ROTATE_CW_90_DEG")
    {
      params.orientation = ORIENTATION_ROTATE_CW_90_DEG;
    }
    else if (orientation_str == "ORIENTATION_421")
    {
      params.orientation = ORIENTATION_421;
    }
    else
    {
      Napi::TypeError::New(env, "Unknown orientation type")
          .ThrowAsJavaScriptException();
      return env.Null();
    }
  }

  // encode
  const char *encoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&params, sizeof(dt_iop_flip_params_t), NULL);

  return Napi::String::New(env, encoded_params);
}
