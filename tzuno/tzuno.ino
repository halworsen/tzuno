#include <ZumoShield.h>
#include "SpinAttack.h"

Strategy* strat;

void setup() {
    strat = new SpinAttack();
}

void loop() {
    strat->run();
}
