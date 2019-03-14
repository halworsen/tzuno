#include "SonarUtil.h"


float distance(){
	unsigned int time = sonar.ping();
	float distance = sonar.convert_cm(time);
	return distance
}