#include "AggressiveRadar.h"

#define ARENA_SIZE 100

// Konstruktører
AggressiveRadar::AggressiveRadar(int aSpeed, int tSpeed) : attackSpeed(aSpeed), turnSpeed(tSpeed) {
}

AggressiveRadar::AggressiveRadar(int speed) : AggressiveRadar(speed, speed) {

}

AggressiveRadar::AggressiveRadar() : AggressiveRadar(200, 200) {
    
}

// Settere
void AggressiveRadar::setAttackSpeed(int s) {
    attackSpeed = 0 < s < 400 ? s : attackSpeed;
}

void AggressiveRadar::setTurnSpeed(int s) {
    turnSpeed = 0 < s < 400 ? s : turnSpeed;
}


void AggressiveRadar::run() {
    // While enemy not found, spin, use sonar
    if (sonarDistance > ARENA_SIZE)
    {
      motor.setSpeed(400, -400);
    }
    // If enemy seen, attack
    else
    {
      motor.setSpeed(400, 400);
    }
}
