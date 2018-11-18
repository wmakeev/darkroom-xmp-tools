'use strict'

const assert = require('assert')
const sidecar = require('..')

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

let paramsObj = sidecar.decodeBlendParams(BLEND_PARAMS_GZIP_STR)
// console.log('blendParams:', JSON.stringify(paramsObj))

let encodedParamsStr = sidecar.encodeBlendParams(paramsObj)
// console.log('encoded blendParams:', encodedParamsStr)

assert.strictEqual(encodedParamsStr, BLEND_PARAMS_GZIP_STR)
console.log('blend test - OK')
