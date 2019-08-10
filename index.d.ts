export interface Params {}

// Sharpen
export interface SharpenParams extends Params {
  radius: number
  amount: number
  threshold: number
}

// Levels
export enum LevelsMode {
  LEVELS_MODE_MANUAL = 'LEVELS_MODE_MANUAL',
  LEVELS_MODE_AUTOMATIC = 'LEVELS_MODE_AUTOMATIC'
}

export interface LevelsParams extends Params {
  mode: LevelsMode
  percentiles: [number, number, number]
  levels: [number, number, number]
}

// Shadhi
export enum GaussianOrder {
  GAUSSIAN_ZERO = 'DT_IOP_GAUSSIAN_ZERO',
  GAUSSIAN_ONE = 'DT_IOP_GAUSSIAN_ONE',
  GAUSSIAN_TOW = 'DT_IOP_GAUSSIAN_TWO'
}

export enum ShadHiAlgo {
  SHADHI_ALGO_GAUSSIAN = 'SHADHI_ALGO_GAUSSIAN',
  SHADHI_ALGO_BILATERAL = 'SHADHI_ALGO_BILATERAL'
}

export interface ShadhiParams extends Params {
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
export enum ExposureMode {
  EXPOSURE_MODE_MANUAL = 'EXPOSURE_MODE_MANUAL',
  EXPOSURE_MODE_DEFLICKER = 'EXPOSURE_MODE_DEFLICKER'
}

export interface ExposureParams extends Params {
  mode: ExposureMode
  black: number
  exposure: number
  deflickerPercentile: number
  deflickerTargetLevel: number
}

// Basecurve
export enum BasecurveType {
  CUBIC_SPLINE = 0,
  CATMULL_ROM = 1,
  MONOTONE_HERMITE = 2
}

export interface BasecurveNode {
  x: number
  y: number
}

export interface BasecurveParams extends Params {
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
export interface BlendParams extends Params {
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
export interface ClippingParams extends Params {
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
export enum DefringeMode {
  MODE_GLOBAL_AVERAGE = 'MODE_GLOBAL_AVERAGE',
  MODE_LOCAL_AVERAGE = 'MODE_LOCAL_AVERAGE',
  MODE_STATIC = 'MODE_STATIC'
}

export interface DefringeParams extends Params {
  radius: number
  thresh: number
  op_mode: DefringeMode
}

// Orientation
export enum ImageOrientation {
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

export interface FlipParams extends Params {
  orientation: ImageOrientation
}

// Masks
export enum MaskType {
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

export enum EllipseFlags {
  EQUIDISTANT = 0,
  PROPORTIONAL = 1
}

export interface MaskPoint {}

export interface MaskCirclePoint extends MaskPoint {
  center: [number, number]
  radius: number,
  border: number
}

export interface MaskEllipsePoint extends MaskPoint {
  center: [number, number]
  radius: [number, number]
  rotation: number
  border: number
  flags: EllipseFlags
}

export interface MaskGradientPoint extends MaskPoint {
  anchor: [number, number]
  rotation: number
  compression: number
  steepness: number
}

// Errors
export class CustomError extends Error {}

export class UnknownOperationError extends CustomError {
  operation: string
}

// Sharpen
export function decodeSharpenParams(encoded: string): SharpenParams
export function encodeSharpenParams(params: SharpenParams): string

// Levels
export function decodeLevelsParams(encoded: string): LevelsParams
export function encodeLevelsParams(params: LevelsParams): string

// Shadhi
export function decodeShadhiParams(encoded: string): ShadhiParams
export function encodeShadhiParams(params: ShadhiParams): string

// Exposure
export function decodeExposureParams(encoded: string): ExposureParams
export function encodeExposureParams(params: ExposureParams): string

// Blend
export function decodeBlendParams(encoded: string): BlendParams
export function encodeBlendParams(params: BlendParams): string

// Clipping
export function decodeClippingParams(encoded: string): ClippingParams
export function encodeClippingParams(params: ClippingParams): string

// Defringe
export function decodeDefringeParams(encoded: string): DefringeParams
export function encodeDefringeParams(params: DefringeParams): string

// Flip
export function decodeFlipParams(encoded: string): FlipParams
export function encodeFlipParams(params: FlipParams): string

// Basecurve
export function decodeBasecurveParams(encoded: string): BasecurveParams
export function encodeBasecurveParams(params: BasecurveParams): string

// Masks
export function decodeMaskPoints<MaskPoint>(maskType: string, numberPoints: number, encodedPoints: string): Array < MaskPoint >
export function encodeMaskPoints<MaskPoint>(maskType: string, points: Array<MaskPoint>): string

// - circle mask
export function decodeCircleMask(encodedMask: string): MaskCirclePoint
export function encodeCircleMask(mask: MaskCirclePoint): string

// - ellipse mask
export function decodeEllipseMask(encodedMask: string): MaskEllipsePoint
export function encodeEllipseMask(mask: MaskEllipsePoint): string

// - gradient mask
export function decodeGradientMask(encodedMask: string): MaskGradientPoint
export function encodeGradientMask(mask: MaskGradientPoint): string

// Helpers
export function decodeParams(operation: 'sharpen', encodedParams: string): SharpenParams
export function decodeParams(operation: 'levels', encodedParams: string): LevelsParams
export function decodeParams(operation: 'shadhi', encodedParams: string): ShadhiParams
export function decodeParams(operation: 'exposure', encodedParams: string): ExposureParams
export function decodeParams(operation: 'blend', encodedParams: string): BlendParams
export function decodeParams(operation: 'clipping', encodedParams: string): ClippingParams
export function decodeParams(operation: 'defringe', encodedParams: string): DefringeParams
export function decodeParams(operation: 'flip', encodedParams: string): FlipParams
export function decodeParams(operation: 'basecurve', encodedParams: string): BasecurveParams
export function decodeParams<T>(operation: string, encodedParams: string): T

export function encodeParams<T extends Params>(operation: string, params: T): string
