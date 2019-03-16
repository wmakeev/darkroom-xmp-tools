'use strict'

const testOperation = require('./testOperation')

const OPERATION = 'clipping'

// clippingParams: {
//   "angle": 0,
//   "cx": 0.129995197057724,
//   "cy": 0.47907647490501404,
//   "cw": 0.8960038423538208,
//   "ch": 0.9191919565200806,
//   "kH": 0, "kV": 0,
//   "kxa": 0.20000000298023224,
//   "kya": 0.20000000298023224,
//   "kxb": 0.800000011920929,
//   "kyb": 0.20000000298023224,
//   "kxc": 0.800000011920929,
//   "kyc": 0.800000011920929,
//   "kxd": 0.20000000298023224,
//   "kyd": 0.800000011920929,
//   "kType": 0,
//   "kSym": 0,
//   "kApply": false,
//   "cropAuto": false,
//   "ratioN": 0,
//   "ratioD": 0
// }

const CLIPPING_PARAMS_BIN_STR = '000000001c1ccc3d1c644d3e0000803fc482663f0000000000000000cdcc4c3ecdcc4c3ecdcc4c3fcdcc4c3ecdcc4c3fcdcc4c3fcdcc4c3ecdcc4c3f000000000000000000000000010000000000000000000000'

testOperation(OPERATION, CLIPPING_PARAMS_BIN_STR)
