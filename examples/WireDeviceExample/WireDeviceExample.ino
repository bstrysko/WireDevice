/*
  WireDeviceExample.ino - WireDevice library for Arduino
  Copyright (c) 2014 Brent Strysko.  All right reserved.
*/

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

/*
 * Called when the I2CMaster wants to read data from the Arduino 
 * @param reg the register the master wants to read data from
 * @param buffer a byte array that the Arduino will send to the master
 * @return the number of bytes to send back to the master
 */
byte wireDeviceRead(byte reg, byte* buffer)
{ 
  switch(reg)
  {
    case REGISTER_A:
    {
      buffer[0] = 'A';
      return 1;
    }
    case REGISTER_B:
    {
      buffer[0] = 'B';
      buffer[1] = 'A';
      return 2; 
    }
  }
  
  return 0;
}

/*
 * Called when the I2CMaster wants to write to the Arduino
 * @param reg the register the master wants to write data to
 * @param buffer a byte array of size bufferSize containing data
 * from the master.
 * @param bufferSize the size of buffer
 */
void wireDeviceWrite(byte reg, byte* buffer, byte bufferSize)
{
  switch(reg)
  {
     case REGISTER_A:
     {
        // buffer contains bufferSize bytes from the I2C master
        // that are adressed to REGISTER_A
        break;
     }
     case REGISTER_B:
     {
       // buffer contains bufferSize bytes from the I2C master
       // that are adressed to REGISTER_B
       break;
     }
  }
}
