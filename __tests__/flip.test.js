'use strict'

const assert = require('assert')
const sidecar = require('..')
const testOperation = require('./testOperation')

const OPERATION = 'flip'

assert.strictEqual(
  sidecar.ImageOrientation.ORIENTATION_NULL,
  'ORIENTATION_NULL')

assert.strictEqual(
  sidecar.ImageOrientation.ORIENTATION_NONE,
  'ORIENTATION_NONE')

assert.strictEqual(
  sidecar.ImageOrientation.ORIENTATION_FLIP_Y,
  'ORIENTATION_FLIP_Y')

assert.strictEqual(
  sidecar.ImageOrientation.ORIENTATION_FLIP_X,
  'ORIENTATION_FLIP_X')

assert.strictEqual(
  sidecar.ImageOrientation.ORIENTATION_SWAP_XY,
  'ORIENTATION_SWAP_XY')

assert.strictEqual(
  sidecar.ImageOrientation.ORIENTATION_ROTATE_180_DEG,
  'ORIENTATION_ROTATE_180_DEG')

assert.strictEqual(
  sidecar.ImageOrientation.ORIENTATION_ROTATE_CCW_90_DEG,
  'ORIENTATION_ROTATE_CCW_90_DEG')

assert.strictEqual(
  sidecar.ImageOrientation.ORIENTATION_ROTATE_CW_90_DEG,
  'ORIENTATION_ROTATE_CW_90_DEG')

assert.strictEqual(
  sidecar.ImageOrientation.ORIENTATION_421,
  'ORIENTATION_421')

// flipParams: { "orientation": "ORIENTATION_ROTATE_CCW_90_DEG" }
const FLIP_PARAMS_BIN_STR = '05000000'

testOperation(OPERATION, FLIP_PARAMS_BIN_STR)
