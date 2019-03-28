#include "Strategy.h"

#define safewait 2

Strategy::Strategy() {}

Strategy::~Strategy() {}


char Strategy::getState() { return state; }


void Strategy::setSonarDistanceLeft(float d) {
    this->lastSonarDistanceLeft = sonarDistanceLeft;
	delay(safewait);
    this->sonarDistanceLeft = d; 
}
void Strategy::setSonarDistanceRight(float d) {
    this->lastSonarDistanceRight = sonarDistanceRight;
	delay(safewait);
    this->sonarDistanceRight = d; 
}
void Strategy::setSonarDistanceBack(float d) {
    this->lastSonarDistanceBack = sonarDistanceBack;
	delay(safewait);
    this->sonarDistanceBack = d; 
}
void Strategy::setSonarDistance(float d) {
    this->sonarDistance = d; 
}
void Strategy::setBorderLeft(bool l) { this->borderLeft = l; }
	
void Strategy::setBorderRight(bool r) { this->borderRight = r; }


void Strategy::setServo(int degrees) {
    servo->write(degrees);
}
