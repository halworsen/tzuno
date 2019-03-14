#include <ZumoShield.h>
#include <ZumoMotors.h>

// Strategier
#include "AggressiveRadar.h"
#include "AlertPassive.h"

Strategy* strat;

void setup() {
    strat = new SpinAttack();
    //dasda
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
