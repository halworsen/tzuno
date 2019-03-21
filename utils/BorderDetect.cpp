#include "BorderDetect.h"

bool border_left(){
	return sensor_values[0] < QTR_THRESHOLD;
}

bool border_right(){
	return sensor_values[5] < QTR_THRESHOLD;
}

void read_s(){
	sensors.read(sensor_values);
}