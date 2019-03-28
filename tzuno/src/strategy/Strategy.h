#ifndef _strategy_h_
#define _strategy_h_

#include <Arduino.h>
#include <PLab_ZumoMotors.h>
#include <NewServo.h>
//#include <ZumoShield.h>

/*
Strategisuperklassen, alle strategier implementerer denne.

Metoder og variabler som alle strategier bruker defineres her.

Feltet name defineres i underklassens kosntruktør til bruk 
i valg av strategi
*/

class Strategy {
protected:
	float sonarDistance=0;//Ikke i bruk
    float sonarDistanceLeft=0;
	float sonarDistanceRight=0;
	float sonarDistanceBack=0;
    float lastSonarDistanceLeft;
	float lastSonarDistanceRight;
	float lastSonarDistanceBack;
    PLab_ZumoMotors* motors;
    NewServo* servo;
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

    void setSonarDistanceLeft(float d);
	void setSonarDistanceRight(float d);

	void setSonarDistanceBack(float d);
	void setSonarDistance(float d);

    
    char getState();
	
	void setBorderLeft(bool l);
	void setBorderRight(bool r);  

    void setServo(int degrees);
};

#endif
