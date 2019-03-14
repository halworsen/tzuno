#include "Strategy.h"

Strategy::Strategy() {}

Strategy::~Strategy() {}


void Strategy::setSonarDistance(float d) { sonarDistance = d > 0 ? d : sonarDistance; }
