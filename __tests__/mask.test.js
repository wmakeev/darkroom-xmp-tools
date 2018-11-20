'use strict'

const assert = require('assert')
const sidecar = require('..')

const {
  decodeGradientMask, encodeGradientMask,
  decodeCircleMask, encodeCircleMask,
  decodeEllipseMask, encodeEllipseMask
} = sidecar

let paramsObj, encodedStr

/*
gradientMask: {
  "anchor": [0.9867653250694275, 0.03192557767033577],
  "rotation": 0,
  "compression": 0.10485762357711792,
  "steepness": 0
}
*/
const GRADIENT_MASK_BLOB = 'a79c7c3f65c4023d0000000098bfd63d00000000'

paramsObj = decodeGradientMask(GRADIENT_MASK_BLOB)
// console.log('gradientMask:', JSON.stringify(paramsObj))

encodedStr = encodeGradientMask(paramsObj)

assert.strictEqual(encodedStr, GRADIENT_MASK_BLOB)
console.log('gradient mask test - OK')

/*
circleMask: {
  "center":[0.5418254733085632,0.48308634757995605],
  "radius":0.13251766562461853,
  "border":0.06990056484937668
}
*/
const CIRCLE_MASK_BLOB = '13b50a3f1857f73eb6b2073e07288f3d'

paramsObj = decodeCircleMask(CIRCLE_MASK_BLOB)
// console.log('circleMask:', JSON.stringify(paramsObj))

encodedStr = encodeCircleMask(paramsObj)

assert.strictEqual(encodedStr, CIRCLE_MASK_BLOB)
console.log('circle mask test - OK')

/*
ellipseMask: {
  "center":[0.8039848208427429,0.28927695751190186],
  "radius":[0.13810302317142487,0.16776850819587708],
  "rotation":90,
  "border":0.08391694724559784,
  "flags":"DT_MASKS_ELLIPSE_EQUIDISTANT"
}
*/
const ELLIPSE_MASK_BLOB = 'f3d14d3f1c1c943ee16a0d3e82cb2b3e0000b442a6dcab3d00000000'

paramsObj = decodeEllipseMask(ELLIPSE_MASK_BLOB)
// console.log('ellipseMask:', JSON.stringify(paramsObj))

encodedStr = encodeEllipseMask(paramsObj)

assert.strictEqual(encodedStr, ELLIPSE_MASK_BLOB)
console.log('ellipse mask test - OK')
