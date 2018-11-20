
/**
 * Expose params
 */
declare interface ExposeParams {
  mode: 'EXPOSURE_MODE_MANUAL' | 'EXPOSURE_MODE_DEFLICKER'
  black: number
  exposure: number
  deflickerPercentile: number
  deflickerTargetLevel: number
}

/**
 * Blend params
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
 * Clipping params
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
  MaskType: MaskType

  EllipseFlags: EllipseFlags

  // Expose
  decodeExposeParams (encoded: string): ExposeParams
  encodeExposeParams (params: ExposeParams): string

  // Blend
  decodeBlendParams (encoded: string): BlendParams
  encodeBlendParams (params: BlendParams): string

  // Clipping
  decodeClippingParams (encoded: string): ClippingParams
  encodeClippingParams (params: ClippingParams): string

  // Masks
  decodeMaskPoints<MaskPoint> (maskType: string, numberPoints: number, encodedPoints: string): Array<MaskPoint>
  encodeMaskPoints<MaskPoint> (maskType: string, points: Array<MaskPoint>): string

  // - circle mask
  decodeCircleMask (encodedMask: string): MaskCirclePoint
  encodeCircleMask (mask: MaskCirclePoint): string

  // - ellipse mask
  decodeEllipseMask (encodedMask: string): MaskEllipsePoint
  encodeEllipseMask (mask: MaskEllipsePoint): string

  // - gradient mask
  decodeGradientMask (encodedMask: string): MaskGradientPoint
  encodeGradientMask (mask: MaskGradientPoint): string
}

export = darkroomXmpTools
