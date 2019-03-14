#include <ZumoShield.h>
#include <NewPing.h>

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
//#define QTR_THRESHOLD  1900 // microseconds
//#define NUM_SENSORS    6    
// Sonar
#define ECHOPIN       0 
#define TRIGGERPIN    1
#define MAX_DISTANCE  100
//=========================================================


//=========================================================
// Deklarasjoner
//---------------------------------------------------------
Strategy* strat;

ZumoMotors motors;

Pushbutton button(ZUMO_BUTTON);

NewPing sonar(TRIGGERPIN, ECHOPIN, MAX_DISTANCE);

//unsigned int sensor_values[NUM_SENSORS];
//=========================================================


void setup() {
    strat = new AggressiveRadar(&motors);
    button.waitForButton();
    Serial.begin(9600);
}


void loop() {
    // Mellom rundene
    

    // Infrarød sjekk på bane
    // Borderdetection
    

    // Sonarmåling
    {
      unsigned int t = sonar.ping();
      float dist = sonar.convert_cm(t);
      strat->setSonarDistance(dist);
      Serial.println(dist);
    }
    

    // Strategiens loop
    strat->run();
}
