#ifndef DEFRINGE_H
#define DEFRINGE_H

#include <napi.h>

enum dt_iop_defringe_mode_t
{
  MODE_GLOBAL_AVERAGE = 0,
  MODE_LOCAL_AVERAGE = 1,
  MODE_STATIC = 2
};

struct dt_iop_defringe_params_t
{
  float radius;
  float thresh;
  dt_iop_defringe_mode_t op_mode;
};

Napi::Value decode_defringe_params(const Napi::CallbackInfo &info);

Napi::Value encode_defringe_params(const Napi::CallbackInfo &info);

#endif
