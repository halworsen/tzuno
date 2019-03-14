#include <ZumoShield.h>

//=========================================================
// Strategier
//---------------------------------------------------------
#include "AggressiveRadar.h"
#include "AlertPassive.h"
//=========================================================


//=========================================================
// Defines
//---------------------------------------------------------
// IR
#define QTR_THRESHOLD  1900 // microseconds
#define NUM_SENSORS    6    
//=========================================================


//=========================================================
// Deklarasjoner
//---------------------------------------------------------
Strategy* strat;

ZumoMotors motors;

Pushbutton button(ZUMO_BUTTON);

usigned int sensor_values[NUM_SENSORS];
//=========================================================

void setup() {
    strat = new AggressiveRadar();
}

void loop() {
    // Mellom rundene
    

    // Infrarød sjekk på bane
    // Borderdetection
    

    // Sonarmåling
    strat->setSonarDistance(0);

    // Strategiens loop
    strat->run();
}
