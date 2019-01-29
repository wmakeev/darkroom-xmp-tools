#include <napi.h>

#ifndef EXPOSE_H
#define EXPOSE_H

enum dt_iop_exposure_mode_t
{
  EXPOSURE_MODE_MANUAL,
  EXPOSURE_MODE_DEFLICKER
};

struct dt_iop_exposure_params_t
{
  dt_iop_exposure_mode_t mode;
  float black;
  float exposure;
  float deflicker_percentile, deflicker_target_level;
};

Napi::Value decode_exposure_params(const Napi::CallbackInfo &info);

Napi::Value encode_exposure_params(const Napi::CallbackInfo &info);

#endif
