'use strict'

const assert = require('assert')
const sidecar = require('..')
const testOperation = require('./testOperation')

const OPERATION = 'exposure'

assert.equal(
  sidecar.ExposureMode.EXPOSURE_MODE_DEFLICKER, 'EXPOSURE_MODE_DEFLICKER')
assert.equal(
  sidecar.ExposureMode.EXPOSURE_MODE_MANUAL, 'EXPOSURE_MODE_MANUAL')

// exposureParams: {
//   "mode": "EXPOSURE_MODE_MANUAL",
//   "black": 0.0021000057458877563,
//   "exposure": 2.871999740600586,
//   "deflickerPercentile": 50,
//   "deflickerTargetLevel": -4
// }
const EXPOSE_PARAMS_BIN_STR = '0000000040a0093bd8ce374000004842000080c0'

testOperation(OPERATION, EXPOSE_PARAMS_BIN_STR)
