darkroom-xmp-tools
==================

[![npm](https://img.shields.io/npm/v/@wmakeev/darkroom-xmp-tools.svg?maxAge=1800&style=flat-square)](https://www.npmjs.com/package/@wmakeev/darkroom-xmp-tools)

> Tools helps automize image processing with [darkroom-cli](https://www.darktable.org/usermanual/en/overview_chapter.html#darktable_cli_commandline_parameters)

## Install

> Tested on MacOS 10.14, NodeJs v9.2.0

`$ npm install @wmakeev/darkroom-xmp-tools`

## Usage

```js
const assert = require('assert')
const { decodeExposeParams, encodeExposeParams } = require('@wmakeev/darkroom-xmp-tools')

const EXPOSE_PARAMS_BIN_STR = '0000000040a0093bd8ce374000004842000080c0'

let paramsObj = decodeExposeParams(EXPOSE_PARAMS_BIN_STR)

// "exposeParams": {
//   "mode": "EXPOSURE_MODE_MANUAL",
//   "black": 0.0021000057458877563,
//   "exposure": 2.871999740600586,
//   "deflickerPercentile": 50,
//   "deflickerTargetLevel": -4
// }
console.log('exposeParams:', JSON.stringify(paramsObj))

let encodedParamsStr = encodeExposeParams(paramsObj)

assert.strictEqual(encodedParamsStr, EXPOSE_PARAMS_BIN_STR)
```

## API

### Expose

- `decodeExposeParams (encoded: string): ExposeParams`

- `encodeExposeParams (params: ExposeParams): string`

### Blend

- `decodeBlendParams (encoded: string): BlendParams`

- `encodeBlendParams (params: BlendParams): string`

### Clipping

- `decodeClippingParams (encoded: string): ClippingParams`

- `encodeClippingParams (params: ClippingParams): string`



