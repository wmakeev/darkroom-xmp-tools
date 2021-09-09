#include <napi.h>

#ifndef CROP_H
#define CROP_H

typedef struct dt_iop_crop_params_t
{
  float cx;    // $MIN: 0.0 $MAX: 1.0 $DESCRIPTION: "left"
  float cy;    // $MIN: 0.0 $MAX: 1.0 $DESCRIPTION: "top"
  float cw;    // $MIN: 0.0 $MAX: 1.0 $DESCRIPTION: "right"
  float ch;    // $MIN: 0.0 $MAX: 1.0 $DESCRIPTION: "bottom"
  int ratio_n; // $DEFAULT: -1
  int ratio_d; // $DEFAULT: -1
} dt_iop_crop_params_t;

Napi::Value decode_crop_params(const Napi::CallbackInfo &info);

Napi::Value encode_crop_params(const Napi::CallbackInfo &info);

#endif
