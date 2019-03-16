#include <napi.h>
#include <string>

#include "basecurve.h"
#include "tools.h"

Napi::Value decode_basecurve_params(const Napi::CallbackInfo &info)
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

  dt_iop_basecurve_params_t *params =
      (dt_iop_basecurve_params_t *)dt_exif_xmp_decode(
          encoded_params, strlen(encoded_params), &params_len);

  Napi::Object params_obj = Napi::Object::New(env);

  // basecurve_nodes
  Napi::Array basecurve_nodes_array = Napi::Array::New(env);
  for (int i = 0; i < 3; i++)
  {
    basecurve_nodes_array.Set(i, params->basecurve_nodes[i]);
  }
  params_obj.Set("basecurve_nodes", basecurve_nodes_array);

  // basecurve_type
  Napi::Array basecurve_type_array = Napi::Array::New(env);
  for (int i = 0; i < 3; i++)
  {
    basecurve_type_array.Set(i, params->basecurve_type[i]);
  }
  params_obj.Set("basecurve_type", basecurve_type_array);

  // basecurve
  Napi::Array basecurve_array = Napi::Array::New(env);

  for (int i = 0; i < 3; i++)
  {
    Napi::Array basecurve_sub_array = Napi::Array::New(env);
    int nodes_num = params->basecurve_nodes[i];
    if (nodes_num > 0) {
      for (int j = 0; j < nodes_num; j++)
      {
        Napi::Object basecurve_node = Napi::Object::New(env);
        basecurve_node.Set("x", params->basecurve[i][j].x);
        basecurve_node.Set("y", params->basecurve[i][j].y);
        basecurve_sub_array.Set(j, basecurve_node);
      }
    }
    basecurve_array.Set(i, basecurve_sub_array);
  }

  params_obj.Set("basecurve", basecurve_array);

  // exposure_fusion
  params_obj.Set("exposure_fusion", params->exposure_fusion);

  // exposure_stops
  params_obj.Set("exposure_stops", params->exposure_stops);

  // exposure_bias
  params_obj.Set("exposure_bias", params->exposure_bias);

  return params_obj;
}

Napi::Value encode_basecurve_params(const Napi::CallbackInfo &info)
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

  const Napi::Object basecurve_params_object = info[0].As<Napi::Object>();

  dt_iop_basecurve_params_t basecurve_params =
      (dt_iop_basecurve_params_t){
          {
              {// three curves (L, a, b) with a number of nodes
               {0.0, 0.0},
               {1.0, 1.0}},
          },
          {2, 0, 0}, // number of nodes per curve
          {MONOTONE_HERMITE, MONOTONE_HERMITE, MONOTONE_HERMITE},
          0,
          1.0f,
          1.0f // no exposure fusion, but if we would, add one stop
      };

  // basecurve_nodes
  if (basecurve_params_object.Has("basecurve_nodes"))
  {
    Napi::Value basecurve_nodes_value =
        basecurve_params_object.Get("basecurve_nodes");
    if (!basecurve_nodes_value.IsArray())
    {
      Napi::TypeError::New(env, "basecurve basecurve_nodes field expected to be Array")
          .ThrowAsJavaScriptException();
      return env.Null();
    };

    Napi::Object basecurve_nodes_object = basecurve_nodes_value.ToObject();

    for (int i = 0; i < 3; i++)
    {
      Napi::Value nodes_num = basecurve_nodes_object.Get(i);
      if (!nodes_num.IsNumber())
      {
        Napi::TypeError::New(env, "basecurve basecurve_nodes value expected to be Number")
            .ThrowAsJavaScriptException();
        return env.Null();
      };
      basecurve_params.basecurve_nodes[i] = nodes_num.ToNumber().Int32Value();
    }
  }

  // basecurve_type
  if (basecurve_params_object.Has("basecurve_type"))
  {
    Napi::Value basecurve_type_value =
        basecurve_params_object.Get("basecurve_type");
    if (!basecurve_type_value.IsArray())
    {
      Napi::TypeError::New(env, "basecurve basecurve_type field expected to be Array")
          .ThrowAsJavaScriptException();
      return env.Null();
    };

    Napi::Object basecurve_type_object = basecurve_type_value.ToObject();

    for (int i = 0; i < 3; i++)
    {
      Napi::Value nodes_type = basecurve_type_object.Get(i);
      if (!nodes_type.IsNumber())
      {
        Napi::TypeError::New(env, "basecurve basecurve_type value expected to be Number")
            .ThrowAsJavaScriptException();
        return env.Null();
      };
      basecurve_params.basecurve_type[i] = nodes_type.ToNumber().Int32Value();
    }
  }

  // basecurve
  if (basecurve_params_object.Has("basecurve"))
  {
    Napi::Value basecurve_value = basecurve_params_object.Get("basecurve");
    if (!basecurve_value.IsArray())
    {
      Napi::TypeError::New(env, "basecurve basecurve field expected to be Array")
          .ThrowAsJavaScriptException();
      return env.Null();
    };

    Napi::Object basecurve_object =
        basecurve_params_object.Get("basecurve").ToObject();

    for (int i = 0; i < 3; i++)
    {
      Napi::Value basecurve_nodes_value = basecurve_object.Get(i);
      if (!basecurve_nodes_value.IsArray())
      {
        Napi::TypeError::New(env, "basecurve basecurve value expected to be Array")
            .ThrowAsJavaScriptException();
        return env.Null();
      };

      Napi::Object basecurve_nodes_array = basecurve_nodes_value.ToObject();

      for (int j = 0; j < basecurve_params.basecurve_nodes[i]; j++)
      {
        Napi::Value basecurve_node_value = basecurve_nodes_array.Get(j);
        if (!basecurve_node_value.IsObject())
        {
          Napi::TypeError::New(env, "basecurve basecurve sub array item expected to be Object")
              .ThrowAsJavaScriptException();
          return env.Null();
        };

        Napi::Object basecurve_node_object = basecurve_node_value.ToObject();

        dt_iop_basecurve_node_t node;

        // x
        if (!basecurve_node_object.Has("x"))
        {
          Napi::TypeError::New(env, "basecurve node expected to have x field")
              .ThrowAsJavaScriptException();
          return env.Null();
        };

        Napi::Value node_x_value = basecurve_node_object.Get("x");
        if (!node_x_value.IsNumber())
        {
          Napi::TypeError::New(env, "basecurve node x field expected to be Number")
              .ThrowAsJavaScriptException();
          return env.Null();
        };
        node.x = node_x_value.ToNumber().FloatValue();

        // y
        if (!basecurve_node_object.Has("y"))
        {
          Napi::TypeError::New(env, "basecurve node expected to have y field")
              .ThrowAsJavaScriptException();
          return env.Null();
        };

        Napi::Value node_y_value = basecurve_node_object.Get("y");
        if (!node_y_value.IsNumber())
        {
          Napi::TypeError::New(env, "basecurve node y field expected to be Number")
              .ThrowAsJavaScriptException();
          return env.Null();
        };
        node.y = node_y_value.ToNumber().FloatValue();

        basecurve_params.basecurve[i][j] = node;
      }
    }
  }

  // exposure_fusion
  if (basecurve_params_object.Has("exposure_fusion"))
  {
    basecurve_params.exposure_fusion =
        basecurve_params_object.Get("exposure_fusion").ToNumber().Int32Value();
  }

  // exposure_stops
  if (basecurve_params_object.Has("exposure_stops"))
  {
    basecurve_params.exposure_stops =
        basecurve_params_object.Get("exposure_stops").ToNumber().FloatValue();
  }

  // exposure_bias
  if (basecurve_params_object.Has("exposure_bias"))
  {
    basecurve_params.exposure_bias =
        basecurve_params_object.Get("exposure_bias").ToNumber().FloatValue();
  }

  // encode
  const char *encoded_params = dt_exif_xmp_encode(
      (const unsigned char *)&basecurve_params, sizeof(dt_iop_basecurve_params_t), NULL);

  return Napi::String::New(env, encoded_params);
}
