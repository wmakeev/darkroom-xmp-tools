#include <napi.h>

#ifndef SHARPEN_H
#define SHARPEN_H

struct dt_iop_sharpen_params_t
{
  float radius, amount, threshold;
};

Napi::Value decode_sharpen_params(const Napi::CallbackInfo &info);

Napi::Value encode_sharpen_params(const Napi::CallbackInfo &info);

#endif
