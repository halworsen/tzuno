#include "AggressiveRadar.h"

// Konstruktører
AggressiveRadar::AggressiveRadar(int aSpeed, int tSpeed) : attackSpeed(aSpeed), turnSpeed(tSpeed) {
    this->name = "Aggressive Radar";
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

    // If enemy seen, attack
}