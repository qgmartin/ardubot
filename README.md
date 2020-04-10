# ardubot

The code in this project enables an Arduino board (Arduino UNO - new boards have not been tested yet) to autonomously solve two problems:
1. Line tracking
2. Labyrinth scape

The arduino board is equipped with four sensors: CNY70 for line tracking and GP2D05 for obstacle detection. Each one has its own library, [CNY70](src/SensorDigital/CNY70) and [GP2D05](src/SensorDigital/GP2D05.h). Both libraries inherit from an [abstract sensor class](src/SensorDigital/Sensor.h) defining the minimum capabilities of a sensor, i.e. pin connection and activation trigger.

The [servo library](src/Servo/Motor.h) is an extension from the standard [Servo](https://www.arduino.cc/en/Reference/Servo), that enhances servo rotation capabilities.

The [protothreads(Pt) library](src/Pt) allow for pseudo concurrent execution by yielding function calls. Pt were created by [Adam Dunkels](http://dunkels.com/adam/pt/index.html), under the open source BSD-style license.

## Line tracking
See [code](ArduLaberinto/ArduLaberinto.ino)

## Labyrinth scape
See [code](ArduSigueLineas/ArduSigueLineas.ino)

All code can be found in spanish, no translation to english is expected to come in the short term unless requested. Code was developed in 2014 and hasn't been updated since then. 
