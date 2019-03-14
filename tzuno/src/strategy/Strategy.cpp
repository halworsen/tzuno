#include "Strategy.h"

Strategy::Strategy() {}

Strategy::~Strategy() {}


void Strategy::setSonarDistance(float d) { sonarDistance = d > 0 ? d : 1000; }

void Strategy::setBorderLeft(bool l) { this->borderLeft = l; }
	
void setBorderRight(bool r) { this->borderRight = r; }
