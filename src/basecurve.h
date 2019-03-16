#ifndef BASECURVE_H
#define BASECURVE_H

#define MAXNODES 20

// Curve Types
#define CUBIC_SPLINE 0
#define CATMULL_ROM 1
#define MONOTONE_HERMITE 2

#include <napi.h>

struct dt_iop_basecurve_node_t
{
  float x;
  float y;
};

struct dt_iop_basecurve_params_t
{
  // three curves (c, ., .) with max number of nodes
  // the other two are reserved, maybe we'll have cam rgb at some point.
  dt_iop_basecurve_node_t basecurve[3][MAXNODES];
  int basecurve_nodes[3];
  int basecurve_type[3];
  int exposure_fusion;  // number of exposure fusion steps
  float exposure_stops; // number of stops between fusion images
  float exposure_bias;  // whether to do exposure-fusion with over or under-exposure
};

Napi::Value decode_basecurve_params(const Napi::CallbackInfo &info);

Napi::Value encode_basecurve_params(const Napi::CallbackInfo &info);

#endif
