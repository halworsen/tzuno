#include "TripleSonar.h"

#define DIST_DIFF 4
#define DIST_THRESHOLD 35
#define TURN_TIME 200

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
		back();
		turn(1);
	}
	else if(borderRight){
		back();
		turn(-1);

	}
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
	else {
		motors->setSpeeds(speed,speed);
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
		
		motors->setSpeeds(speed, -speed);
		
	}
	else{
		motors->setSpeeds(-speed, speed);
		
	}
	delay(TURN_TIME);
}