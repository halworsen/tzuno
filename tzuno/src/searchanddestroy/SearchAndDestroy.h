#ifndef _search_and_destroy_h_
#define _search_and_destroy_h_

#include "../strategy/Strategy.h"

/*
Strategi: Search and Destroy
------------------------------------------
Vandrer på måfå på banen og angriper hvis den ser en fiende
*/

class SearchAndDestroy : public Strategy {
private:
    const short tresh = 40; // Sonar attack treshold
    const short failTresh = 20; // Ticks before aborting attack
    short failCount;

    const short freq = 25;  // Wandering variation frequency
    short i;
    const unsigned short minSpeed = 10;
    const unsigned short maxSpeed = 300;

    
public:
    SearchAndDestroy(PLab_ZumoMotors* motors);
    ~SearchAndDestroy();

    void run();

};

#endif