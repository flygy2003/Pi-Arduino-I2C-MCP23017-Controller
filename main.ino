#include "Wire.h"
#include <Stdint.h>
//Bank A is pins 21-28 on right side of chip
//Bank B is pins 1-8 on left side of chip
enum Bank {
  GPIOA = 0x12,
  GPIOB = 0x13
};
//Provide enumeration for pin generation
enum Pin
{
  PIN1 =  1, 
  PIN2 =  1 << 1,
  PIN3 =  1 << 2, 
  PIN4 =  1 << 3,
  PIN5 =  1 << 4,
  PIN6 =  1 << 5,
  PIN7 =  1 << 6,
  PIN8 =  1 << 7 
};

//registers define I/O direction
enum IODIR {
  BANK_A =  0x01,
  BANK_B =  0x00
};

//directions
enum IO {
  IN = 1,
  OUT = 0
};

//Address definitions
enum ADDR {
  DEFADDR = 0x20,
  ADDRA = 0x40,
  ADDRB = 0x41,
  ADDRC = 0x42,
  ADDRD = 0x43,
  ADDRE = 0x44,
  ADDRF = 0x45,
  ADDRG = 0x46,
  ADDRH = 0x47
}

//modulate individual pin
uint8_t setField(uint8_t prev, Pin pin, bool state)
{
  if(state) {
    return (prev | (0x01 << static_cast<uint8_t>(pin)));
  
  } else {
    return (prev & ~(0x01 << static_cast<uint8_t>(pin)));
  }
}

void init(ADDR addr, Bank bank, IO direction) 
{
  Wire.beginTransmission(addr);
  Wire.write(bank); 
  Wire.write(direction);
  Wire.endTransmission();
}

void write(ADDR addr, Bank bank, Pin pin, bool state) 
{
  uint8_t pkt = setField((static_cast<uint8_t>(pull(addr, bank))), pin, state);
  Wire.beginTransmission(addr);
  Wire.write(bank);
  Wire.write(pkt);
  Wire.endTransmission();
}

bool read(ADDR addr, Bank bank, int pin) 
{
  uint8_t TRNS = (((pull(addr, bank)) >> static_cast<uint8_t>((pin-1))) & static_cast<uint8_t>(0x01))
  if (TRNS == static_cast<uint8_t>(0x01)) {
    return true;
  } else if (TRNS == static_cast<uint8_t>(0x00)){
    return false;
  } else {
    Serial.println("read unsuccessful")
  }
}

void push(ADDR addr, Bank bank, uint8_t val) 
{
  Wire.beginTransmission(addr);
  Wire.write(bank);
  Wire.write(val);
  Wire.endTransmission();
}

uint8_t pull(ADDR addr, Bank bank) 
{
  Wire.beginTransmission(addr);
  return Wire.read(bank);
  Wire.endTransmission();
}

void setup() 
{
  // put your setup code here, to run once:
  Wire.begin();
  init(DEFADDR, GPA, O);
  init(DEFADDR, GPB, O);
}

void loop() 
{

}