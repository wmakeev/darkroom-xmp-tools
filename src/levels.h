#include <napi.h>

#ifndef LEVELS_H
#define LEVELS_H

enum dt_iop_levels_mode_t
{
  LEVELS_MODE_MANUAL,
  LEVELS_MODE_AUTOMATIC
};

struct dt_iop_levels_params_t
{
  dt_iop_levels_mode_t mode;
  float percentiles[3];
  float levels[3];
};

Napi::Value decode_levels_params(const Napi::CallbackInfo &info);

Napi::Value encode_levels_params(const Napi::CallbackInfo &info);

#endif
