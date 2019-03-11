#include <ZumoShield.h>
#include <NewServo.h>
#include "AggressiveRadar.h"

Strategy* strat;

void setup() {

    // Instansiering av strategi, eksempel
    strat = new AggressiveRadar();
}

void loop() {
    // Infrarød sjekk på bane

    // Sonarmåling

    // Strategiens loop
    strat->run();
}
