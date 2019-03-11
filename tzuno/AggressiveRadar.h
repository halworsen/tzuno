#ifndef _aggressive_radar_h_
#define _aggressive_radar_h_

#include <Arduino.h>
#include "Strategy.h"

class AggressiveRadar : public Strategy {
private:
    int attackSpeed;
    int turnSpeed;
public:
    // Set speeds to tweek aggression
    AggressiveRadar(int aSpeed, int tSpeed);
    AggressiveRadar(int speed);
    AggressiveRadar();
    ~AggressiveRadar();
    void run();


    void setAttackSpeed(int s);
    void setTurnSpeed(int s);
};

#endif