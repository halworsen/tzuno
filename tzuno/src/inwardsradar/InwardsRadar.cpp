#include "InwardsRadar.h"

//Konstrukt�rer
InwardsRadar::InwardsRadar(int speed){
	this->speed = speed;
	this->degrees = 0;
	this->prev_degrees = degrees;
}

InwardsRadar::InwardsRadar(PLab_ZumoMotors *motors, NewServo* servo) : InwardsRadar(400){
	this->motors = motors;
	this -> servo = servo;
}

InwardsRadar::~InwardsRadar() {}

//Gj�res i loopen
void InwardsRadar::run() {
	if(borderLeft){
		back();
		turn(1);
		degrees = 0;
	}
	else if(borderRight){
		back();
		turn(-1);
		degrees = 180;
		
	}
	else if (0<sonarDistance && sonarDistance<20){
		turn(90-degrees);
	}
	else {
		motors->setSpeeds(speed,speed);
		servo->write(degrees);
	}
	//servo->write(degrees);
}

//Kollisjon
void InwardsRadar::contact(){
	
}

//Beveglse
void InwardsRadar::extra_delay(int degrees){
	if(degrees == prev_degrees){
		delay(200);
	}
	prev_degrees = degrees;
}
void InwardsRadar::back(){
	motors->setSpeeds(-speed, -speed);
	delay(200);
}

void InwardsRadar::turn(int dir){
	if(dir>=0){
		
		motors->setSpeeds(speed, -speed);
		//delay(100);
		
	}
	else{
		motors->setSpeeds(-speed, speed);
		//delay(100);
		
	}
	extra_delay(degrees);

}