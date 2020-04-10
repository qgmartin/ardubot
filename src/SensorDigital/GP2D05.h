#ifndef GP2D05_H
#define GP2D05_H

#include "Arduino.h"
#include "Sensor.h"

/// \def Clase que emula a un sensor de proximidad con voltimetro GP2D05.
/// 	 Para un funcionamiento correcto, asegurar la conexion para _pinVO
///		 y para _pinVIN (imprescindible)

class GP2D05 : public Sensor
{
	public:
		GP2D05();
		~GP2D05();
		
		/// \def seActiva. Devuelve
		/// \return TRUE (hay objeto), es _pinVO = LOW
		/// 		FALSE (no hay objeto), es _pinVO = HIGH
		/// \note Cuidado con la calibracion de la resistencia variable
		virtual bool seActiva() const;
};

#endif