#ifndef _inwards_radar_h_
#define _inwards_radar_h_

#include <Arduino.h>
#include "../strategy/Strategy.h"


/*
Strategi "Inwards Radar"
APPROVED
Kjører tilfeldig, og unngår å kjøre ut,men har en radar som peker innover
og kan få zumoen til å svinge
*/

class InwardsRadar: public Strategy{
private:
	int speed;
	bool collision;
	int degrees;
public:
	InwardsRadar(int speed);
	InwardsRadar(PLab_ZumoMotors* motors, Servo* servo);
	~RandomMotionContact();
	
	//Gjøres i loopen
	void run();
	
	//Kollisjon
	void contact();
	
	//Beveglse
	void turn(int dir);
	void back();
	
};

#endif