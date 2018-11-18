'use strict'

const assert = require('assert')
const sidecar = require('..')

// clippingParams: {
//   "angle": 0,
//   "cx": 0.129995197057724,
//   "cy": 0.47907647490501404,
//   "cw": 0.8960038423538208,
//   "ch": 0.9191919565200806,
//   "kH": 0, "kV": 0,
//   "kxa": 0.20000000298023224,
//   "kya": 0.20000000298023224,
//   "kxb": 0.800000011920929,
//   "kyb": 0.20000000298023224,
//   "kxc": 0.800000011920929,
//   "kyc": 0.800000011920929,
//   "kxd": 0.20000000298023224,
//   "kyd": 0.800000011920929,
//   "kType": 0,
//   "kSym": 0,
//   "kApply": false,
//   "cropAuto": false,
//   "ratioN": 0,
//   "ratioD": 0
// }

// const CLIPPING_PARAMS_BIN_STR = '00000000761d053e8349f53e8260653f2a506b3f0000000000000000cdcc4c3ecdcc4c3ecdcc4c3fcdcc4c3ecdcc4c3fcdcc4c3fcdcc4c3ecdcc4c3f000000000000000000000000000000000000000000000000'
const CLIPPING_PARAMS_BIN_STR = '000000001c1ccc3d1c644d3e0000803fc482663f0000000000000000cdcc4c3ecdcc4c3ecdcc4c3fcdcc4c3ecdcc4c3fcdcc4c3fcdcc4c3ecdcc4c3f000000000000000000000000010000000000000000000000'

let paramsObj = sidecar.decodeClippingParams(CLIPPING_PARAMS_BIN_STR)
// console.log('clippingParams:', JSON.stringify(paramsObj))

let encodedParamsStr = sidecar.encodeClippingParams(paramsObj)
// console.log('encoded clippingParams:', encodedParamsStr)

assert.strictEqual(encodedParamsStr, CLIPPING_PARAMS_BIN_STR)
console.log('clipping test - OK')
