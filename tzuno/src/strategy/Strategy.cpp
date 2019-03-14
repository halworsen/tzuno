#include "Strategy.h"

Strategy::Strategy() {}

Strategy::~Strategy() {}


void Strategy::setSonarDistance(int d) { sonarDistance = d > 0 ? d : sonarDistance; }