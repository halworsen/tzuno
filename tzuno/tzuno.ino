#include <ZumoShield.h>
#include <ZumoMotors.h>

// Strategier
#include "AggressiveRadar.h"
#include "AlertPassive.h"

Strategy* strat;



void setup() {

    // Instansiering av strategi, eksempel
    strat = new AggressiveRadar();
    // Endre strategi:
    strat = new AlertPassive();
}

void loop() {
    // Mellom rundene
    if ("pause")
    {
        // Hjelp-kommando: plasseres inni meny
        Serial.println(F(
            "Tilgjengelige kommandoer:\n" +
            " - strat [strategi] : Endre strategi\n"
        ));
        
        string in = Serial.readLine();

        // Prosesser kommando

    }

    // Infrarød sjekk på bane

    // Sonarmåling
    strat->setSonarDistance(0);

    // Strategiens loop
    strat->run();
}
