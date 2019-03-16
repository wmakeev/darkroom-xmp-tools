'use strict'

const { UnknownOperationError } = require('./errors')

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

const BasecurveType = {
  CUBIC_SPLINE: 0,
  CATMULL_ROM: 1,
  MONOTONE_HERMITE: 2
}

const ShadHiAlgo = {
  SHADHI_ALGO_GAUSSIAN: 'SHADHI_ALGO_GAUSSIAN',
  SHADHI_ALGO_BILATERAL: 'SHADHI_ALGO_BILATERAL'
}

const DefringeMode = {
  MODE_GLOBAL_AVERAGE: 'MODE_GLOBAL_AVERAGE',
  MODE_LOCAL_AVERAGE: 'MODE_LOCAL_AVERAGE',
  MODE_STATIC: 'MODE_STATIC'
}

const ImageOrientation = {
  ORIENTATION_NULL: 'ORIENTATION_NULL',
  ORIENTATION_NONE: 'ORIENTATION_NONE',
  ORIENTATION_FLIP_Y: 'ORIENTATION_FLIP_Y',
  ORIENTATION_FLIP_X: 'ORIENTATION_FLIP_X',
  ORIENTATION_SWAP_XY: 'ORIENTATION_SWAP_XY',
  ORIENTATION_ROTATE_180_DEG: 'ORIENTATION_ROTATE_180_DEG',
  ORIENTATION_ROTATE_CCW_90_DEG: 'ORIENTATION_ROTATE_CCW_90_DEG',
  ORIENTATION_ROTATE_CW_90_DEG: 'ORIENTATION_ROTATE_CW_90_DEG',
  ORIENTATION_421: 'ORIENTATION_421'
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

function decodeParams (operation, paramsStr) {
  switch (operation) {
    case 'sharpen':
      return tools.decodeSharpenParams(paramsStr)

    case 'levels':
      return tools.decodeLevelsParams(paramsStr)

    case 'shadhi':
      return tools.decodeShadhiParams(paramsStr)

    case 'exposure':
      return tools.decodeExposureParams(paramsStr)

    case 'blend':
      return tools.decodeBlendParams(paramsStr)

    case 'clipping':
      return tools.decodeClippingParams(paramsStr)

    case 'defringe':
      return tools.decodeDefringeParams(paramsStr)

    case 'flip':
      return tools.decodeFlipParams(paramsStr)

    case 'basecurve':
      return tools.decodeBasecurveParams(paramsStr)

    default:
      throw new UnknownOperationError(operation)
  }
}

function encodeParams (operation, params) {
  switch (operation) {
    case 'sharpen':
      return tools.encodeSharpenParams(params)

    case 'levels':
      return tools.encodeLevelsParams(params)

    case 'shadhi':
      return tools.encodeShadhiParams(params)

    case 'exposure':
      return tools.encodeExposureParams(params)

    case 'blend':
      return tools.encodeBlendParams(params)

    case 'clipping':
      return tools.encodeClippingParams(params)

    case 'defringe':
      return tools.encodeDefringeParams(params)

    case 'flip':
      return tools.encodeFlipParams(params)

    case 'basecurve':
      return tools.encodeBasecurveParams(params)

    default:
      throw new UnknownOperationError(operation)
  }
}

Object.assign(module.exports, {
  MaskType,
  EllipseFlags,
  ExposureMode,
  LevelsMode,
  GaussianOrder,
  BasecurveType,
  ShadHiAlgo,
  DefringeMode,
  ImageOrientation,
  decodeCircleMask,
  encodeCircleMask,
  decodeEllipseMask,
  encodeEllipseMask,
  decodeGradientMask,
  encodeGradientMask,
  decodeParams,
  encodeParams,
  UnknownOperationError
})
