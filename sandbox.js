var i2c = require('i2c-bus'), io = i2c.openSync(1)

let DEVICEA = 0x20
let DEVICEB = 0x21
//  Pin direction register
let IODIRA = 0x00
let IODIRB = 0x01
//  Register for inputs
let GPIOA = 0x12
let GPIOB = 0x13

function setField(prev, pin, state) {
  if (state) {
    return (prev | (0x01 << (pin - 1)))
  } if (state == false) {
    return (prev & ~(0x01 << (pin - 1)))
  } else {
    console.log("invalid state arguement")
  }
}

function init(addrA, bankA, iodir) {
  io.writeByteSync((addrA ? DEVICEA : DEVICEB),
                  (bankA ? IODIRA : IODIRB), 
                  iodir)
}