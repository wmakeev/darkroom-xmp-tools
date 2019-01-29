'use strict'

const assert = require('assert')
const sidecar = require('..')

assert.equal(
  sidecar.ExposeMode.EXPOSURE_MODE_DEFLICKER, 'EXPOSURE_MODE_DEFLICKER')

assert.equal(
  sidecar.ExposeMode.EXPOSURE_MODE_MANUAL, 'EXPOSURE_MODE_MANUAL')

// exposeParams: {
//   "mode": "EXPOSURE_MODE_MANUAL",
//   "black": 0.0021000057458877563,
//   "exposure": 2.871999740600586,
//   "deflickerPercentile": 50,
//   "deflickerTargetLevel": -4
// }
const EXPOSE_PARAMS_BIN_STR = '0000000040a0093bd8ce374000004842000080c0'

let paramsObj = sidecar.decodeExposeParams(EXPOSE_PARAMS_BIN_STR)
// console.log('exposeParams:', JSON.stringify(paramsObj))

let encodedParamsStr = sidecar.encodeExposeParams(paramsObj)
// console.log('encoded exposeParams:', encodedParamsStr)

assert.strictEqual(encodedParamsStr, EXPOSE_PARAMS_BIN_STR)
console.log('expose test - OK')
