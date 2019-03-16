'use strict'

const testOperation = require('./testOperation')

const OPERATION = 'blend'

// blendParams: {
//   "maskMode": 3,
//   "blendMode": 24,
//   "maskId": 1541258146,
//   "opacity": 100,
//   "maskCombine": 1,
//   "blendif": 0,
//   "radius": 92.4000015258789,
//   "reserved": [0, 0, 0, 0],
//   "blendifParameters": [
//     0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
//     0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
//     0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
//     0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1
//   ]
// }

const BLEND_PARAMS_GZIP_STR = 'gz08eJxjZmBgkGAAgRNOjEBy0e670SDe2TM7nBhwggZ7CB5ZfAB1kB4v'

testOperation(OPERATION, BLEND_PARAMS_GZIP_STR)
