#include <Wire.h>
#include <WireDevice.h>

#define WIRE_DEVICE_ADDRESS 0x12

#define REGISTER_A 0x10
#define REGISTER_B 0x14

byte i2cRead(byte reg, byte* buffer);
void i2cWrite(byte reg, byte* buffer, byte buffer_size);

void setup()
{
  Serial.begin(9600);
  Serial.println("Beginning Program");

  WireDevice.begin(WIRE_DEVICE_ADDRESS, wireDeviceRead, wireDeviceWrite);
}

void loop()
{
  // Whatever you want to do
}


byte i2c_read(byte reg, byte* buffer)
{ 
  switch(reg)
  {
    case 0x01:
    {
      buffer[0] = 10;
      return 1;
    }
    case 0x02:
    {
      buffer[0] = 20;
      buffer[1] = 21;
      return 2; 
    }
    case 0x03:
    {
      buffer[0] = s;
      return 1;
    }
  }
  
  return 0;
}

void i2c_write(byte reg, byte* buffer, byte bufferSize)
{
  switch(reg)
  {
     case REGISTER_A:
     {
    
     }
  }
}
