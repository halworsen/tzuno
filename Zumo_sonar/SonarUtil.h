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

const int echoPin;
const int triggerPin;
int maxDistance;

float distance();
//Servo styring?

#endif