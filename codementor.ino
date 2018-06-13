// type here your function
#include <Stdint.h>
enum Pin{
  PIN1 =  1 , 
  PIN2 =  1 << 1,
  PIN3 =  1 << 2, 
  PIN4 =  1 << 3,
  PIN5 =  1 << 4,
  PIN6 =  1 << 5,
  PIN7 =  1 << 6,
  PIN8 =  1 << 7 
};


#define  PIN0   1; 
#define  PIN1   2; 
#define  PIN2   4; 




void ssetField (Pin field, int* num)
{
  *num = *num | field;
}

void unsetField (Pin field, int* num)
{
  *num = *num & (~field);
}
//{0,0,0,0,0,0,0,0} 0x00

/* 01010101 |
00100000 =

01110101 << 1 

11001101

00000001

(2 << 1) == (int)2   00000100  0x04
 */

uint8_t setField(uint8_t prev, Pin pin, bool state)
{
  if(state) {
    return prev | ( 0x01 << static_cast<uint8_t>(pin) );
  
  } else {
    return prev & ~( 0x01 << static_cast<uint8_t>(pin) );
  }
}

setField( val, PIN0, true);



