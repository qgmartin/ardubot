#ifndef SENSOR_H
#define SENSOR_H

#include "Arduino.h"

/// \def Clase que define un sensor digital. Vale para cualquier sensor que 
/// 	 emita un valor de voltaje cuando se active
/// \note El que sea digital viene marcado por la funcion seActiva

class Sensor
{
	public:
		/// \def Sensor. Constructor y destructor por defecto
		Sensor();
		~Sensor();

		/// \def conectarEn. Funcion que establece la conexion en el pin
		/// \param pinSIGNAL. El valor del pin en el que se conecta, VO
		void conectarEn(int pinSIGNAL);
		
		/// \def fijarVin. Funcion que da el valor para Vin, si es necesario.
		///		 Dejar cuerpo vacio en la herencia si no precisa de VIN
		/// \param pinVIN. El valor del pin de la conexion
		virtual void fijarVin(int pinVIN);

		/// \def seACtiva. Funcion que devuelve el resultado obtenido por la
		/// 	 percepcion del entorno. Como actuar, debera hacerse
		/// 	 desde un nivel mas alto en la jerarquia del codigo. Como
		///		 se activa se especificara segun las caracteristicas del sensor
		/// \return TRUE si el detector se ha activado
		///			FALSE si el detector no "ve" nada
		virtual bool seActiva() const = 0;

	protected:
		/// Variable que almacena el pin de conexion. Es necesaria
		/// para la lectura del estado del pin (ver seActiva()). Su
		/// valor permanecera constante durante la existencia del objeto
		int _pinVO;
		int _pinVIN;
};

#endif
