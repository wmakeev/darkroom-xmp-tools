'use strict'

const testOperation = require('./testOperation')

const OPERATION = 'sharpen'

// sharpenParams: {
//   "radius": 2,
//   "amount": 0.5,
//   "threshold": 0.5
// }
const SHARPEN_PARAMS_BIN_STR = '000000400000003f0000003f'

testOperation(OPERATION, SHARPEN_PARAMS_BIN_STR)
