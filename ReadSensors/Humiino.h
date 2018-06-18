/*
	Humiino.h - Library for reading DHT22 sensor.
	Created Autumn, 2014
	Released into the Public Domain
*/

#ifndef Humiino_h
#define Humiino_h

#include "Arduino.h"

class Humiino
{
	public:
		Humiino(int pin = 2, int updateRate = 5);
		float readHumidity();
		float readTemperature();

	private:
		boolean readData();
		int _pin;
		float _humidity, _temperature, _updateRate;
		unsigned int _timeout;
		unsigned long _lastread;
		byte _data[5], _checksum;
		boolean _firstReading = true;
};

#endif
