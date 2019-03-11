#ifndef _strategy_h_
#define _strategy_h_

#include <Arduino.h>

/*
Strategisuperklassen, alle strategier implementerer denne.

Metoder og variabler som alle strategier bruker defineres her.
*/

class Strategy {
public:
    // Konstruktør og destruktør gjør ingenting annet enn 
    // å måtte være implementert.
    Strategy() {}
    ~Strategy() {}

    // Virtuelle funksjoner må implementeres av alle strategiklasser
    virtual void run() = 0;

};

#endif