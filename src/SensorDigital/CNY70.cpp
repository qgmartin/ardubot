#include "CNY70.h"

CNY70::CNY70() : Sensor()
{
	_pinVIN = -1;
}

CNY70::~CNY70()
{

}

void CNY70::fijarVin(int pinVIN)
{

}

bool CNY70::seActiva() const
{
	return digitalRead(_pinVO) == HIGH;
}