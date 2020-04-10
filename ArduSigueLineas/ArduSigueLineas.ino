#include <CNY70.h>
#include <Sensor.h>
#include <pt.h>
#include <Definiciones.h>
#include <Motor.h>
#include <Servo.h>

Motor motorDerecho(95), motorIzquierdo(96);
CNY70 sensorCentral, sensorLateral;
struct pt ptSensores;

// Definicion de constantes estilo macros
#define pinMotorDerecho 10
#define pinMotorIzquierdo 9
#define pinVoutCentral 3
#define pinVoutLateral 5

void arrancar()
{
  while(motorDerecho.cambiarVelocidad(100, rapidez::INSTANTANEO) == PT_YIELDED &&
        motorIzquierdo.cambiarVelocidad(100, rapidez::INSTANTANEO) == PT_YIELDED);
}

void parar()
{
  while(motorDerecho.cambiarVelocidad(96, rapidez::INSTANTANEO) == PT_YIELDED &&
        motorIzquierdo.cambiarVelocidad(96, rapidez::INSTANTANEO) == PT_YIELDED);
}

static PT_THREAD(hiloSensores(struct pt* unPt))
{
  PT_BEGIN(unPt);
  while(1)
  {
    PT_WAIT_UNTIL(unPt, sensorCentral.seActiva());
    if(!sensorLateral.seActiva())
    {
      while(sensorCentral.seActiva())
      {
        // estara girando mientras no encuentre de nuevo la linea negra, i.e.
        // que el sensorCentral permanezca activado
        while(motorIzquierdo.cambiarVelocidad(109, rapidez::INSTANTANEO) == PT_YIELDED &&
              motorDerecho.cambiarVelocidad(91) == PT_YIELDED);
      }
      arrancar(); // restauramos la velocidad inicial
    }
    else
    {
      // situacion simetrica, para el otro lado
      while(sensorCentral.seActiva())
      {
        while(motorDerecho.cambiarVelocidad(109, rapidez::INSTANTANEO) == PT_YIELDED &&
              motorIzquierdo.cambiarVelocidad(91) == PT_YIELDED);
      }
      arrancar();
    }
  }
  PT_END(unPt);
}

void setup() 
{
  PT_INIT(&ptSensores);
  motorIzquierdo.invertir();
  motorDerecho.conectarEn(pinMotorDerecho);
  motorIzquierdo.conectarEn(pinMotorIzquierdo);
  sensorCentral.conectarEn(pinVoutCentral);
  sensorLateral.conectarEn(pinVoutLateral);
  arrancar();
}


void loop() 
{
  // Se llama de forma recurrente al PT
  hiloSensores(&ptSensores);
}
