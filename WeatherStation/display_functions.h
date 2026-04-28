#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H

void writeWeatherStationDisplay(float tempF, float pressure_hPa, float humidity);
void writeStationWelcome();

const int totalMessages = sizeof(messages) / sizeof(messages[0]);

// Button settings
const int buttonPin = 9;
bool autoMode = true; // Start in auto mode
int currentMessage = 0;

// Debounce variables
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 500; // ms

// Timing variables
unsigned long previousMillis = 0;
const unsigned long autoInterval = 5000; // Auto-cycle every 3 seconds


#endif