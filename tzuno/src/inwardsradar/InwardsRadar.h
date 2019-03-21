#ifndef _inwards_radar_h_
#define _inwards_radar_h_

#include <Arduino.h>
#include "../strategy/Strategy.h"


/*
Strategi "Inwards Radar"
APPROVED
Kj�rer tilfeldig, og unng�r � kj�re ut,men har en radar som peker innover
og kan f� zumoen til � svinge
*/

class InwardsRadar: public Strategy{
private:
	int speed;
	bool collision;
	int degrees;
public:
	InwardsRadar(int speed);
	InwardsRadar(PLab_ZumoMotors* motors, Servo* servo);
	~InwardsRadar();
	
	//Gj�res i loopen
	void run();
	
	//Kollisjon
	void contact();
	
	//Beveglse
	void turn(int dir);
	void back();
	
};

#endif