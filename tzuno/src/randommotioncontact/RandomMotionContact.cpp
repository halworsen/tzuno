#include "RandomMotionContact.h"

//Konstruktører
RandomMotionContact::RandomMotionContact(int speed){
	this->speed = speed;
}

RandomMotionContact::RandomMotionContact(PLab_ZumoMotors *motors) : RandomMotionContact(400){
	this->motors = motors;
}
//Gjøres i loopen
void RandomMotionContact::run() {
	if(borderLeft){
		turn(1);
	}
	else if(borderRight){
		turn(-1);
	}
	else {
		motors->setSpeeds(speed,speed);
	}
}

//Kollisjon
void RandomMotionContact::contact(){
	
}

//Beveglse
void RandomMotionContact::turn(int dir){
	if(dir){
		motors->setSpeeds(-speed, -speed);
		delay(200);
		motors->setSpeeds(speed, -speed);
		delay(200);
		motors->setSpeeds(speed, speed);
		
	}
	else{
		motors->setSpeeds(-speed, -speed);
		delay(200);
		motors->setSpeeds(-speed, speed);
		delay(200);
		motors->setSpeeds(speed, speed);
		
	}
}