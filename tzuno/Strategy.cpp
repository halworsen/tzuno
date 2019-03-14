#include "Strategy.h"

Strategy::Strategy() {}

Strategy::~Strategy() {}


static string Strategy::getName() { return name; }


void Strategy::setSonarDistance(int d) { sonarDistance = d > 0 ? d : sonarDistance; }