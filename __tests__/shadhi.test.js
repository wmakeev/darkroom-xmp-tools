'use strict'

const assert = require('assert')
const sidecar = require('..')

assert.equal(
  sidecar.GaussianOrder.GAUSSIAN_ZERO, 'DT_IOP_GAUSSIAN_ZERO')
assert.equal(
  sidecar.GaussianOrder.GAUSSIAN_ONE, 'DT_IOP_GAUSSIAN_ONE')
assert.equal(
  sidecar.GaussianOrder.GAUSSIAN_TOW, 'DT_IOP_GAUSSIAN_TWO')

assert.equal(
  sidecar.ShadHiAlgo.SHADHI_ALGO_GAUSSIAN, 'SHADHI_ALGO_GAUSSIAN')
assert.equal(
  sidecar.ShadHiAlgo.SHADHI_ALGO_BILATERAL, 'SHADHI_ALGO_BILATERAL')

// shadhiParams: {
//   "order": "DT_IOP_GAUSSIAN_ZERO",
//   "shadhi_algo": "SHADHI_ALGO_GAUSSIAN",
//   "radius": 100,
//   "shadows": 13.790000915527344,
//   "whitepoint": 0,
//   "highlights": 0,
//   "reserved2": 0,
//   "compress": 50,
//   "shadows_ccorrect": 100,
//   "flags": 127,
//   "low_approximation": 9.999999974752427e-7
// }
const SHADHI_PARAMS_BIN_STR = '000000000000c842d8a35c41000000000000000000000000000048420000c842000048427f000000bd37863500000000'

let paramsObj = sidecar.decodeShadhiParams(SHADHI_PARAMS_BIN_STR)
// console.log('shadhiParams:', JSON.stringify(paramsObj))

let encodedParamsStr = sidecar.encodeShadhiParams(paramsObj)

assert.strictEqual(encodedParamsStr, SHADHI_PARAMS_BIN_STR)
console.log('shadhi test - OK')