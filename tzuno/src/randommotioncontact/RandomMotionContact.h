#ifndef _random_motion_contact_h_
#define _random_motion_contact_h_

#include <Arduino.h>
#include "../strategy/Strategy.h"


/*
Strategi "Random Motion (until)Contact"
APPROVED
Kjører tilfeldig, og unngår å kjøre ut, til den kolliderer 
med motstander og kjører på
*/

class RandomMotionContact: public Strategy{
private:
	int speed;
	bool collision;
public:
	RandomMotionContact(int speed);
	RandomMotionContact(PLab_ZumoMotors* motors);
	~RandomMotionContact();
	
	//Gjøres i loopen
	void run();
	
	//Kollisjon
	void contact();
	
	//Beveglse
	void turn(int dir);
	
};

#endif