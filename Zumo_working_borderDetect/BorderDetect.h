#ifndef _border_detect_h_
#define _border_detect_h_


#include <Arduino.h>
#include <Wire.h>
#include <ZumoShield.h>

/*
Instrument kant
-bool for venstre og høyre side
*/
#define LED 13
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1900 // microseconds
//WARNING!!! Det her e den aller viktigste verdien
//med verdi 90 kjøre den på bordet og alt mørkere og stoppe på hvitt ark
//grå underlag(som baksiden av skrivebøker) kan man ha verdi 100, kanskje 110
// jo større verdi man kan ha, jo mer sensitiv for kanten blir den :))

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];

ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

bool border_left();

bool border_right();
#endif