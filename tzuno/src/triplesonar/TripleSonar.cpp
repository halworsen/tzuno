#include "TripleSonar.h"

#define DIST_DIFF 4
#define DIST_THRESHOLD 4
#define TURN_TIME 230
#define TURN_SPEED 350

//Konstrukt�rer
TripleSonar::TripleSonar(int speed){
	this->speed = speed;
}

TripleSonar::TripleSonar(PLab_ZumoMotors *motors) : TripleSonar(400){
	this->motors = motors;
}

TripleSonar::~TripleSonar() {}

//Gj�res i loopen
void TripleSonar::run() {
	if(borderLeft){
		Serial.println("BLEFT");
		back();
		turn(1);
	}
	else if(borderRight){
		Serial.println("BRIGHT");
		back();
		turn(-1);

	}
	else{
		
		if(sonarDistanceRight > DIST_THRESHOLD && sqrt(pow(sonarDistanceRight-lastSonarDistanceRight,2)) < DIST_DIFF){
			Serial.println("RIGHT");
			turn(1);

		}
		else if(sonarDistanceBack > DIST_THRESHOLD && sqrt(pow(sonarDistanceBack-lastSonarDistanceBack,2)) < DIST_DIFF){
			Serial.println("BACK");
			turn(1);
			turn(1);


		}
		else if(sonarDistanceLeft > DIST_THRESHOLD && sqrt(pow(sonarDistanceLeft-lastSonarDistanceLeft,2)) < DIST_DIFF){
			Serial.println("LEFT");
			turn(-1);

		}
		
		{
			motors->setSpeeds(speed,speed);
			Serial.println("FORWARD");
		}
	}
}

//Kollisjon
void TripleSonar::contact(){
	
}

//Beveglse

void TripleSonar::back(){
	motors->setSpeeds(-speed, -speed);
	delay(200);
}

void TripleSonar::turn(int dir){
	if(dir>=0){
		
		motors->setSpeeds(TURN_SPEED, -TURN_SPEED);
		delay(TURN_TIME);
		
	}
	else{
		motors->setSpeeds(-TURN_SPEED, TURN_SPEED);
		delay(TURN_TIME);
		
	}
	
}