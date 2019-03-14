#include <ZumoShield.h>
#include <NewPing.h>
//#include <Wire.h> //Er kanskje relevant for border detection

//=========================================================
// Strategier
//---------------------------------------------------------
#include "src/aggressiveradar/AggressiveRadar.h"
#include "src/alertpassive/AlertPassive.h"
//=========================================================


//=========================================================
// Defines
//---------------------------------------------------------
// IR
#define LED 13
#define QTR_THRESHOLD  1900 // microseconds
#define NUM_SENSORS    6    
// Sonar
#define ECHOPIN       0 
#define TRIGGERPIN    1
#define MAX_DISTANCE 25
//=========================================================


//=========================================================
// Deklarasjoner
//---------------------------------------------------------
Strategy* strat;

ZumoMotors motors;

Pushbutton button(ZUMO_BUTTON);

NewPing sonar(TRIGGERPIN, ECHOPIN, MAX_DISTANCE);

unsigned int sensor_values[NUM_SENSORS];

ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN)
//=========================================================


void setup() {
    strat = new AggressiveRadar(&motors);
    button.waitForButton();
}


void loop() {
    // Mellom rundene
    

    // Infrarød sjekk på bane
    // Borderdetection
	{
		sensors.read(sensor_values);
		bool r =sensor_values[5] < QTR_THRESHOLD;
		bool l =sensor_values[0] < QTR_THRESHOLD;
		strat->setBorderRight(r);
		strat->setBorderLeft(l);
	}
    // Sonarmåling
    {
      unsigned int t = sonar.ping();
      float dist = sonar.convert_cm(t);
      strat->setSonarDistance(dist);
    }
    

    // Strategiens loop
    strat->run();
}
