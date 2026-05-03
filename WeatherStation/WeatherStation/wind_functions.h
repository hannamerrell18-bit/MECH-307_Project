#ifndef WIND_FUNCTIONS_H
#define WIND_FUNCTIONS_H

extern float windSpeedMPH;
extern float windSpeedMS;
extern const char* windDirection;

void initWindSensors();
void updateWindSensors();

#endif