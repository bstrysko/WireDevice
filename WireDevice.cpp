/*
  WireDevice.h - WireDevice library for Arduino
  Copyright (c) 2014 Brent Strysko.  All right reserved.
*/

#include "WireDevice.h"

#include <Wire.h>

byte TwoWireDevice::reg = 0;
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
	reg = Wire.read();

	//write
	if(count >= 2)
	{
		byte buffer[TWO_WIRE_DEVICE_BUFFER_SIZE];
	
		int i = 0;

		while(Wire.available())
		{
			buffer[i] = Wire.read();
			i++;
		}
	
		writeFunction(reg, buffer, i);
	}
}

TwoWireDevice WireDevice = TwoWireDevice();

