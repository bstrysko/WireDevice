/*
  WireDevice.h - WireDevice library for Arduino
  Copyright (c) 2014 Brent Strysko.  All right reserved.
*/

#ifndef TwoWireDevice_h
#define TwoWireDevice_h

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Wire.h"

#define TWO_WIRE_DEVICE_BUFFER_SIZE 20

typedef byte (*TwoWireDeviceReadFunction)(byte, byte*);
typedef void (*TwoWireDeviceWriteFunction)(byte, byte*, byte);

class TwoWireDevice
{
  private:
    static bool isWrite;
    static byte reg;
    static byte bufferSize;
    static byte buffer[TWO_WIRE_DEVICE_BUFFER_SIZE];
    static TwoWireDeviceReadFunction readFunction;
    static TwoWireDeviceWriteFunction writeFunction;

    static void request();
    static void receive(int count);
  public:
    TwoWireDevice();
    void begin(byte address,
      TwoWireDeviceReadFunction readFunction,
      TwoWireDeviceWriteFunction writeFunction);
};

extern TwoWireDevice WireDevice; 

#endif
