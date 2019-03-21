#include "Strategy.h"

Strategy::Strategy() {}

Strategy::~Strategy() {}


char Strategy::getState() { return state; }


void Strategy::setSonarDistance(float d) {
    lateSonarDistance = sonarDistance;
    sonarDistance = d > 0 ? d : 1000; 
}

void Strategy::setBorderLeft(bool l) { this->borderLeft = l; }
	
void Strategy::setBorderRight(bool r) { this->borderRight = r; }


void Strategy::setServo(int degrees) {
    servo->write(degrees);
}
