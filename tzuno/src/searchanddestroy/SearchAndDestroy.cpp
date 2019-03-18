#include "SearchAndDestroy.h"


SearchAndDestroy::SearchAndDestroy(PLab_ZumoMotors *motors) {
    this->motors = motors;
    this->failCount = failTresh;
    this->i = 0;
}

SearchAndDestroy::~SearchAndDestroy() {}


void SearchAndDestroy::run() {
    // Borderdetection
    if (borderLeft && borderRight)
    {
        // Snu 180 grader
        motors->turnRight(400, 180);
    }
    else if (borderLeft)
    {
        // Snu høyre
        motors->turnRight(400, 30);
    }
    else if (borderRight)
    {
        // Snu venstre
        motors->turnLeft(400, 30);
    }
    // Attack
    else if (0 < sonarDistance < tresh)
    {
        motors->setSpeeds(400, 400);
        failCount = 0
    }
    // Wandering
    else 
    {
        if (failCount == failTresh) 
        {
            // Velg tilfeldig hastighet på hvert hjul innen et intervall
            if (i > 0)
                i--;
            else {
                motors->setLeftSpeed(random(minSpeed, maxSpeed));
                motors->setRightSpeed(random(minSpeed, maxSpeed));
                i = freq;
            }
        }
        else failCount++;
    }
}