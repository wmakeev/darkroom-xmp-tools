'use strict'

const testOperation = require('./testOperation')

const OPERATION = 'crop'

// cropParams: {
// 	"cx": 0.2619973421096802,
// 	"cy": 0.02298051305115223,
// 	"cw": 0.7741972804069519,
// 	"ch": 0.8658803105354309,
// 	"ratioN": 0,
// 	"ratioD": 0
// }

const CLIPPING_PARAMS_BIN_STR = '8424863ea141bc3ccb31463f55aa5d3f0000000000000000'

testOperation(OPERATION, CLIPPING_PARAMS_BIN_STR)
