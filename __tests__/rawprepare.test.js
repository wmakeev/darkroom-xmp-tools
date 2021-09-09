'use strict'

const testOperation = require('./testOperation')

const OPERATION = 'rawprepare'

// rawprepareParams: {
// 	"x": 16,
// 	"y": 12,
// 	"width": 16,
// 	"height": 12,
// 	"rawBlackLevelSeparate": [
// 		3200,
// 		3200,
// 		3200,
// 		3200
// 	],
// 	"rawWhitePoint": 65000
// }

const CLIPPING_PARAMS_BIN_STR = '100000000c000000100000000c000000800c800c800c800ce8fd0000'

testOperation(OPERATION, CLIPPING_PARAMS_BIN_STR)
