#include <napi.h>

#ifndef FLIP_H
#define FLIP_H

enum dt_image_orientation_t
{
  ORIENTATION_NULL = -1,        //-1, or autodetect
  ORIENTATION_NONE = 0,         // 0
  ORIENTATION_FLIP_Y = 1 << 0,  // 1
  ORIENTATION_FLIP_X = 1 << 1,  // 2
  ORIENTATION_SWAP_XY = 1 << 2, // 4

  /* ClockWise rotation == "-"; CounterClockWise rotation == "+" */
  ORIENTATION_FLIP_HORIZONTALLY = ORIENTATION_FLIP_Y,                                       // 1
  ORIENTATION_FLIP_VERTICALLY = ORIENTATION_FLIP_X,                                         // 2
  ORIENTATION_ROTATE_180_DEG = ORIENTATION_FLIP_Y | ORIENTATION_FLIP_X,                     // 3
  ORIENTATION_400 /* ??? */ = ORIENTATION_SWAP_XY,                                          // 4
  ORIENTATION_ROTATE_CCW_90_DEG = ORIENTATION_FLIP_Y | ORIENTATION_SWAP_XY,                 // 5
  ORIENTATION_ROTATE_CW_90_DEG = ORIENTATION_FLIP_X | ORIENTATION_SWAP_XY,                  // 6
  ORIENTATION_421 /* ??? */ = ORIENTATION_FLIP_Y | ORIENTATION_FLIP_X | ORIENTATION_SWAP_XY // 7
};

struct dt_iop_flip_params_t
{
  dt_image_orientation_t orientation;
};

Napi::Value decode_flip_params(const Napi::CallbackInfo &info);

Napi::Value encode_flip_params(const Napi::CallbackInfo &info);

#endif
