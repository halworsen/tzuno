#include "SearchAndDestroy.h"


SearchAndDestroy::SearchAndDestroy(PLab_ZumoMotors* motors) {
    this->motors = motors;
    this->failCount = failTresh;
    this->i = 0;
    this->state = 's';
}

SearchAndDestroy::~SearchAndDestroy() {}



void SearchAndDestroy::run() {
    // Borderdetection
    if (borderLeft && borderRight)
    {
        // Snu 180 grader
        motors->backward(300, 10);
        motors->turnRight(300, 180);
        failCount = failTresh;
    }
    else if (borderLeft)
    {
        // Snu høyre
        motors->backward(300, 10);
        motors->turnRight(300, 120);
        failCount = failTresh;
    }
    else if (borderRight)
    {
        // Snu venstre
        motors->backward(300, 10);
        motors->turnLeft(300, 120);
        failCount = failTresh;
    }
    // Attack
    else if (0 < sonarDistance && sonarDistance < tresh)
    {
        motors->setSpeeds(400, 400);
        failCount = 0;
        this->state = 'a';
    }
    // Wandering
    else 
    {
        if (failCount == failTresh) 
        {
            // Velg tilfeldig hastighet på hvert hjul innen et intervall
            // motors->setSpeeds(
            //     cos(i * 0.02 + 0) * maxSpeed/2 + maxSpeed/2,
            //     cos(i * 0.02 + 0) * maxSpeed/2 + maxSpeed/2
            // );
            motors->setSpeeds(100, 100);
            i++;
        }
        else failCount++;
    }
}