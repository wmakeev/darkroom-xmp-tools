#include <napi.h>
#include <string>

#include "blend.hpp"
#include "tools.hpp"

static dt_develop_blend_params_t _default_blendop_params = {
    DEVELOP_MASK_DISABLED,
    DEVELOP_BLEND_NORMAL2,
    100.0f,
    DEVELOP_COMBINE_NORM_EXCL,
    0,
    0,
    0.0f,
    {0, 0, 0, 0},
    {0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f}};

Napi::Value decode_blend_params(const Napi::CallbackInfo &info)
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

  dt_develop_blend_params_t *params = (dt_develop_blend_params_t *)dt_exif_xmp_decode(
      encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  params_obj.Set(
      Napi::String::New(env, "maskMode"),
      Napi::Number::New(env, params->mask_mode));

  params_obj.Set(
      Napi::String::New(env, "blendMode"),
      Napi::Number::New(env, params->blend_mode));

  params_obj.Set(
      Napi::String::New(env, "opacity"),
      Napi::Number::New(env, params->opacity));

  params_obj.Set(
      Napi::String::New(env, "maskCombine"),
      Napi::Number::New(env, params->mask_combine));

  params_obj.Set(
      Napi::String::New(env, "maskId"),
      Napi::Number::New(env, params->mask_id));

  params_obj.Set(
      Napi::String::New(env, "blendif"),
      Napi::Number::New(env, params->blendif));

  params_obj.Set(
      Napi::String::New(env, "radius"),
      Napi::Number::New(env, params->radius));

  // reserved
  Napi::Array reserved = Napi::Array::New(env, 4);

  for (size_t i = 0; i < 4; i++)
  {
    reserved.Set(i, Napi::Number::New(env, params->reserved[i]));
  }

  params_obj.Set(Napi::String::New(env, "reserved"), reserved);

  // blendif_parameters
  const int blendif_parameters_size = 4 * DEVELOP_BLENDIF_SIZE;
  Napi::Array blendif_parameters = Napi::Array::New(env, blendif_parameters_size);

  for (size_t i = 0; i < blendif_parameters_size; i++)
  {
    blendif_parameters.Set(i, Napi::Number::New(env, params->blendif_parameters[i]));
  }

  params_obj.Set(Napi::String::New(env, "blendifParameters"), blendif_parameters);

  return params_obj;
}

Napi::Value encode_blend_params(const Napi::CallbackInfo &info)
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

  const Napi::Object blend_params_object = info[0].As<Napi::Object>();

  int blend_params_size = sizeof(dt_develop_blend_params_t);
  dt_develop_blend_params_t *blend_params = (dt_develop_blend_params_t *)malloc(blend_params_size);
  memcpy(blend_params, &_default_blendop_params, blend_params_size);

  // mask_mode
  if (blend_params_object.Has("maskMode"))
  {
    blend_params->mask_mode =
        blend_params_object.Get("maskMode").ToNumber().Uint32Value();
  }

  // blend_mode
  if (blend_params_object.Has("blendMode"))
  {
    blend_params->blend_mode =
        blend_params_object.Get("blendMode").ToNumber().Uint32Value();
  }

  // opacity
  if (blend_params_object.Has("opacity"))
  {
    blend_params->opacity =
        blend_params_object.Get("opacity").ToNumber().FloatValue();
  }

  // mask_combine
  if (blend_params_object.Has("maskCombine"))
  {
    blend_params->mask_combine =
        blend_params_object.Get("maskCombine").ToNumber().Uint32Value();
  }

  // mask_id
  if (blend_params_object.Has("maskId"))
  {
    blend_params->mask_id =
        blend_params_object.Get("maskId").ToNumber().Uint32Value();
  }

  // blendif
  if (blend_params_object.Has("blendif"))
  {
    blend_params->blendif =
        blend_params_object.Get("blendif").ToNumber().Uint32Value();
  }

  // radius
  if (blend_params_object.Has("radius"))
  {
    blend_params->radius =
        blend_params_object.Get("radius").ToNumber().FloatValue();
  }

  // blendif_parameters
  if (blend_params_object.Has("blendifParameters"))
  {
    const int blendif_parameters_size = 4 * DEVELOP_BLENDIF_SIZE;
    Napi::Value blendif_parameters_value = blend_params_object.Get("blendifParameters");

    if (!blendif_parameters_value.IsArray())
    {
      Napi::TypeError::New(env, "blendifParameters expected to be Array")
          .ThrowAsJavaScriptException();
      return env.Null();
    }

    Napi::Object blendif_parameters_obj = blendif_parameters_value.ToObject();

    Napi::Value blendif_parameter;

    for (size_t i = 0; i < blendif_parameters_size; i++)
    {
      blendif_parameter = blendif_parameters_obj.Get(i);

      if (blendif_parameter.IsNumber())
      {
        blend_params->blendif_parameters[i] =
            blendif_parameter.ToNumber().FloatValue();
      }
      else
      {
        Napi::TypeError::New(env, "blendifParameters expected to be numbers Array")
            .ThrowAsJavaScriptException();
        return env.Null();
      }
    }
  }

  const char *encoded_params = dt_exif_xmp_encode(
      (const unsigned char *)blend_params, sizeof(dt_develop_blend_params_t), NULL);

  return Napi::String::New(env, encoded_params);
}
