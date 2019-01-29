#include <napi.h>
#include <string>

#include "levels.h"
#include "tools.h"

Napi::Value decode_levels_params(const Napi::CallbackInfo &info)
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

  dt_iop_levels_params_t *params =
      (dt_iop_levels_params_t *)dt_exif_xmp_decode(
          encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  // mode
  Napi::String mode_string;

  switch (params->mode)
  {
  case LEVELS_MODE_MANUAL:
    mode_string = Napi::String::New(env, "LEVELS_MODE_MANUAL");
    break;

  case LEVELS_MODE_AUTOMATIC:
    mode_string = Napi::String::New(env, "LEVELS_MODE_AUTOMATIC");
    break;
  };

  params_obj.Set("mode", mode_string);

  // percentiles
  Napi::Array percentiles_array = Napi::Array::New(env, 3);

  for (u_int32_t i = 0; i < 3; i++)
  {
    percentiles_array.Set(i, params->percentiles[i]);
  }

  params_obj.Set("percentiles", percentiles_array);

  // levels
  Napi::Array levels_array = Napi::Array::New(env, 3);

  for (u_int32_t i = 0; i < 3; i++)
  {
    levels_array.Set(i, params->levels[i]);
  }

  params_obj.Set("levels", levels_array);

  return params_obj;
}

Napi::Value encode_levels_params(const Napi::CallbackInfo &info)
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

  const Napi::Object levels_params_object = info[0].As<Napi::Object>();

  dt_iop_levels_params_t levels_params =
      (dt_iop_levels_params_t){LEVELS_MODE_MANUAL, {0.0f, 50.0f, 100.0f}, {0.0f, 0.5f, 1.0f}};

  // mode
  if (levels_params_object.Has("mode"))
  {
    std::string levels_mode_str =
        levels_params_object.Get("mode").As<Napi::String>().Utf8Value();

    if (levels_mode_str == "LEVELS_MODE_MANUAL")
    {
      levels_params.mode = LEVELS_MODE_MANUAL;
    }
    else if (levels_mode_str == "LEVELS_MODE_AUTOMATIC")
    {
      levels_params.mode = LEVELS_MODE_AUTOMATIC;
    }
    else
    {
      Napi::TypeError::New(env, "Unknown levels mode name")
          .ThrowAsJavaScriptException();
      return env.Null();
    }
  }

  // percentiles
  if (levels_params_object.Has("percentiles"))
  {
    Napi::Value percentiles_value = levels_params_object.Get("percentiles");

    if (!percentiles_value.IsArray())
    {
      Napi::TypeError::New(env, "percentiles expected to be Array")
          .ThrowAsJavaScriptException();
      return env.Null();
    }

    Napi::Object percentiles_obj = percentiles_value.ToObject();

    Napi::Value percentile;

    for (size_t i = 0; i < 3; i++)
    {
      percentile = percentiles_obj.Get(i);

      if (percentile.IsNumber())
      {
        levels_params.percentiles[i] = percentile.ToNumber().FloatValue();
      }
      else
      {
        Napi::TypeError::New(env, "percentiles expected to be numbers Array")
            .ThrowAsJavaScriptException();
        return env.Null();
      }
    }
  }

  // levels
  if (levels_params_object.Has("levels"))
  {
    Napi::Value levels_value = levels_params_object.Get("levels");

    if (!levels_value.IsArray())
    {
      Napi::TypeError::New(env, "levels expected to be Array")
          .ThrowAsJavaScriptException();
      return env.Null();
    }

    Napi::Object levels_obj = levels_value.ToObject();

    Napi::Value level;

    for (size_t i = 0; i < 3; i++)
    {
      level = levels_obj.Get(i);

      if (level.IsNumber())
      {
        levels_params.levels[i] = level.ToNumber().FloatValue();
      }
      else
      {
        Napi::TypeError::New(env, "levels expected to be numbers Array")
            .ThrowAsJavaScriptException();
        return env.Null();
      }
    }
  }

  // encode
  const char *encoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&levels_params, sizeof(dt_iop_levels_params_t), NULL);

  return Napi::String::New(env, encoded_params);
}
