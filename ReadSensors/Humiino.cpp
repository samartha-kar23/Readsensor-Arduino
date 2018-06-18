/*
	Humiino.cpp - Library for reading DHT22 sensor.
	Created Autumn, 2014
	Released into the Public Domain
*/

#include "Arduino.h"
#include "Humiino.h"

Humiino::Humiino(int pin, int updateRate):_pin(pin), _updateRate(updateRate)
{
	if(updateRate < 2){
		Serial.println("TOO FAST UPDATERATE CHOSEN, USING DEAFULT OF 5 SECONDS...");
		_updateRate = 2;
	}
}


float Humiino::readHumidity()
{
	if(((millis() - _lastread) > (_updateRate * 1000)) || (_firstReading)){
		if(readData()){
			return _humidity;
		}else{
			Serial.println("AN ERROR OCCURED WHILE READING, RETURNING NAN, PLEASE CHECK YOUR CONNECTIONS AND SETTINGS!");
			return NAN;
		}
	}else{
		return _humidity;
	}
}

float Humiino::readTemperature()
{
	if(((millis() - _lastread) > (_updateRate * 1000)) || (_firstReading)){
		if(readData()){
			return _temperature;
		}else{
			Serial.println("AN ERROR OCCURED WHILE READING, RETURNING NAN, PLEASE CHECK YOUR CONNECTIONS AND SETTINGS!");
			return NAN;
		}
	}else{
		return _temperature;
	}
}

boolean Humiino::readData()
{
	//VARIABLES FOR RECEIVEING DATA
	byte _element = 0, _count =7;

	//REGISTERS LASTREAD AND TURNS FIRSTREADING TO FALSE
	if(_firstReading){
		_firstReading = false;
	}
	_lastread = millis();

	//CHECKS IF THERE HAVE BEEN A ROLLOVER
	if(_lastread > millis()){
		_lastread = 0;
	}
	
	//CLEARS DATA IN ARRAY AND ASSIGNS 0 TO EVERY ELEMENT
	for(byte i = 0; i < 5; i++){
		_data[i] = 0;
	}
	
	//SENDS DATA REQUEST TO SENSOR
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delay(20);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(40);
	pinMode(_pin, INPUT);
	
	//READ SENSOR CONFIRMATION OR PRINT TIMEOUT ERROR
	_timeout = 10000;
	while(digitalRead(_pin) == LOW){
		if(_timeout-- == 0){
			Serial.println("ERROR: TIMEOUT at LOW START-SIGNAL");
			return false;
		}
	}
	_timeout = 10000;
	while(digitalRead(_pin) == HIGH){
		if(_timeout-- == 0){
			Serial.println("ERROR: TIMEOUT at HIGH START-SIGNAL");
			return false;
		}
	}
	
	//READ DATA
	for(byte i = 0; i < 40; i++){
		_timeout = 10000;
		while(digitalRead(_pin) == LOW){
			if(_timeout-- == 0){
				Serial.println("ERROR: TIMEOUT at READ SIGNAL LOW");
				return false;
			}
		}
		
		unsigned long length = micros();
		
		_timeout = 10000;
		while(digitalRead(_pin) == HIGH){
			if(_timeout-- == 0){
				Serial.println("ERROR: TIMEOUT at READ SIGNAL HIGH");
				return false;
			}
		}
		
		if((micros() - length) > 43){
			_data[_element] |= (1 << _count);
		}
		if(_count == 0){
			_count = 7;
			_element++;
		}else{
			_count--;
		}
	}
	
	//COMPARE CHECKSUM
	_checksum = (_data[0] + _data[1] + _data[2] + _data[3]);
	if (_data[4] != _checksum){
		Serial.println("ERROR: at CHECKSUM");
		return false;
	}
	
	//CONVERTS AND STORE DATA
	_humidity = word(_data[0], _data[1]) * 0.1;
	if(_data[2] & 0x80){
		_temperature = (-0.1 * word(_data[2] & 0x7F, _data[3]));
	}else{
		_temperature = (0.1 * word(_data[2], _data[3]));
	}
	return true;
}
