#include <GP2D05.h>
#include <Sensor.h>
#include <Definiciones.h>
#include <Motor.h>
#include <Servo.h>
#include <pt.h>

Motor motorIzquierdo(96), motorDerecho(95);
GP2D05 sensorFrontal, sensorLateral; // lateral en la derecha
static struct pt ptGestionFrontal, ptBusquedaParedDerecha; // threads que gestionan los dos GP2D05

const int pinMotorDerecho = 10;
const int pinMotorIzquierdo = 9;
const int pinVOSensorFrontal = 5;
const int pinVINSensorFrontal = 4;
const int pinVOSensorLateral = 3;
const int pinVINSensorLateral = 2;

void arrancar()
{
  while (motorDerecho.cambiarVelocidad(95, rapidez::INSTANTANEO) == PT_YIELDED &&
         motorIzquierdo.cambiarVelocidad(96, rapidez::INSTANTANEO) == PT_YIELDED);
}

// declaracion y definicion de las funciones auxiliares
static PT_THREAD(buscaParedDerecha(struct pt* unPt))
{
  PT_BEGIN(unPt);
  while (1)
  {
    PT_WAIT_UNTIL(unPt, !sensorLateral.seActiva());
    {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
  }
  PT_END(unPt);
}

// declaramos y definimos el thread de los sensores
static PT_THREAD(gestionFrontal(struct pt* unPt))
{
  PT_BEGIN(unPt); // empieza el protothread
  while (1)
  {
    PT_WAIT_UNTIL(unPt, sensorFrontal.seActiva()); // establecemos las condiciones
    {
      digitalWrite(13, HIGH);
      delay(200);
      digitalWrite(13, LOW);
      delay(200);
      // girar a la izquierda siempre
    }
  }
  PT_END(unPt);
}

void setup()
{
  PT_INIT(&ptGestionFrontal);
  PT_INIT(&ptBusquedaParedDerecha);
  pinMode(13, OUTPUT);
  motorIzquierdo.invertir();
  motorDerecho.conectarEn(pinMotorDerecho);
  motorIzquierdo.conectarEn(pinMotorIzquierdo);
  sensorFrontal.conectarEn(pinVOSensorFrontal);
  sensorFrontal.fijarVin(pinVINSensorFrontal);
  sensorLateral.conectarEn(pinVOSensorLateral);
  sensorLateral.fijarVin(pinVINSensorLateral);
  arrancar();
}

void loop()
{
  buscaParedDerecha(&ptBusquedaParedDerecha);
  gestionFrontal(&ptGestionFrontal);
}
