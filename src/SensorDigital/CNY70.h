#ifndef CNY70_H
#define CNY70_H

#include "Arduino.h"
#include "Sensor.h"

/// \def Clase que emula a un sensor de proximidad CNY70 conectado sobre
///		 un pin digital. Ver clase Sensor

class CNY70 : public Sensor
{
	public:
		CNY70();
		~CNY70();
		
		/// \def Redefinicion de la funcion fijarVin, pues este sensor
		///		 carece de VIN. Codigo vacio, no hara nada
		virtual void fijarVin(int pinVIN);
		
		/// \def seActiva. Cuando el voltaje sea HIGH, devuelve
		/// \return TRUE (ha visto blanco - o distinto de negro)
		/// 		FALSE en caso contrario
		virtual bool seActiva() const;
};

#endif