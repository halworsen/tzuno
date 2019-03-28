#include "Strategy.h"

Strategy::Strategy() {}

Strategy::~Strategy() {}


char Strategy::getState() { return state; }


void Strategy::setSonarDistanceLeft(float d) {
    lastSonarDistanceLeft = sonarDistanceLeft;
	delay(2);
    sonarDistanceLeft = d > 0 ? d : 1000; 
}
void Strategy::setSonarDistanceRight(float d) {
    lastSonarDistanceRight = sonarDistanceRight;
	delay(2);
    sonarDistanceRight = d > 0 ? d : 1000; 
}
void Strategy::setSonarDistanceBack(float d) {
    lastSonarDistanceBack = sonarDistanceBack;
	delay(2);
    sonarDistanceBack = d > 0 ? d : 1000; 
}
void Strategy::setSonarDistance(float d) {
    sonarDistance = d > 0 ? d : 1000; 
}
void Strategy::setBorderLeft(bool l) { this->borderLeft = l; }
	
void Strategy::setBorderRight(bool r) { this->borderRight = r; }


void Strategy::setServo(int degrees) {
    servo->write(degrees);
}
