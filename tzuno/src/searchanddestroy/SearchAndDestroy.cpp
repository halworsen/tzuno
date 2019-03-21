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
        //motors->turnRight(300, 180);
        motors->setSpeeds(300, -300);
        delay(400);
        failCount = failTresh;
    }
    else if (borderLeft)
    {
        // Snu høyre
        motors->backward(300, 10);
        //motors->turnRight(300, 120);
        motors->setSpeeds(300, -300);
        delay(300);
        i = 50;
        failCount = failTresh;
    }
    else if (borderRight)
    {
        // Snu venstre
        motors->backward(300, 10);
        //motors->turnLeft(300, 120);
        motors->setSpeeds(-300, 300);
        delay(300);
        i = 0;
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
            motors->setSpeeds(
                abs(sin(i * 0.03 - 0) * maxSpeed),
                abs(cos(i * 0.03 + 0) * maxSpeed)
            );
            //motors->setSpeeds(100, 100);
            i++;
        }
        else failCount++;
    }
}