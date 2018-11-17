#include <Wire.h>
#include <stdint.h>
//Bank A is pins 21-28 on right side of chip
//Bank B is pins 1-8 on left side of chip
enum Bank {
  GPIOA = 0x12,
  GPIOB = 0x13
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
};

//modulate individual pin
uint8_t setField(uint8_t prev, int pin, bool state)
{
  if(state) {
    return (prev | (0x01 << static_cast<uint8_t>(pin)));
  
  } else {
    return (prev & ~(0x01 << static_cast<uint8_t>(pin)));
  }
}

void init(ADDR addr, IODIR bank, IO io) 
{
  Wire.beginTransmission(addr);
  Wire.write(bank); 
  Wire.write(io);
  Wire.endTransmission();
}

void write(ADDR addr, int pin, bool state) 
{
  uint8_t pkt = setField((static_cast<uint8_t>(pull(addr, (pin>8) ? GPIOA : GPIOB))), ((pin>8) ? (pin-9) : pin), state);
  Wire.beginTransmission(addr);
  Wire.write((pin>8) ? GPIOA : GPIOB);
  Wire.write(pkt);
  Wire.endTransmission();
}

bool read(ADDR addr, int pin) 
{
  uint8_t TRNS = (((pull(addr, ((pin>8) ? GPIOA : GPIOB)))
                    >> 
                    static_cast<uint8_t>((pin>8) ? (pin-9) : pin)) & static_cast<uint8_t>(0x01));
  if (TRNS == static_cast<uint8_t>(0x01)) {
    return true;
  } else if (TRNS == static_cast<uint8_t>(0x00)){
    return false;
  } else {
    Serial.println("read unsuccessful");
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
  return Wire.requestFrom(bank, 1);
  Wire.endTransmission();
}

void setup() 
{
  // put your setup code here, to run once:
  Wire.begin();
  init(DEFADDR, BANK_A, OUT);
  init(DEFADDR, BANK_B, OUT);
  /*
  * Obtain states from firebase
  * save in bitwise array va, vb
  * cast uint8_t(va, vb) = v_a, v_b
  * push(DEFADDR, BANK_A, v_a);
  * push(DEFADDR, BANK_B, v_b);
  */
}
void loop() {  
  for (int i = 0; i<17; i++) {
    write(DEFADDR, i, true);
    delay(50);
  }
}
