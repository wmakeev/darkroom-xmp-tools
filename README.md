darkroom-xmp-tools
==================

[![npm](https://img.shields.io/npm/v/@wmakeev/darkroom-xmp-tools.svg?maxAge=1800&style=flat-square)](https://www.npmjs.com/package/@wmakeev/darkroom-xmp-tools)

> Retrieve and update [darktable](https://www.darktable.org/) operations params stored in sidecar xmp files. This helps automize image processing with [darktable-cli](https://www.darktable.org/usermanual/en/overview_chapter.html#darktable_cli_commandline_parameters)

## Install

> Tested on MacOS 10.14, NodeJs v9.2.0

`$ npm install @wmakeev/darkroom-xmp-tools`

## Usage

Take some darktable XMP

```xml
...
<darktable:history>
  <rdf:Seq>
    ...
    <rdf:li
    darktable:operation="exposure"
    darktable:enabled="1"
    darktable:modversion="5"
    darktable:params="0000000040a0093bd8ce374000004842000080c0"
    darktable:multi_name="1"
    darktable:multi_priority="0"
    darktable:blendop_version="7"
    darktable:blendop_params="gz12eJxjYGBgkGAAgRNODESDBnsIHll8ANNSGQM="/>
    ...
  <rdf:Seq>
</darktable:history>
...
```

add some code

```js
const assert = require('assert')
const { decodeExposureParams, encodeExposureParams } = require('@wmakeev/darkroom-xmp-tools')

// from XMP darktable:params
const EXPOSURE_PARAMS_BIN_STR = '0000000040a0093bd8ce374000004842000080c0'

let paramsObj = decodeExposureParams(EXPOSURE_PARAMS_BIN_STR)

console.log('exposureParams:', JSON.stringify(paramsObj))
// "exposureParams": {
//   "mode": "EXPOSURE_MODE_MANUAL",
//   "black": 0.0021000057458877563,
//   "exposure": 2.871999740600586,
//   "deflickerPercentile": 50,
//   "deflickerTargetLevel": -4
// }

// before encode you can modify paramsObj ...

let encodedParamsStr = encodeExposureParams(paramsObj)

// ... and update exposure darktable:params in XMP file with new value

assert.strictEqual(encodedParamsStr, EXPOSURE_PARAMS_BIN_STR)
```

## API

### Sharpen

- `decodeSharpenParams (encoded: string): SharpenParams`

- `encodeSharpenParams (params: SharpenParams): string`

### Levels

- `decodeLevelsParams (encoded: string): LevelsParams`

- `encodeLevelsParams (params: LevelsParams): string`

### Shadhi

- `decodeShadhiParams (encoded: string): ShadhiParams`

- `encodeShadhiParams (params: ShadhiParams): string`

### Exposure

- `decodeExposureParams (encoded: string): ExposureParams`

- `encodeExposureParams (params: ExposureParams): string`

### Blend

- `decodeBlendParams (encoded: string): BlendParams`

- `encodeBlendParams (params: BlendParams): string`

### Clipping

- `decodeClippingParams (encoded: string): ClippingParams`

- `encodeClippingParams (params: ClippingParams): string`

### Defringe

- `decodeDefringeParams (encoded: string): DefringeParams`

- `encodeDefringeParams (params: DefringeParams): string`

### Flip

- `decodeFlipParams (encoded: string): FlipParams`

- `encodeFlipParams (params: FlipParams): string`

### Basecurve

- `decodeBasecurveParams (encoded: string): Basecurve`

- `encodeBasecurveParams (params: Basecurve): string`

### Common

- `decodeParams (operation: 'sharpen', encodedParams: string): SharpenParams`

- `decodeParams (operation: 'levels', encodedParams: string): LevelsParams`

- `decodeParams (operation: 'shadhi', encodedParams: string): ShadhiParams`

- `decodeParams (operation: 'exposure', encodedParams: string): ExposureParams`

- `decodeParams (operation: 'blend', encodedParams: string): BlendParams`

- `decodeParams (operation: 'clipping', encodedParams: string): ClippingParams`

- `decodeParams (operation: 'defringe', encodedParams: string): DefringeParams`

- `decodeParams (operation: 'flip', encodedParams: string): FlipParams`

- `decodeParams (operation: 'basecurve', encodedParams: string): BasecurveParams`

- `encodeParams (operation: string, params: Params): string`

### Masks

- `decodeMaskPoints<MaskPoint> (maskType: string, numberPoints: number, encodedPoints: string): Array<MaskPoint>`

- `encodeMaskPoints<MaskPoint> (maskType: string, points: Array<MaskPoint>): string`

#### circle mask

- `decodeCircleMask (encodedMask: string): MaskCirclePoint`

- `encodeCircleMask (mask: MaskCirclePoint): string`

#### ellipse mask

- `decodeEllipseMask (encodedMask: string): MaskEllipsePoint`

- `encodeEllipseMask (mask: MaskEllipsePoint): string`

#### gradient mask

- `decodeGradientMask (encodedMask: string): MaskGradientPoint`

- `encodeGradientMask (mask: MaskGradientPoint): string`

## TODO

- Test on Linux and Windows
- Improve errors message and arguments validation

## Changes


