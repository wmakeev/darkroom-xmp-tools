#ifndef SHADHI_H
#define SHADHI_H

#include <napi.h>

#define UNBOUND_L 1
#define UNBOUND_A 2
#define UNBOUND_B 4
#define UNBOUND_SHADOWS_L UNBOUND_L
#define UNBOUND_SHADOWS_A UNBOUND_A
#define UNBOUND_SHADOWS_B UNBOUND_B
#define UNBOUND_HIGHLIGHTS_L (UNBOUND_L << 3) /* 8 */
#define UNBOUND_HIGHLIGHTS_A (UNBOUND_A << 3) /* 16 */
#define UNBOUND_HIGHLIGHTS_B (UNBOUND_B << 3) /* 32 */
#define UNBOUND_GAUSSIAN 64
#define UNBOUND_BILATERAL 128 /* not implemented yet */
#define UNBOUND_DEFAULT \
  (UNBOUND_SHADOWS_L | UNBOUND_SHADOWS_A | UNBOUND_SHADOWS_B | UNBOUND_HIGHLIGHTS_L | UNBOUND_HIGHLIGHTS_A | UNBOUND_HIGHLIGHTS_B | UNBOUND_GAUSSIAN)

enum dt_gaussian_order_t
{
  DT_IOP_GAUSSIAN_ZERO = 0,
  DT_IOP_GAUSSIAN_ONE = 1,
  DT_IOP_GAUSSIAN_TWO = 2
};

enum dt_iop_shadhi_algo_t
{
  SHADHI_ALGO_GAUSSIAN,
  SHADHI_ALGO_BILATERAL
};

struct dt_iop_shadhi_params_t
{
  dt_gaussian_order_t order;
  float radius;
  float shadows;
  float whitepoint;
  float highlights;
  float reserved2;
  float compress;
  float shadows_ccorrect;
  float highlights_ccorrect;
  unsigned int flags;
  float low_approximation;
  dt_iop_shadhi_algo_t shadhi_algo;
};

Napi::Value decode_shadhi_params(const Napi::CallbackInfo &info);

Napi::Value encode_shadhi_params(const Napi::CallbackInfo &info);

#endif
