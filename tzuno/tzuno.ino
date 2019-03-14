#include <ZumoShield.h>

// Utilities

//=========================================================
// Strategier
//---------------------------------------------------------
#include "AggressiveRadar.h"
#include "AlertPassive.h"
//=========================================================

// Defines
#define QTR_THRESHOLD  1900 // microseconds


//=========================================================
// Deklarasjoner
//---------------------------------------------------------
Strategy* strat;

ZumoMotor motors
//=========================================================s

void setup() {
    strat = new AggressiveRadar();
}

void loop() {
    // Mellom rundene
    

    // Infrarød sjekk på bane
    // Borderdetection, 

    // Sonarmåling
    strat->setSonarDistance(0);

    // Strategiens loop
    strat->run();
}
