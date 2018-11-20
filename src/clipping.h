#include <napi.h>

#ifndef CLIPPING_H
#define CLIPPING_H

struct dt_iop_clipping_params_t
{
  float angle, cx, cy, cw, ch, k_h, k_v;
  float kxa, kya, kxb, kyb, kxc, kyc, kxd, kyd;
  int k_type, k_sym;
  int k_apply, crop_auto;
  int ratio_n, ratio_d;
};

Napi::Value decode_clipping_params(const Napi::CallbackInfo &info);

Napi::Value encode_clipping_params(const Napi::CallbackInfo &info);

#endif
