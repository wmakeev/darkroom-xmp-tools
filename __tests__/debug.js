// const assert = require('assert')
const { decodeCircleMask, encodeCircleMask } = require('../build/Debug/darkroom-xmp-tools.node')

let paramsObj, encodedStr

const CIRCLE_MASK_BLOB = '13b50a3f1857f73eb6b2073e07288f3d'

paramsObj = decodeCircleMask(CIRCLE_MASK_BLOB)
console.log('gradientMask:', JSON.stringify(paramsObj))

encodedStr = encodeCircleMask(paramsObj)
console.log('encoded exposureParams:', encodedStr)
