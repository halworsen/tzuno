#ifndef _sonar_util_h_
#define _sonar_util_h_

#include <Arduino.h>
#include <NewPing.h>

/*
Informasjon fra Sonar
---------------------
Gir informasjon knyttet til sonaren
-Avstand som den gir


*/

#define echoPin     0
#define triggerPin  1
#define maxDistance 25

NewPing* sonar = new NewPing(triggerPin, echoPin, maxDistance);

float distance();
//Servo styring?

#endif