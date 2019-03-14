#include "SonarUtil.h"

NewPing sonar(triggerPin, echoPin, maxDistance);
float distance(){
	unsigned int time = sonar.ping();
	float distance = sonar.convert_cm(time);
	return distance
}