'use strict'

const assert = require('assert')
const sidecar = require('..')

assert.equal(
  sidecar.DefringeMode.MODE_GLOBAL_AVERAGE, 'MODE_GLOBAL_AVERAGE')
assert.equal(
  sidecar.DefringeMode.MODE_LOCAL_AVERAGE, 'MODE_LOCAL_AVERAGE')
assert.equal(
  sidecar.DefringeMode.MODE_STATIC, 'MODE_STATIC')

// defringeParams: {
//   "radius":4,
//   "thresh":20,
//   "op_mode":"MODE_GLOBAL_AVERAGE"
// }
const DEFRINGE_PARAMS_BIN_STR = '000080400000a04100000000'

let paramsObj = sidecar.decodeDefringeParams(DEFRINGE_PARAMS_BIN_STR)
// console.log('defringeParams:', JSON.stringify(paramsObj))

let encodedParamsStr = sidecar.encodeDefringeParams(paramsObj)

assert.strictEqual(encodedParamsStr, DEFRINGE_PARAMS_BIN_STR)
console.log('defringe test - OK')
