#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H

void writeWeatherStationDisplay(float tempF, float pressure_hPa, float humidity);
void writeStationWelcome();
void writeHallSensorDisplay(int hallState);

// void writeRainGauge();

// const int totalMessages = sizeof(messages) / sizeof(messages[0]);

// // Button settings
// const int buttonPin = 9;
// bool autoMode = true; // Start in auto mode
// int currentMessage = 0;

// // Debounce variables
// unsigned long lastButtonPress = 0;
// const unsigned long debounceDelay = 500; // ms

// // Timing variables
// unsigned long previousMillis_button = 0;
// const unsigned long autoInterval = 5000; // Auto-cycle every 3 seconds

// Messages to display
// const char* messages[] = {
//   BME_280(),
//   Wind(),
//   solarPanelPos(),
//   rainGauge()
// };


#endif