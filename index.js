module.exports = require('bindings')('darkroom-xmp-tools')

const tools = module.exports

const MaskType = {
  NONE: 0,
  CIRCLE: 1,
  PATH: 2,
  GROUP: 4,
  CLONE: 8,
  GRADIENT: 16,
  ELLIPSE: 32,
  BRUSH: 64,
  NON_CLONE: 128
}

const EllipseFlags = {
  EQUIDISTANT: 0,
  PROPORTIONAL: 1
}

const ExposureMode = {
  EXPOSURE_MODE_MANUAL: 'EXPOSURE_MODE_MANUAL',
  EXPOSURE_MODE_DEFLICKER: 'EXPOSURE_MODE_DEFLICKER'
}

const LevelsMode = {
  LEVELS_MODE_MANUAL: 'LEVELS_MODE_MANUAL',
  LEVELS_MODE_AUTOMATIC: 'LEVELS_MODE_AUTOMATIC'
}

const GaussianOrder = {
  GAUSSIAN_ZERO: 'DT_IOP_GAUSSIAN_ZERO',
  GAUSSIAN_ONE: 'DT_IOP_GAUSSIAN_ONE',
  GAUSSIAN_TOW: 'DT_IOP_GAUSSIAN_TWO'
}

const ShadHiAlgo = {
  SHADHI_ALGO_GAUSSIAN: 'SHADHI_ALGO_GAUSSIAN',
  SHADHI_ALGO_BILATERAL: 'SHADHI_ALGO_BILATERAL'
}

// Circle mask
function decodeCircleMask (encodedMask) {
  return tools.decodeMaskPoints(MaskType.CIRCLE, 1, encodedMask)[0]
}

function encodeCircleMask (mask) {
  return tools.encodeMaskPoints(MaskType.CIRCLE, [mask])
}

// Ellipse mask
function decodeEllipseMask (encodedMask) {
  return tools.decodeMaskPoints(MaskType.ELLIPSE, 1, encodedMask)[0]
}

function encodeEllipseMask (mask) {
  return tools.encodeMaskPoints(MaskType.ELLIPSE, [mask])
}

// Gradient mask
function decodeGradientMask (encodedMask) {
  return tools.decodeMaskPoints(MaskType.GRADIENT, 1, encodedMask)[0]
}

function encodeGradientMask (mask) {
  return tools.encodeMaskPoints(MaskType.GRADIENT, [mask])
}

Object.assign(module.exports, {
  MaskType,
  EllipseFlags,
  ExposureMode,
  LevelsMode,
  GaussianOrder,
  ShadHiAlgo,
  decodeCircleMask,
  encodeCircleMask,
  decodeEllipseMask,
  encodeEllipseMask,
  decodeGradientMask,
  encodeGradientMask
})
