#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H

#include "servo_functions.h"

void writeWeatherStationDisplay(float tempF, float pressure_hPa, float humidity);
void writeRainGaugeDisplay(float rainTotal, int tipCount);
void writeServoDisplay(int servoPosition, ServoState servoState);
void writeWindDisplay(float windSpeedMPH, const char* windDirection);
void writeStationWelcome();

#endif