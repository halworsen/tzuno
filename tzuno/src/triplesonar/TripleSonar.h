#ifndef _triple_sonar_h_
#define _triple_sonar_h_

#include <Arduino.h>
#include "../strategy/Strategy.h"


/*
Strategi "TripleSonar"

Kj�rer tilfeldig, og unng�r � kj�re ut,men har tre sonarer
og kan f� zumoen til � svinge
*/

class TripleSonar: public Strategy{
private:
	int speed;
	bool collision;
public:
	TripleSonar(int speed);
	TripleSonar(PLab_ZumoMotors* motors);
	~TripleSonar();
	
	//Gj�res i loopen
	void run();
	
	//Kollisjon
	void contact();
	
	//Beveglse
	void turn(int dir);
	void back();
	
};

#endif