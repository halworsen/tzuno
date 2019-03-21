#ifndef _border_crawler_h_
#define _border_crawler_h_

#include "../strategy/Strategy.h"


/*
Strategi: Border Crawler
---------------------------------------
Kjører langs med kanten med sonar vendt inn. Snur og
Angriper hvis den ser noe, og kjører så på full fart til
den eventuelt treffer kanten og begynner å lete igjen.

VED START: Sonar vendes til høyre mot motstander. Hvis 
motstander da nøler noe vil vi kunne treffe den i siden.
*/
class BorderCrawler : public Strategy {
private:

public:
    BorderCrawler(PLab_ZumoMotors* motors, Servo* servo);
    ~BorderCrawler();

    void run();
};

#endif