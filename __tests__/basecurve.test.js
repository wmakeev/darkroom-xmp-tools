'use strict'

const assert = require('assert')
const sidecar = require('..')
const testOperation = require('./testOperation')

const OPERATION = 'basecurve'

assert.strictEqual(sidecar.BasecurveType.CUBIC_SPLINE, 0)
assert.strictEqual(sidecar.BasecurveType.CATMULL_ROM, 1)
assert.strictEqual(sidecar.BasecurveType.MONOTONE_HERMITE, 2)

// basecurveParams: {
//   "basecurve_nodes": [6,0,0],
//   "basecurve_type": [2,0,0],
//   "basecurve": [
//     [
//       {"x":0,"y":0},
//       {"x":0.02822599932551384,"y":0.029676999896764755},
//       {"x":0.13321290910243988,"y":0.22817637026309967},
//       {"x":0.48416683077812195,"y":0.7271729111671448},
//       {"x":0.8670341968536377,"y":0.959578812122345},
//       {"x":1,"y":1}
//     ],
//     [],
//     []
//   ],
//   "exposure_fusion":0,
//   "exposure_stops":1,
//   "exposure_bias":1
// }
const BASECURVE_PARAMS_BIN_STR = 'gz09eJxjYIAAM6vnNnqyn22+Z3DYCS7PtNv+5Lsdo4aV/ZevsfZfl5XaMzA0QPEoGEqADYnNhCELiVMAUgARXA=='

testOperation(OPERATION, BASECURVE_PARAMS_BIN_STR)
