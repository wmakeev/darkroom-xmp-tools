#include <napi.h>
#include <string>

#include "shadhi.h"
#include "tools.h"

Napi::Value decode_shadhi_params(const Napi::CallbackInfo &info)
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

  dt_iop_shadhi_params_t *params =
      (dt_iop_shadhi_params_t *)dt_exif_xmp_decode(
          encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  // order
  Napi::String order_string;

  switch (params->order)
  {
  case DT_IOP_GAUSSIAN_ZERO:
    order_string = Napi::String::New(env, "DT_IOP_GAUSSIAN_ZERO");
    break;

  case DT_IOP_GAUSSIAN_ONE:
    order_string = Napi::String::New(env, "DT_IOP_GAUSSIAN_ONE");
    break;

  case DT_IOP_GAUSSIAN_TWO:
    order_string = Napi::String::New(env, "DT_IOP_GAUSSIAN_TWO");
    break;
  };

  params_obj.Set("order", order_string);

  // shadhi_algo
  std::string algo_str;

  switch (params->shadhi_algo)
  {
  case SHADHI_ALGO_GAUSSIAN:
    algo_str = "SHADHI_ALGO_GAUSSIAN";
    break;

  case SHADHI_ALGO_BILATERAL:
    algo_str = "SHADHI_ALGO_BILATERAL";
    break;
  };

  params_obj.Set("shadhi_algo", algo_str);

  // other num fields
  params_obj.Set("radius", params->radius);
  params_obj.Set("shadows", params->shadows);
  params_obj.Set("whitepoint", params->whitepoint);
  params_obj.Set("highlights", params->highlights);
  params_obj.Set("reserved2", params->reserved2);
  params_obj.Set("compress", params->compress);
  params_obj.Set("shadows_ccorrect", params->shadows_ccorrect);
  params_obj.Set("flags", params->flags);
  params_obj.Set("low_approximation", params->low_approximation);

  params_obj.Set("shadows_ccorrect", params->shadows_ccorrect);

  return params_obj;
}

Napi::Value encode_shadhi_params(const Napi::CallbackInfo &info)
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

  const Napi::Object shadhi_params_object = info[0].As<Napi::Object>();

  dt_iop_shadhi_params_t shadhi_params =
      (dt_iop_shadhi_params_t){DT_IOP_GAUSSIAN_ZERO, 100.0f, 50.0f, 0.0f, -50.0f, 0.0f, 50.0f, 100.0f,
                               50.0f, UNBOUND_DEFAULT, 0.000001f, SHADHI_ALGO_GAUSSIAN};

  // order
  if (shadhi_params_object.Has("order"))
  {
    std::string shadhi_order_str =
        shadhi_params_object.Get("order").As<Napi::String>().Utf8Value();

    if (shadhi_order_str == "DT_IOP_GAUSSIAN_ZERO")
    {
      shadhi_params.order = DT_IOP_GAUSSIAN_ZERO;
    }
    else if (shadhi_order_str == "DT_IOP_GAUSSIAN_ONE")
    {
      shadhi_params.order = DT_IOP_GAUSSIAN_ONE;
    }
    else if (shadhi_order_str == "DT_IOP_GAUSSIAN_TWO")
    {
      shadhi_params.order = DT_IOP_GAUSSIAN_TWO;
    }
    else
    {
      Napi::TypeError::New(env, "Unknown shadhi order type")
          .ThrowAsJavaScriptException();
      return env.Null();
    }
  }

  // shadhi_algo
  if (shadhi_params_object.Has("shadhi_algo"))
  {
    std::string shadhi_algo_str =
        shadhi_params_object.Get("shadhi_algo").As<Napi::String>().Utf8Value();

    if (shadhi_algo_str == "SHADHI_ALGO_GAUSSIAN")
    {
      shadhi_params.shadhi_algo = SHADHI_ALGO_GAUSSIAN;
    }
    else if (shadhi_algo_str == "SHADHI_ALGO_BILATERAL")
    {
      shadhi_params.shadhi_algo = SHADHI_ALGO_BILATERAL;
    }
    else
    {
      Napi::TypeError::New(env, "Unknown shadhi shadhi_algo type")
          .ThrowAsJavaScriptException();
      return env.Null();
    }
  }

  // radius
  if (shadhi_params_object.Has("radius"))
  {
    shadhi_params.radius = shadhi_params_object.Get("radius").ToNumber().FloatValue();
  }

  // shadows
  if (shadhi_params_object.Has("shadows"))
  {
    shadhi_params.shadows = shadhi_params_object.Get("shadows").ToNumber().FloatValue();
  }

  // whitepoint
  if (shadhi_params_object.Has("whitepoint"))
  {
    shadhi_params.whitepoint = shadhi_params_object.Get("whitepoint").ToNumber().FloatValue();
  }

  // highlights
  if (shadhi_params_object.Has("highlights"))
  {
    shadhi_params.highlights = shadhi_params_object.Get("highlights").ToNumber().FloatValue();
  }

  // reserved2
  if (shadhi_params_object.Has("reserved2"))
  {
    shadhi_params.reserved2 = shadhi_params_object.Get("reserved2").ToNumber().FloatValue();
  }

  // compress
  if (shadhi_params_object.Has("compress"))
  {
    shadhi_params.compress = shadhi_params_object.Get("compress").ToNumber().FloatValue();
  }

  // shadows_ccorrect
  if (shadhi_params_object.Has("shadows_ccorrect"))
  {
    shadhi_params.shadows_ccorrect = shadhi_params_object.Get("shadows_ccorrect").ToNumber().FloatValue();
  }

  // highlights_ccorrect
  if (shadhi_params_object.Has("highlights_ccorrect"))
  {
    shadhi_params.highlights_ccorrect = shadhi_params_object.Get("highlights_ccorrect").ToNumber().FloatValue();
  }

  // flags
  if (shadhi_params_object.Has("flags"))
  {
    shadhi_params.flags = shadhi_params_object.Get("flags").ToNumber().Uint32Value();
  }

  // low_approximation
  if (shadhi_params_object.Has("low_approximation"))
  {
    shadhi_params.low_approximation = shadhi_params_object.Get("low_approximation").ToNumber().FloatValue();
  }

  // encode
  const char *encoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&shadhi_params, sizeof(dt_iop_shadhi_params_t), NULL);

  return Napi::String::New(env, encoded_params);
}
