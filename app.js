var i2c = require('i2c-bus'), io = i2c.openSync(1)
var fb = require('firebase')
var config = {
  apiKey: "AIzaSyDJ31YrXt8JAPUZHYGNRS8WNjoHaz8ssuE",
  authDomain: "home-b7104.firebaseapp.com",
  databaseURL: "https://home-b7104.firebaseio.com",
  projectId: "home-b7104",
  storageBucket: "home-b7104.appspot.com",
  messagingSenderId: "42864256502"
}
fb.initializeApp(config)
var db = fb.database()
//  Device address (A0-A2)
let DEVICEA = 0x20 
let DEVICEB = 0x41 
//  Pin direction register
let IODIRA = 0x00
let IODIRB = 0x01
//  Register for inputs
let GPIOA  = 0x12 
let GPIOB  = 0x13

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
                   (bankA ? IODIRA : IODIRB), iodir)
}

function write(addrA, pin, state) {
  io.writeByteSync((addrA ? DEVICEA : DEVICEB), 
                   ((pin > 8) ? GPIOA : GPIOB), 
                   setField(io.readByteSync((addrA ? DEVICEA : DEVICEB), 
                                            ((pin > 8) ? GPIOA : GPIOB)),
                            ((pin > 8) ? (pin-8):pin),
                            state))
}

function read(addrA, pin) {
  let trns = ((io.readByteSync((addrA ? DEVICEA : DEVICEB), ((pin > 8) ? GPIOA : GPIOB)) >> (pin - 1)) & 0x01)
  if (trns == 0x01) {
    return true
  } else if (trns == 0x00) {
    return false
  } else {
    console.log("read unsuccessful")
  }
}

init(true, true, 0x00)
init(true, false, 0x00)
db.ref("VirtualDB").on("child_changed", (data) => {
  if(data.key+1 < 24) {
    console.log(`key: ${data.key}`)
    console.log(`state: ${data.val().state}`)
    // write(((data.key+1 > 16) ? false : true), data.key+1, data.val().state)
    write(true, data.key, data.val().state)
    console.log(io.readByteSync(DEVICEA, GPIOB))
  } else {
    console.log(`index ${data.key} will be written to by station 1`)
    io.writeByteSync(0x20, 0x13, 0xcf)
  }
})
