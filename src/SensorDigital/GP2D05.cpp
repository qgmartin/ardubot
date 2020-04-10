#include "GP2D05.h"

GP2D05::GP2D05() : Sensor()
{

}

GP2D05::~GP2D05()
{

}

bool GP2D05::seActiva() const
{
	bool deteccion;
	
	// empieza la deteccion
	digitalWrite(_pinVIN, HIGH);
	delay(2);
	digitalWrite(_pinVIN, LOW);
	delay(56); 
	// fin de la deteccion
	
	if (digitalRead(_pinVO) == LOW)
		deteccion = true;
	else
		deteccion = false;
		
	digitalWrite(_pinVIN, HIGH); // reinicia
	return deteccion;
}