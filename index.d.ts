
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

declare var darkroomXmpTools: {
  // Expose
  decodeExposeParams (encoded: string): ExposeParams
  encodeExposeParams (params: ExposeParams): string

  // Blend
  decodeBlendParams (encoded: string): BlendParams
  encodeBlendParams (params: BlendParams): string

  // Clipping
  decodeClippingParams (encoded: string): ClippingParams
  encodeClippingParams (params: ClippingParams): string
}

export = darkroomXmpTools
