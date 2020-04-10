#include "Sensor.h"

Sensor::Sensor()
{

}

Sensor::~Sensor()
{

}

void Sensor::conectarEn(int pinSIGNAL)
{
	pinMode(pinSIGNAL, INPUT);
	_pinVO = pinSIGNAL;
}

void Sensor::fijarVin(int pinVIN)
{
	pinMode(pinVIN, OUTPUT);
	_pinVIN = pinVIN;
}