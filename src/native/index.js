'use strict'
const binding = require(`./build/Release/binding`)

function generateAuthorization() {
    return binding.hello()
}

module.exports = {
    generateAuthorization,
}
