#ifndef MOTOR_ARDUBOT_H
#define MOTOR_ARDUBOT_H

#include "Arduino.h"
#include <Definiciones.h>
#include <Servo.h>
#include <pt.h>

/// \def Clase que representa la conexion de un SERVO a ARDUBOT. Puede acoplarse con mas motores

class Motor : public Servo
{
	public:
		Motor();
		Motor(byte velocidadCalibrada);
		~Motor();

		/// \def conectarEn. Funcion que conecta el motor a ARDUINO
		/// \param pinSIGNAL. El pin de conexion
		void conectarEn(int pinSIGNAL);

		/// \def cambiarVelocidad. Funcion que cambia la velocidad del motor.
		/// \note ES UN PROTOTHREAD EN SI MISMA, lo que permite acoplar mas de un motor.
		///		  Para que el PT funcione correctamente, la funcion debe llamarse
		///		  de la forma: while(cambiarVelocidad(valor, duracion) != PT_WAITING);
		///		  para cualquier numero de motores.
		/// \param velocidad. Es el nuevo valor de la velocidad. Se
		///		   comprueba que la nueva velocidad no supera el valor
		/// 	   de la velocidad de seguridad. Rango maximo: 0 (velocidad
		///		   maxima hacia atras) a 180 (velocidad maxima hacia delante)
		/// 	   pasando por 90 (parado). Ver definiciones de calibracion
		///	\param duracion. Representa la rapidez a la que se efectua el
		///		   cambio. Ver definiciones de calibracion
		/// \return #defines de PT_WAITING, PT_EXITED, PT_YIELDED, PT_ENDED, 
		/// 		segun <pt.h>
		char cambiarVelocidad(byte velocidad, rapidez::intervalo duracion = rapidez::RAPIDO);
		
		/// \def activar. Funcion que activa el motor para su movimiento, puede 
		///		 aprovecharse para activar o desactivar motores acoplados segun
		///		 el caso de giro
		void activar();
		
		/// \def desactivar. Funcion que desactiva al motor para su movimiento
		/// \note Al desactivar no lo para, si no que no permite cambiar su velocidad
		/// 	  e interactuar con el motor
		void desactivar();
		
		/// \def estaActivo. Funcion que devuelve el estado activo del motor
		/// \return TRUE si esta activo
		///			FALSE si esta desactivado
		bool estaActivo() const;

		/// \def velocidad. Funcion que devuelve el valor de la velocidad actual
		/// \return el valor actual de velocidad
		byte velocidad();
		
		void invertir();

	private:
		/// Variables de la velocidad
		byte _velocidad;
		byte _velocidadParado;
		
		/// Variable de estado del motor
		bool _activo, _invertido;
		
		/// ProtoThread del motor
		struct pt _ptMotor;
};

#endif
