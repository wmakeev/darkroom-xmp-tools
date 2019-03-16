'use strict'

const assert = require('assert')
const sidecar = require('..')
const testOperation = require('./testOperation')

const OPERATION = 'defringe'

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

testOperation(OPERATION, DEFRINGE_PARAMS_BIN_STR)
