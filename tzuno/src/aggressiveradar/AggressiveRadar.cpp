#include "AggressiveRadar.h"


// Konstruktører
AggressiveRadar::AggressiveRadar(int aSpeed, int tSpeed) : attackSpeed(aSpeed), turnSpeed(tSpeed) {
}

AggressiveRadar::AggressiveRadar(int speed) : AggressiveRadar(speed, speed) {

}

AggressiveRadar::AggressiveRadar() : AggressiveRadar(200, 200) {
    
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
    if (sonarDistance > ARENA_SIZE || sonarDistance == 0)
    {
      motors->setSpeeds(turnSpeed, -turnSpeed);
    }
    // If enemy seen, attack
    else
    {
      motors->setSpeeds(attackSpeed, attackSpeed);
    }
}
