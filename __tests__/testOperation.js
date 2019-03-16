'use strict'

const assert = require('assert')
const sidecar = require('..')

function testOperation (operation, paramsStr) {
  let paramsObj = sidecar.decodeParams(operation, paramsStr)
  // console.log(`${operation}Params:`, JSON.stringify(paramsObj))

  let encodedParamsStr = sidecar.encodeParams(operation, paramsObj)

  assert.strictEqual(encodedParamsStr, paramsStr)
  console.log(`${operation} test - OK`)
}

module.exports = testOperation
