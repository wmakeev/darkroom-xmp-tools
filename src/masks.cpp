#include <napi.h>
#include <string>

#include "masks.h"
#include "tools.h"

Napi::Value decode_mask_points(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 3)
  {
    Napi::TypeError::New(env, "Wrong number of arguments (expected three arguments)")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  // maskType
  if (!info[0].IsNumber())
  {
    Napi::TypeError::New(env, "maskType argument expected to be a number")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  int mask_type = info[0].ToNumber().Int32Value();

  // numberPoints
  if (!info[1].IsNumber())
  {
    Napi::TypeError::New(env, "numberPoints argument expected to be a number")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  int nb_points = info[1].ToNumber().Int32Value();

  // encodedPoints
  if (!info[2].IsString())
  {
    Napi::TypeError::New(env, "encodedPoints argument expected to be a string")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  const char *encoded_points_blob = info[2].ToString().Utf8Value().c_str();

  unsigned char *points_blob = dt_exif_xmp_decode(
      encoded_points_blob,
      strlen(encoded_points_blob), NULL);

  // GList *points_list = NULL;

  Napi::Array points_array = Napi::Array::New(env, nb_points);

  // CIRCLE
  if (mask_type & DT_MASKS_CIRCLE)
  {
    dt_masks_point_circle_t *circle =
        (dt_masks_point_circle_t *)malloc(sizeof(dt_masks_point_circle_t));
    memcpy(circle, points_blob, sizeof(dt_masks_point_circle_t));
    // points_list = g_list_append(points_list, circle);

    // circle
    Napi::Object circle_point_obj = Napi::Object::New(env);

    // circle.center[]
    Napi::Array center_array = Napi::Array::New(env, 2);
    center_array.Set((u_int32_t)0, Napi::Number::New(env, circle->center[0]));
    center_array.Set((u_int32_t)1, Napi::Number::New(env, circle->center[1]));
    circle_point_obj.Set("center", center_array);

    // circle.radius
    circle_point_obj.Set("radius", Napi::Number::New(env, circle->radius));

    // circle.border
    circle_point_obj.Set("border", Napi::Number::New(env, circle->border));

    points_array.Set((u_int32_t)0, circle_point_obj);
  }
  // PATH
  else if (mask_type & DT_MASKS_PATH)
  {
    dt_masks_point_path_t *ptbuf = (dt_masks_point_path_t *)points_blob;
    for (int i = 0; i < nb_points; i++)
    {
      dt_masks_point_path_t *point = (dt_masks_point_path_t *)malloc(sizeof(dt_masks_point_path_t));
      memcpy(point, ptbuf + i, sizeof(dt_masks_point_path_t));
      // points_list = g_list_append(points_list, point);

      // path
      Napi::Object path_point_obj = Napi::Object::New(env);

      // path.corner[]
      Napi::Array corner_array = Napi::Array::New(env, 2);
      corner_array.Set((u_int32_t)0, Napi::Number::New(env, point->corner[0]));
      corner_array.Set((u_int32_t)1, Napi::Number::New(env, point->corner[1]));
      path_point_obj.Set("corner", corner_array);

      // path.ctrl1[]
      Napi::Array ctrl1_array = Napi::Array::New(env, 2);
      ctrl1_array.Set((u_int32_t)0, Napi::Number::New(env, point->ctrl1[0]));
      ctrl1_array.Set((u_int32_t)1, Napi::Number::New(env, point->ctrl1[1]));
      path_point_obj.Set("ctrl1", ctrl1_array);

      // path.ctrl2[]
      Napi::Array ctrl2_array = Napi::Array::New(env, 2);
      ctrl2_array.Set((u_int32_t)0, Napi::Number::New(env, point->ctrl2[0]));
      ctrl2_array.Set((u_int32_t)1, Napi::Number::New(env, point->ctrl2[1]));
      path_point_obj.Set("ctrl2", ctrl2_array);

      // path.border[]
      Napi::Array border_array = Napi::Array::New(env, 2);
      border_array.Set((u_int32_t)0, Napi::Number::New(env, point->border[0]));
      border_array.Set((u_int32_t)1, Napi::Number::New(env, point->border[1]));
      path_point_obj.Set("border", border_array);

      // path.state
      switch (point->state)
      {
      case DT_MASKS_POINT_STATE_NORMAL:
        path_point_obj.Set("state", "DT_MASKS_POINT_STATE_NORMAL");
        break;

      case DT_MASKS_POINT_STATE_USER:
        path_point_obj.Set("state", "DT_MASKS_POINT_STATE_USER");
        break;
      }

      points_array.Set(i, path_point_obj);
    }
  }
  // GROUP
  else if (mask_type & DT_MASKS_GROUP)
  {
    // dt_masks_point_group_t *ptbuf = (dt_masks_point_group_t *)points_blob;
    // for (int i = 0; i < nb_points; i++)
    // {
    //   dt_masks_point_group_t *point = (dt_masks_point_group_t *)malloc(sizeof(dt_masks_point_group_t));
    //   memcpy(point, ptbuf + i, sizeof(dt_masks_point_group_t));
    //   points_list = g_list_append(points_list, point);
    // }
    Napi::TypeError::New(env, "type DT_MASKS_GROUP not supported yet")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  // GRADIENT
  else if (mask_type & DT_MASKS_GRADIENT)
  {
    dt_masks_point_gradient_t *gradient = (dt_masks_point_gradient_t *)malloc(sizeof(dt_masks_point_gradient_t));
    memcpy(gradient, points_blob, sizeof(dt_masks_point_gradient_t));
    //points_list = g_list_append(points_list, gradient);

    // gradient
    Napi::Object gradient_point_obj = Napi::Object::New(env);

    // gradient.anchor[2]
    Napi::Array anchor_array = Napi::Array::New(env, 2);
    anchor_array.Set((u_int32_t)0, Napi::Number::New(env, gradient->anchor[0]));
    anchor_array.Set((u_int32_t)1, Napi::Number::New(env, gradient->anchor[1]));
    gradient_point_obj.Set("anchor", anchor_array);

    // gradient.rotation
    gradient_point_obj.Set("rotation", Napi::Number::New(env, gradient->rotation));

    // gradient.compression
    gradient_point_obj.Set("compression", Napi::Number::New(env, gradient->compression));

    // gradient.steepness
    gradient_point_obj.Set("steepness", Napi::Number::New(env, gradient->steepness));

    points_array.Set((u_int32_t)0, gradient_point_obj);
  }
  // ELLIPSE
  else if (mask_type & DT_MASKS_ELLIPSE)
  {
    dt_masks_point_ellipse_t *ellipse = (dt_masks_point_ellipse_t *)malloc(sizeof(dt_masks_point_ellipse_t));
    memcpy(ellipse, points_blob, sizeof(dt_masks_point_ellipse_t));
    // points_list = g_list_append(points_list, ellipse);

    // ellipse
    Napi::Object ellipse_point_obj = Napi::Object::New(env);

    // ellipse.center[]
    Napi::Array center_array = Napi::Array::New(env, 2);
    center_array.Set((u_int32_t)0, Napi::Number::New(env, ellipse->center[0]));
    center_array.Set((u_int32_t)1, Napi::Number::New(env, ellipse->center[1]));
    ellipse_point_obj.Set("center", center_array);

    // ellipse.radius
    Napi::Array radius_array = Napi::Array::New(env, 2);
    radius_array.Set((u_int32_t)0, Napi::Number::New(env, ellipse->radius[0]));
    radius_array.Set((u_int32_t)1, Napi::Number::New(env, ellipse->radius[1]));
    ellipse_point_obj.Set("radius", radius_array);

    // ellipse.rotation
    ellipse_point_obj.Set("rotation", Napi::Number::New(env, ellipse->rotation));

    // ellipse.border
    ellipse_point_obj.Set("border", Napi::Number::New(env, ellipse->border));

    // ellipse.flags
    switch (ellipse->flags)
    {
    case DT_MASKS_ELLIPSE_EQUIDISTANT:
      ellipse_point_obj.Set("flags", "DT_MASKS_ELLIPSE_EQUIDISTANT");
      break;

    case DT_MASKS_ELLIPSE_PROPORTIONAL:
      ellipse_point_obj.Set("flags", "DT_MASKS_ELLIPSE_PROPORTIONAL");
      break;
    }

    points_array.Set((u_int32_t)0, ellipse_point_obj);
  }
  // BRUSH
  else if (mask_type & DT_MASKS_BRUSH)
  {
    // dt_masks_point_brush_t *ptbuf = (dt_masks_point_brush_t *)points_blob;
    // for (int i = 0; i < nb_points; i++)
    // {
    //   dt_masks_point_brush_t *point = (dt_masks_point_brush_t *)malloc(sizeof(dt_masks_point_brush_t));
    //   memcpy(point, ptbuf + i, sizeof(dt_masks_point_brush_t));
    //   points_list = g_list_append(points_list, point);
    // }
    Napi::TypeError::New(env, "type DT_MASKS_BRUSH not supported yet").ThrowAsJavaScriptException();
    return env.Null();
  }
  else
  {
    Napi::TypeError::New(env, "Unknown maskType").ThrowAsJavaScriptException();
    return env.Null();
  }

  return points_array;
}

Napi::Value encode_mask_points(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 2)
  {
    Napi::TypeError::New(env, "Wrong number of arguments (expected tow arguments)")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  // maskType
  if (!info[0].IsNumber())
  {
    Napi::TypeError::New(env, "maskType argument expected to be a number")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  int mask_type = info[0].ToNumber().Int32Value();

  const char *encoded_points = nullptr;
  Napi::Object point_object;

  // points
  if (!info[1].IsArray())
  {
    Napi::TypeError::New(env, "points argument expected to be an array")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  Napi::Array points_array = info[1].ToObject().As<Napi::Array>();

  // CIRCLE
  if (mask_type & DT_MASKS_CIRCLE)
  {
    dt_masks_point_circle_t *circle =
        (dt_masks_point_circle_t *)malloc(sizeof(dt_masks_point_circle_t));

    point_object = points_array.Get((u_int32_t)0).ToObject();

    circle->border = point_object.Get("border").ToNumber().FloatValue();

    for (int i = 0; i < 2; i++)
      circle->center[i] =
          point_object.Get("center").ToObject().Get(i).ToNumber().FloatValue();

    circle->radius = point_object.Get("radius").ToNumber().FloatValue();

    encoded_points = dt_exif_xmp_encode(
        (const unsigned char *)circle, sizeof(dt_masks_point_circle_t), NULL);
  }
  // PATH
  else if (mask_type & DT_MASKS_PATH)
  {
    Napi::TypeError::New(env, "type DT_MASKS_PATH not supported yet")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  // GROUP
  else if (mask_type & DT_MASKS_GROUP)
  {
    Napi::TypeError::New(env, "type DT_MASKS_GROUP not supported yet")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  // GRADIENT
  else if (mask_type & DT_MASKS_GRADIENT)
  {
    dt_masks_point_gradient_t *gradient =
        (dt_masks_point_gradient_t *)malloc(sizeof(dt_masks_point_gradient_t));

    point_object = points_array.Get((u_int32_t)0).ToObject();

    for (int i = 0; i < 2; i++)
      gradient->anchor[i] =
          point_object.Get("anchor").ToObject().Get(i).ToNumber().FloatValue();

    gradient->compression = point_object.Get("compression").ToNumber().FloatValue();

    gradient->rotation = point_object.Get("rotation").ToNumber().FloatValue();

    gradient->steepness = point_object.Get("steepness").ToNumber().FloatValue();

    encoded_points = dt_exif_xmp_encode(
        (const unsigned char *)gradient, sizeof(dt_masks_point_gradient_t), NULL);
  }
  // ELLIPSE
  else if (mask_type & DT_MASKS_ELLIPSE)
  {
    dt_masks_point_ellipse_t *ellipse =
        (dt_masks_point_ellipse_t *)malloc(sizeof(dt_masks_point_ellipse_t));

    point_object = points_array.Get((u_int32_t)0).ToObject();

    ellipse->border = point_object.Get("border").ToNumber().FloatValue();

    for (int i = 0; i < 2; i++)
      ellipse->center[i] =
          point_object.Get("center").ToObject().Get(i).ToNumber().FloatValue();

    std::string flags_str = point_object.Get("flags").ToString().Utf8Value();
    if (flags_str == "DT_MASKS_ELLIPSE_EQUIDISTANT")
      ellipse->flags = DT_MASKS_ELLIPSE_EQUIDISTANT;
    else if (flags_str == "DT_MASKS_ELLIPSE_PROPORTIONAL")
      ellipse->flags = DT_MASKS_ELLIPSE_PROPORTIONAL;
    else
    {
      Napi::TypeError::New(env, "Wrong point flags field value").ThrowAsJavaScriptException();
      return env.Null();
    }

    for (int i = 0; i < 2; i++)
      ellipse->radius[i] =
          point_object.Get("radius").ToObject().Get(i).ToNumber().FloatValue();

    ellipse->rotation = point_object.Get("rotation").ToNumber().FloatValue();

    encoded_points = dt_exif_xmp_encode(
        (const unsigned char *)ellipse, sizeof(dt_masks_point_ellipse_t), NULL);
  }
  else if (mask_type & DT_MASKS_BRUSH)
  {
    Napi::TypeError::New(env, "type DT_MASKS_BRUSH not supported yet").ThrowAsJavaScriptException();
    return env.Null();
  }
  else
  {
    Napi::TypeError::New(env, "Unknown maskType").ThrowAsJavaScriptException();
    return env.Null();
  }

  return Napi::String::New(env, encoded_points);
}
