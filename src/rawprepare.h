#include <napi.h>

#ifndef RAWPREPARE_H
#define RAWPREPARE_H

typedef struct dt_iop_rawprepare_params_t
{
  int32_t x; // $MIN: 0 $MAX: UINT16_MAX $DESCRIPTION: "crop left"
  int32_t y; // $MIN: 0 $MAX: UINT16_MAX $DESCRIPTION: "crop top"
  int32_t width; // $MIN: 0 $MAX: UINT16_MAX $DESCRIPTION: "crop right"
  int32_t height; // $MIN: 0 $MAX: UINT16_MAX $DESCRIPTION: "crop bottom"
  uint16_t raw_black_level_separate[4]; // $MIN: 0 $MAX: UINT16_MAX $DESCRIPTION: "black level"
  uint16_t raw_white_point; // $MIN: 0 $MAX: UINT16_MAX $DESCRIPTION: "white point"
} dt_iop_rawprepare_params_t;

Napi::Value decode_rawprepare_params(const Napi::CallbackInfo &info);

Napi::Value encode_rawprepare_params(const Napi::CallbackInfo &info);

#endif
