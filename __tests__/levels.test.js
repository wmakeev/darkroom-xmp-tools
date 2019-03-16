'use strict'

const assert = require('assert')
const sidecar = require('..')
const testOperation = require('./testOperation')

const OPERATION = 'levels'

assert.equal(
  sidecar.LevelsMode.LEVELS_MODE_AUTOMATIC, 'LEVELS_MODE_AUTOMATIC')
assert.equal(
  sidecar.LevelsMode.LEVELS_MODE_MANUAL, 'LEVELS_MODE_MANUAL')

// levelsParams: {
//   "mode":"LEVELS_MODE_MANUAL",
//   "percentiles":[0,50,100],
//   "levels":[0.01224489789456129,0.48367348313331604,0.9551020264625549]
// }
const LEVELS_PARAMS_BIN_STR = '0000000000000000000048420000c842d39e483c0da4f73e9181743f'

testOperation(OPERATION, LEVELS_PARAMS_BIN_STR)
