declare interface Params {}

// Sharpen
declare interface SharpenParams extends Params {
  radius: number
  amount: number
  threshold: number
}

// Levels
declare enum LevelsMode {
  LEVELS_MODE_MANUAL = 'LEVELS_MODE_MANUAL',
  LEVELS_MODE_AUTOMATIC = 'LEVELS_MODE_AUTOMATIC'
}

declare interface LevelsParams extends Params {
  mode: LevelsMode
  percentiles: [number, number, number]
  levels: [number, number, number]
}

// Shadhi
declare enum GaussianOrder {
  GAUSSIAN_ZERO = 'DT_IOP_GAUSSIAN_ZERO',
  GAUSSIAN_ONE = 'DT_IOP_GAUSSIAN_ONE',
  GAUSSIAN_TOW = 'DT_IOP_GAUSSIAN_TWO'
}

declare enum ShadHiAlgo {
  SHADHI_ALGO_GAUSSIAN = 'SHADHI_ALGO_GAUSSIAN',
  SHADHI_ALGO_BILATERAL = 'SHADHI_ALGO_BILATERAL'
}

declare interface ShadhiParams extends Params {
  order: GaussianOrder
  radius: number
  shadows: number
  whitepoint: number
  highlights: number
  reserved2: number
  compress: number
  shadows_ccorrect: number
  highlights_ccorrect: number
  flags: number
  low_approximation: number
  shadhi_algo: ShadHiAlgo
}

// Exposure
declare enum ExposureMode {
  EXPOSURE_MODE_MANUAL = 'EXPOSURE_MODE_MANUAL',
  EXPOSURE_MODE_DEFLICKER = 'EXPOSURE_MODE_DEFLICKER'
}

declare interface ExposureParams extends Params {
  mode: ExposureMode
  black: number
  exposure: number
  deflickerPercentile: number
  deflickerTargetLevel: number
}

// Basecurve
declare enum BasecurveType {
  CUBIC_SPLINE = 0,
  CATMULL_ROM = 1,
  MONOTONE_HERMITE = 2
}

declare interface BasecurveNode {
  x: number
  y: number
}

declare interface BasecurveParams extends Params {
  /** curve (the other two are reserved) */
  basecurve: [
    Array<BasecurveNode>,
    Array<BasecurveNode>,
    Array<BasecurveNode>
  ]
  basecurve_nodes: [number, number, number]
  basecurve_type: [BasecurveType, BasecurveType, BasecurveType]

  /** number of exposure fusion steps */
  exposure_fusion: number

  /** number of stops between fusion images */
  exposure_stops: number

  /** whether to do exposure-fusion with over or under-exposure */
  exposure_bias: number
}

// Blend
declare interface BlendParams extends Params {
  maskMode: number
  blendMode: number
  maskId: number
  opacity: number
  maskCombine: number
  blendif: number
  radius: number
  reserved: [number, number, number, number]
  blendifParameters: Array<number>
}

// Clipping
declare interface ClippingParams extends Params {
  angle: number
  cx: number
  cy: number
  cw: number
  ch: number
  kH: number
  kV: number
  kxa: number
  kya: number
  kxb: number
  kyb: number
  kxc: number
  kyc: number
  kxd: number
  kyd: number
  kType: number
  kSym: number
  kApply: boolean
  cropAuto: boolean
  ratioN: number
  ratioD: number
}

// Defringe
declare enum DefringeMode {
  MODE_GLOBAL_AVERAGE = 'MODE_GLOBAL_AVERAGE',
  MODE_LOCAL_AVERAGE = 'MODE_LOCAL_AVERAGE',
  MODE_STATIC = 'MODE_STATIC'
}

declare interface DefringeParams extends Params {
  radius: number
  thresh: number
  op_mode: DefringeMode
}

// Orientation
declare enum ImageOrientation {
  ORIENTATION_NULL = 'ORIENTATION_NULL',
  ORIENTATION_NONE = 'ORIENTATION_NONE',
  ORIENTATION_FLIP_Y = 'ORIENTATION_FLIP_Y',
  ORIENTATION_FLIP_X = 'ORIENTATION_FLIP_X',
  ORIENTATION_SWAP_XY = 'ORIENTATION_SWAP_XY',
  ORIENTATION_ROTATE_180_DEG = 'ORIENTATION_ROTATE_180_DEG',
  ORIENTATION_ROTATE_CCW_90_DEG = 'ORIENTATION_ROTATE_CCW_90_DEG',
  ORIENTATION_ROTATE_CW_90_DEG = 'ORIENTATION_ROTATE_CW_90_DEG',
  ORIENTATION_421 = 'ORIENTATION_421'
}

declare interface FlipParams extends Params {
  orientation: ImageOrientation
}

// Masks
declare enum MaskType {
  NONE = 0,
  CIRCLE = 1,
  PATH = 2,
  GROUP = 4,
  CLONE = 8,
  GRADIENT = 16,
  ELLIPSE = 32,
  BRUSH = 64,
  NON_CLONE = 128
}

declare enum EllipseFlags {
  EQUIDISTANT = 0,
  PROPORTIONAL = 1
}

declare interface MaskPoint {}

declare interface MaskCirclePoint extends MaskPoint {
  center: [number, number]
  radius: number,
  border: number
}

declare interface MaskEllipsePoint extends MaskPoint {
  center: [number, number]
  radius: [number, number]
  rotation: number
  border: number
  flags: EllipseFlags
}

declare interface MaskGradientPoint extends MaskPoint {
  anchor: [number, number]
  rotation: number
  compression: number
  steepness: number
}

// Errors
declare class CustomError extends Error {}

declare class UnknownOperationError extends CustomError {
  operation: string
}

// declare type operation = 'sharpen' | 'levels' | 'shadhi' | 'exposure' |
//   'blend' | 'clipping' | 'defringe' | 'flip' | 'basecurve'

// Export
declare var darkroomXmpTools: {
  // Sharpen
  decodeSharpenParams (encoded: string): SharpenParams
  encodeSharpenParams (params: SharpenParams): string

  // Levels
  LevelsMode: typeof LevelsMode
  decodeLevelsParams (encoded: string): LevelsParams
  encodeLevelsParams (params: LevelsParams): string

  // Shadhi
  GaussianOrder: typeof GaussianOrder
  ShadHiAlgo: typeof ShadHiAlgo
  decodeShadhiParams (encoded: string): ShadhiParams
  encodeShadhiParams (params: ShadhiParams): string

  // Exposure
  ExposureMode: typeof ExposureMode
  decodeExposureParams (encoded: string): ExposureParams
  encodeExposureParams (params: ExposureParams): string

  // Blend
  decodeBlendParams (encoded: string): BlendParams
  encodeBlendParams (params: BlendParams): string

  // Clipping
  decodeClippingParams (encoded: string): ClippingParams
  encodeClippingParams (params: ClippingParams): string

  // Defringe
  DefringeMode: typeof DefringeMode
  decodeDefringeParams (encoded: string): DefringeParams
  encodeDefringeParams (params: DefringeParams): string

  // Flip
  ImageOrientation: typeof ImageOrientation
  decodeFlipParams (encoded: string): FlipParams
  encodeFlipParams (params: FlipParams): string

  // Basecurve
  BasecurveType: typeof BasecurveType
  decodeBasecurveParams (encoded: string): BasecurveParams
  encodeBasecurveParams (params: BasecurveParams): string

  // Masks
  MaskType: typeof MaskType
  decodeMaskPoints<MaskPoint> (maskType: string, numberPoints: number, encodedPoints: string): Array<MaskPoint>
  encodeMaskPoints<MaskPoint> (maskType: string, points: Array<MaskPoint>): string

  // - circle mask
  decodeCircleMask (encodedMask: string): MaskCirclePoint
  encodeCircleMask (mask: MaskCirclePoint): string

  // - ellipse mask
  EllipseFlags: typeof EllipseFlags
  decodeEllipseMask (encodedMask: string): MaskEllipsePoint
  encodeEllipseMask (mask: MaskEllipsePoint): string

  // - gradient mask
  decodeGradientMask (encodedMask: string): MaskGradientPoint
  encodeGradientMask (mask: MaskGradientPoint): string

  // Helpers
  decodeParams (operation: 'sharpen', encodedParams: string): SharpenParams
  decodeParams (operation: 'levels', encodedParams: string): LevelsParams
  decodeParams (operation: 'shadhi', encodedParams: string): ShadhiParams
  decodeParams (operation: 'exposure', encodedParams: string): ExposureParams
  decodeParams (operation: 'blend', encodedParams: string): BlendParams
  decodeParams (operation: 'clipping', encodedParams: string): ClippingParams
  decodeParams (operation: 'defringe', encodedParams: string): DefringeParams
  decodeParams (operation: 'flip', encodedParams: string): FlipParams
  decodeParams (operation: 'basecurve', encodedParams: string): BasecurveParams
  decodeParams<T> (operation: string, encodedParams: string): T

  encodeParams (operation: string, params: Params): string

  // Errors
  UnknownOperationError: typeof UnknownOperationError
}

export = darkroomXmpTools
