#ifndef _aggressive_radar_h_
#define _aggressive_radar_h_

#include <Arduino.h>
#include "../strategy/Strategy.h"

/*
Strategi "Aggresiv Radar"
-------------------------------------------------
Snurrer rundt seg selv som en radar, og så snart den sanser et objekt 
i nærheten angriper den fort. Stopper så snart den mister motstander 
av syne for å unngå å kjøre ut.

Ekstra: Få med seg hvilken retning motstander forsvant, og spinn i den 
retningen for å spare tid.

*/
#define ARENA_SIZE 100

class AggressiveRadar : public Strategy {
private:
    int attackSpeed;
    int turnSpeed;

public:
    // Set speeds to tweek aggression
    AggressiveRadar(int aSpeed, int tSpeed);
    AggressiveRadar(int speed);
    AggressiveRadar();
    AggressiveRadar(ZumoMotors* motors);
    ~AggressiveRadar();


    void run();


    void setAttackSpeed(int s);
    void setTurnSpeed(int s);
};

#endif