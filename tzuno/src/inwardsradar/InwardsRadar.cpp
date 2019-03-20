#include "InwardsRadar.h"

//Konstruktører
InwardsRadar::InwardsRadar(int speed){
	this->speed = speed;
	this->degrees = 0;
}

InwardsRadar::InwardsRadar(PLab_ZumoMotors *motors, Servo* servo) : InwardsRadar(400){
	this->motors = motors;
}
//Gjøres i loopen
void InwardsRadar::run() {
	if(borderLeft){
		back();
		turn(1);
		degrees = 180;
	}
	else if(borderRight){
		back();
		turn(-1);
		degrees = 0;
	}
	else if (0<sonarDistance && sonarDistance<20){
		turn(degrees-90);
	}
	else {
		motors->setSpeeds(speed,speed);
	}
	servo.write(degrees)
}

//Kollisjon
void InwardsRadar::contact(){
	
}

//Beveglse
void InwardsRadar::back(){
	motors->setSpeeds(-speed, -speed);
	delay(200);
}

void InwardsRadar::turn(int dir){
	if(dir){
		
		motors->setSpeeds(speed, -speed);
		delay(200);
		
	}
	else{
		motors->setSpeeds(-speed, speed);
		delay(200);
		
	}
}