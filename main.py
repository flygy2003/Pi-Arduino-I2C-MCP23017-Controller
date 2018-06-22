import 
import smbus
import time
 
#bus = smbus.SMBus(0)  # Rev 1 Pi uses 0
bus = smbus.SMBus(1) # Rev 2 Pi uses 1
 
DEVICEA = 0x40 # Device address (A0-A2)
DEVICEB = 0x41 
IODIRA = 0x00 # Pin direction register
IODIRB = 0x01
GPIOA  = 0x12 # Register for inputs
GPIOB  = 0x13

#manipulate individual pins
def setField(prev, pin, state):
  if state:
    return (prev | (0x01 << (pin - 1)))
  if state == false:
    return (prev & ~(0x01 << (pin - 1)))
#set iodir variable to spec
def init(addr, bankA, iodir):
  bus.write_byte_data(addr, (IODIRA if bankA else IODIRB, iodir))
#write to specified pin 1-8 within specified register and address
def write(addrA, pin, state):
  bus.write_byte_data((DEVICEA if addrA else DEVICEB), (GPIOA if pin > 8 else GPIOB), setField(bus.read_byte_data((DEVICEA if addrA else DEVICEB), (GPIOA if pin > 8 else GPIOB)), ((pin - 9) if (pin > 8) else pin), state))
#read from specified pin 1-8 within specified register and address
def read(addrA, pin):
  trns = ((bus.read_byte_data((DEVICEA if addrA else DEVICEB), (GPIOA if pin > 8 else GPIOB)) >> (pin - 1)) & 0x01)
  if trns == 0x01:
    return True
  elif trns == 0x00:
    return False
  else print("read unsuccessful")

