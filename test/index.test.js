const inclose5 = require('../src/index.js')

const dataset = new Uint8Array([0,0,0,1,1,1,0,0,0,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0])
const result = inclose5.run(dataset.buffer, 4, 6)
console.log(`Algorithm result: `, JSON.stringify(result))