'use strict'

const assert = require('assert')
const sidecar = require('..')

function testOperation (operation, paramsStr) {
  const paramsObj = sidecar.decodeParams(operation, paramsStr)
  // console.log(`${operation}Params:`, JSON.stringify(paramsObj))

  const encodedParamsStr = sidecar.encodeParams(operation, paramsObj)

  assert.strictEqual(encodedParamsStr, paramsStr)
  console.log(`${operation} test - OK`)
}

module.exports = testOperation
