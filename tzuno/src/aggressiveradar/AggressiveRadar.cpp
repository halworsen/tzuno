#include "AggressiveRadar.h"


// Konstruktører
AggressiveRadar::AggressiveRadar(int aSpeed, int tSpeed) : attackSpeed(aSpeed), turnSpeed(tSpeed) {
}

AggressiveRadar::AggressiveRadar(ZumoMotors *motors) : AggressiveRadar(400, 400) {
    this->motors = motors;
}

// Settere
void AggressiveRadar::setAttackSpeed(int s) {
    attackSpeed = 0 <= s <= 400 ? s : attackSpeed;
}

void AggressiveRadar::setTurnSpeed(int s) {
    turnSpeed = 0 <= s <= 400 ? s : turnSpeed;
}


void AggressiveRadar::run() {
    // While enemy not found, spin, use sonar
    if (sonarDistance > ARENA_SIZE &&
      lateSonarDistance > ARENA_SIZE)
    {
      motors->setSpeeds(turnSpeed, -turnSpeed);
    }
    // Border detection
    else if (borderLeft || borderRight)
    {
      motors->setSpeeds(-200, -200);
      delay(200);
      motors->setSpeeds(0, 0);
    }
    // If enemy seen, attack
    else
    {
      motors->setSpeeds(attackSpeed, attackSpeed);
    }
}
