


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


#define rate 5

Humiino sensorOne(2, rate);

void setup(){
	Serial.begin(9600);
	//Serial.println("Booting up.....");
	//Serial.println("Starting to output data.....");
}

void loop(){
	Serial.println("");
	delay(5000);
  
	//sensorOne
	//Serial.print("Sensor 1: ");
	Serial.print(sensorOne.readHumidity(),1);
  //sensorOne.readHumidity();
	//Serial.print("%\t");
	//Serial.print(sensorOne.readTemperature(), 1);
  //sensorOne.readTemperature();
	//Serial.println("*C");
}
