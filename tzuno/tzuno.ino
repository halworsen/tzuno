#include <ZumoShield.h>
#include <ZumoMotors.h>

// Strategier
#include "src/aggressiveradar/AggressiveRadar.h"
#include "src/alertpassive/AlertPassive.h"

// Defines

Strategy* strat;

void setup() {
    strat = new AggressiveRadar();
}

void loop() {
    // Mellom rundene
    

    // Infrarød sjekk på bane

    // Sonarmåling
    strat->setSonarDistance(0);

    // Strategiens loop
    strat->run();
}
