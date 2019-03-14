#ifndef _alert_passive_h_
#define _alert_passive_h_

#include <Arduino.h>
#include "../strategy/Strategy.h"

/*
Strategi: På vakt
-------------------------------------------------
* Hardware-krav: Sonar på alle sider, evt. kjøre radarteknikken
Ser etter angripere, og kjører til siden, snur og får overtaket
*/

class AlertPassive : public Strategy {
//private:
    
public:
    AlertPassive();
    ~AlertPassive();

    void run();
};

#endif