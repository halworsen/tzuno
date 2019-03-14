#include <ZumoShield.h>
#include <ZumoMotors.h>

// Strategier
#include "AggressiveRadar.h"
#include "AlertPassive.h"

Strategy* strat;



void setup() {
<<<<<<< HEAD
    strat = new SpinAttack();
void setup() {
    //dasda
    strat = new AggressiveRadar();
=======

    // Instansiering av strategi, eksempel
    strat = new AggressiveRadar();
    // Endre strategi:
    strat = new AlertPassive();
>>>>>>> 7e580f3cb3d40b814caa75c42db3f53e4ae6467d
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
