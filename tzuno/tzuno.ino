#include <ZumoShield.h>
#include "SpinAttack.h"

Strategy* strat;

void setup() {
    strat = new SpinAttack();
void setup() {
    //dasda
    strat = new AggressiveRadar();
}

void loop() {
    strat->run();
}
