'use strict'

const assert = require('assert')
const { decodeParams, encodeParams, UnknownOperationError } = require('..')

try {
  decodeParams('foo', '0000')
  assert.fail('decodeParams should throw error')
} catch (err) {
  assert.ok(err instanceof UnknownOperationError)
  assert.equal(err.message, "Unknown operation 'foo'")
}

try {
  encodeParams('foo', '0000')
  assert.fail('encodeParams should throw error')
} catch (err) {
  assert.ok(err instanceof UnknownOperationError)
  assert.equal(err.message, "Unknown operation 'foo'")
}
