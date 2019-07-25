// const assert = require('assert')
const { decodeSharpenParams, encodeSharpenParams } =
  // require('bindings')('darkroom-xmp-tools')
  require('../build/Debug/darkroom-xmp-tools.node')

const SHARPEN_PARAMS_BIN_STR = '000000400000003f0000003f'

const paramsObj = decodeSharpenParams(SHARPEN_PARAMS_BIN_STR)
console.log('decodeParams:', JSON.stringify(paramsObj))

const encodedStr = encodeSharpenParams(paramsObj)
console.log('encodeParams:', encodedStr)
