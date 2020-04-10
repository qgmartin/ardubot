#include <GP2D05.h>
#include <Sensor.h>
#include <Definiciones.h>
#include <Motor.h>
#include <Servo.h>
#include <pt.h>

Motor motorIzquierdo(96), motorDerecho(98);
GP2D05 sensorFrontal, sensorLateral; // lateral en la derecha
static struct pt ptGestionFrontal, ptBusquedaParedDerecha; // threads que gestionan los dos GP2D05
static struct pt ptCorreccionLineaRecta;

const int pinMotorDerecho = 10;
const int pinMotorIzquierdo = 9;
const int pinVOSensorFrontal = 5;
const int pinVINSensorFrontal = 4;
const int pinVOSensorLateral = 3;
const int pinVINSensorLateral = 2;
unsigned long int tiempoUltimaCorreccion;

void arrancar()
{
  while (motorDerecho.cambiarVelocidad(110, rapidez::INSTANTANEO) == PT_YIELDED &&
         motorIzquierdo.cambiarVelocidad(110, rapidez::INSTANTANEO) == PT_YIELDED);
}

void parar()
{
  while(motorDerecho.cambiarVelocidad(96, rapidez::INSTANTANEO) == PT_YIELDED &&
        motorIzquierdo.cambiarVelocidad(96, rapidez::INSTANTANEO) == PT_YIELDED);
}

void marchaAtras()
{
  while(motorDerecho.cambiarVelocidad(70, rapidez::INSTANTANEO) == PT_YIELDED &&
        motorIzquierdo.cambiarVelocidad(70, rapidez::INSTANTANEO) == PT_YIELDED);
}

// declaracion y definicion de las funciones auxiliares
static PT_THREAD(buscaParedDerecha(struct pt* unPt))
{
  PT_BEGIN(unPt);
  while(1)
  {
    PT_WAIT_UNTIL(unPt, !sensorLateral.seActiva());
    {
      delay(200);
      while(motorDerecho.cambiarVelocidad(92, rapidez::INSTANTANEO) == PT_YIELDED);
      PT_WAIT_WHILE(unPt, !sensorLateral.seActiva());
      while(motorDerecho.cambiarVelocidad(110, rapidez::INSTANTANEO) == PT_YIELDED);
    }
  }
  PT_END(unPt);
}

// declaramos y definimos el thread de los sensores
static PT_THREAD(gestionFrontal(struct pt* unPt))
{
  PT_BEGIN(unPt); // empieza el protothread
  while(1)
  {
    PT_WAIT_UNTIL(unPt, sensorFrontal.seActiva()); // establecemos las condiciones
    {
      parar();
      marchaAtras();
      PT_WAIT_WHILE(unPt, sensorFrontal.seActiva());
      arrancar();
      while(motorIzquierdo.cambiarVelocidad(75, rapidez::INSTANTANEO) == PT_YIELDED);
      PT_WAIT_WHILE(unPt, sensorFrontal.seActiva());
      delay(400);
      while(motorIzquierdo.cambiarVelocidad(110, rapidez::INSTANTANEO) == PT_YIELDED);
    }
  }
  PT_END(unPt);
}

void setup()
{
  PT_INIT(&ptGestionFrontal);
  PT_INIT(&ptBusquedaParedDerecha);
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
