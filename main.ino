#include "Wire.h"

//Bank A is pins 21-28 on right side of chip
//Bank B is pins 1-8 on left side of chip
#define GPA 0x12
#define GPB 0x13

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
#define IODIRA 0x01
#define IODIRB 0x00

//directions
#define I 0xFF
#define O 0x00

//Address definitions
#define DEFADDR 0x20
#define ADDRA 0x40
#define ADDRB 0x41
#define ADDRC 0x42
#define ADDRD 0x43
#define ADDRE 0x44
#define ADDRF 0x45
#define ADDRG 0x46
#define ADDRH 0x47

//modulate individual pin
uint8_t setField(uint8_t prev, Pin pin, bool state)
{
  if(state) {
    return prev | ( 0x01 << static_cast<uint8_t>(pin) );
  
  } else {
    return prev & ~( 0x01 << static_cast<uint8_t>(pin) );
  }
}

void init(const addr, const bank, const direction) 
{
  Wire.beginTransmission(addr);
  Wire.write(bank);
  Wire.write(direction);
  Wire.endTransmission();
}

void write(const addr, const bank, Pin pin, bool state) 
{
  byte act = pull(addr, bank);
  byte pkt = setField(act, pin, state);
  Wire.beginTransmission(addr);
  Wire.write(bank);
  Wire.write(pkt);
  Wire.endTransmission();
}

void read(const addr, const bank, const pin) 
{

}

void push(const addr, const bank, byte val) 
{
  
}

uint8_t pull(const addr, const bank) 
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