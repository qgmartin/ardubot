#include <CNY70.h>
#include <Sensor.h>
#include <pt.h>
#include <Definiciones.h>
#include <Motor.h>
#include <Servo.h>

Motor motorDerecho(96), motorIzquierdo(96);
CNY70 sensorCentral, sensorLateral;
struct pt ptSensores;

// Definicion de constantes estilo macros
#define pinMotorDerecho 10
#define pinMotorIzquierdo 9
#define pinVoutCentral 3
#define pinVoutLateral 5

void arrancar()
{
  while(motorDerecho.cambiarVelocidad(95, rapidez::INSTANTANEO) == PT_YIELDED &&
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
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
    else
    {
      digitalWrite(13, HIGH);
      delay(200);
      digitalWrite(13, LOW);
      delay(200);
    }
  }
  PT_END(unPt);
}

void setup() 
{
  PT_INIT(&ptSensores);
  pinMode(13, OUTPUT);
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
