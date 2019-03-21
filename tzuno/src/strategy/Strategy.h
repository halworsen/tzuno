#ifndef _strategy_h_
#define _strategy_h_

#include <Arduino.h>
#include <PLab_ZumoMotors.h>
#include <Servo.h>
//#include <ZumoShield.h>

/*
Strategisuperklassen, alle strategier implementerer denne.

Metoder og variabler som alle strategier bruker defineres her.

Feltet name defineres i underklassens kosntruktør til bruk 
i valg av strategi
*/

class Strategy {
protected:
    float sonarDistance;
    float lateSonarDistance;
    PLab_ZumoMotors* motors;
    Servo* servo;
	bool borderLeft;
	bool borderRight;
    // Debugging
    char state;
public:
    // Konstruktør og destruktør gjør ingenting annet enn 
    // å måtte være implementert.
    Strategy();
    ~Strategy();

    // Virtuelle funksjoner må implementeres av alle strategiklasser
    virtual void run() = 0;

    void setSonarDistance(float d);
    
    char getState();
	
	void setBorderLeft(bool l);
	void setBorderRight(bool r);  

    void setServo(int degrees);
};

#endif
