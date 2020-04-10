#include "Motor.h"

using namespace rapidez;

Motor::Motor() : Servo()
{
	
}

Motor::Motor(byte velocidadCalibrada) : Servo(), _velocidadParado(velocidadCalibrada), _velocidad(velocidadCalibrada)
{
	this->write(_velocidad);	
	this->activar();
	_invertido = false;
}

void Motor::conectarEn(int pinSIGNAL)
{
	this->attach(pinSIGNAL);
}

Motor::~Motor()
{

}

char Motor::cambiarVelocidad(byte velocidad, rapidez::intervalo duracion)
{
	PT_BEGIN(&_ptMotor)
	while(1)
	{
		PT_WAIT_UNTIL(&_ptMotor, _activo);
		if(velocidad <= _velocidadParado + 30 && velocidad >= _velocidadParado - 30)
		{
			if(!_invertido)
			{
				while(_velocidad != velocidad)
				{
					if(_velocidad > velocidad)
					{
						_velocidad--;
						this->write(_velocidad);
						delay(duracion);
						PT_YIELD_UNTIL(&_ptMotor, _activo);
					}
					else
					{
						_velocidad++;
						this->write(_velocidad);
						delay(duracion);
						PT_YIELD_UNTIL(&_ptMotor, _activo);
					}
				}
			}
			else
			{
				while(_velocidad != 2 * _velocidadParado - velocidad)
				{
					if(_velocidad > 2 * _velocidadParado - velocidad)
					{
						_velocidad--;
						this->write(_velocidad);
						delay(duracion);
						PT_YIELD_UNTIL(&_ptMotor, _activo);
					}
					else
					{
						_velocidad++;
						this->write(_velocidad);
						delay(duracion);
						PT_YIELD_UNTIL(&_ptMotor, _activo);
					}
				}
			}
		}
		PT_RESTART(&_ptMotor);
	}
	PT_END(&_ptMotor); 
}

byte Motor::velocidad()
{
	return _velocidad;
}

void Motor::activar()
{
	_activo = true;
}

void Motor::desactivar()
{
	_activo = false;
}

bool Motor::estaActivo() const
{
	return _activo;
}

void Motor::invertir()
{
	_invertido = !_invertido;
}