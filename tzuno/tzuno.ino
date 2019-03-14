#include <ZumoShield.h>
#include <ZumoMotors.h>

// Strategier
#include "AggressiveRadar.h"
#include "AlertPassive.h"

Strategy* strat;



void setup() {
    strat = new SpinAttack();
void setup() {
    //dasda
    strat = new AggressiveRadar();
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
