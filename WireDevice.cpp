/*
  WireDevice.h - WireDevice library for Arduino
  Copyright (c) 2014 Brent Strysko.  All right reserved.
*/

#include "WireDevice.h"

#include <Wire.h>

bool TwoWireDevice::isWrite = false;
byte TwoWireDevice::reg = 0;
byte TwoWireDevice::bufferSize = 0;
byte TwoWireDevice::buffer[TWO_WIRE_DEVICE_BUFFER_SIZE];
TwoWireDeviceReadFunction TwoWireDevice::readFunction = 0;
TwoWireDeviceWriteFunction TwoWireDevice::writeFunction = 0;

TwoWireDevice::TwoWireDevice()
{
}

void TwoWireDevice::begin(byte address,
      TwoWireDeviceReadFunction readFunction,
      TwoWireDeviceWriteFunction writeFunction)
{
	TwoWireDevice::readFunction = readFunction;
	TwoWireDevice::writeFunction = writeFunction;

	Wire.begin(address);
	Wire.onRequest(TwoWireDevice::request);
	Wire.onReceive(TwoWireDevice::receive);
}

void TwoWireDevice::request()
{
	byte readBuffer[TWO_WIRE_DEVICE_BUFFER_SIZE];
	byte numBytesRead = readFunction(TwoWireDevice::reg, readBuffer);
	Wire.write(readBuffer, numBytesRead);
}

void TwoWireDevice::receive(int count)
{
	byte temp = Wire.read();
    isWrite = !(!(temp & 0x80));
	reg = (temp & ~0x80);
  
	int i = 0;
  
	while(Wire.available())
	{
		buffer[i] = Wire.read();
		i++;
	}

	bufferSize = i;
  
	if(isWrite)
	{
		writeFunction(reg, buffer, bufferSize);
	}
}

TwoWireDevice WireDevice = TwoWireDevice();

