'use strict'

const assert = require('assert')
const sidecar = require('..')

// sharpenParams: {
//   "radius": 2,
//   "amount": 0.5,
//   "threshold": 0.5
// }
const SHARPEN_PARAMS_BIN_STR = '000000400000003f0000003f'

let paramsObj = sidecar.decodeSharpenParams(SHARPEN_PARAMS_BIN_STR)
// console.log('sharpenParams:', JSON.stringify(paramsObj))

let encodedParamsStr = sidecar.encodeSharpenParams(paramsObj)
// console.log('encoded sharpenParams:', encodedParamsStr)

assert.strictEqual(encodedParamsStr, SHARPEN_PARAMS_BIN_STR)
console.log('sharpen test - OK')
