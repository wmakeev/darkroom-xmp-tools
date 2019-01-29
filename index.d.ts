/**
 * Sharpen
 */
declare interface SharpenParams {
  radius: number
  amount: number
  threshold: number
}

/**
 * Levels
 */
declare enum LevelsMode {
  LEVELS_MODE_MANUAL = 'LEVELS_MODE_MANUAL',
  LEVELS_MODE_AUTOMATIC = 'LEVELS_MODE_AUTOMATIC'
}

declare interface LevelsParams {
  mode: LevelsMode
  percentiles: [number, number, number]
  levels: [number, number, number]
}

/**
 * Shadhi
 */
declare enum GaussianOrder {
  GAUSSIAN_ZERO = 'DT_IOP_GAUSSIAN_ZERO',
  GAUSSIAN_ONE = 'DT_IOP_GAUSSIAN_ONE',
  GAUSSIAN_TOW = 'DT_IOP_GAUSSIAN_TWO'
}

declare enum ShadHiAlgo {
  SHADHI_ALGO_GAUSSIAN = 'SHADHI_ALGO_GAUSSIAN',
  SHADHI_ALGO_BILATERAL = 'SHADHI_ALGO_BILATERAL'
}

declare interface ShadhiParams {
  order: GaussianOrder
  radius: number
  shadows: number
  shadows: number
  highlights: number
  reserved2: number
  compress: number
  shadows_ccorrect: number
  highlights_ccorrect: number
  flags: number
  low_approximation: number
  shadhi_algo: ShadHiAlgo
}

/**
 * Exposure
 */
declare enum ExposureMode {
  EXPOSURE_MODE_MANUAL = 'EXPOSURE_MODE_MANUAL',
  EXPOSURE_MODE_DEFLICKER = 'EXPOSURE_MODE_DEFLICKER'
}

declare interface ExposureParams {
  mode: ExposureMode
  black: number
  exposure: number
  deflickerPercentile: number
  deflickerTargetLevel: number
}

/**
 * Blend
 */
declare interface BlendParams {
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

/**
 * Clipping
 */
declare interface ClippingParams {
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

declare var darkroomXmpTools: {
  // Sharpen
  decodeSharpenParams (encoded: string): SharpenParams
  encodeSharpenParams (params: SharpenParams): string

  // Levels
  LevelsMode: typeof LevelsMode
  decodeSharpenParams (encoded: string): LevelsParams
  encodeSharpenParams (params: LevelsParams): string

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
}

export = darkroomXmpTools
