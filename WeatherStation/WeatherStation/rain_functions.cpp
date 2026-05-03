#include <Arduino.h>
#include "rain_functions.h"

#define RAIN_SENSOR_PIN 7
#define BUZZER_PIN 8

int tipCount = 0;
float rainTotal = 0.0;
bool lastRainSensorState = HIGH;

const float inPerTip = 0.1;
const float inThreshold = 1;
int lastBuzzThreshold = 0;

unsigned long lastRainTipTime = 0;
const unsigned long rainDebounceDelay = 200;

unsigned long rainStartTime = 0;
const unsigned long rainDayLength = 86400000;

// Non-blocking buzzer
bool buzzerActive = false;
unsigned long buzzerStartTime = 0;
const unsigned long buzzerDuration = 500;

void initRainGauge() {
  pinMode(RAIN_SENSOR_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  rainStartTime = millis();
}

void updateRainGauge() {
  int currentRainState = digitalRead(RAIN_SENSOR_PIN);

  if (lastRainSensorState == HIGH && currentRainState == LOW) {
    if (millis() - lastRainTipTime > rainDebounceDelay) {
      tipCount++;
      rainTotal = tipCount * inPerTip;
      lastRainTipTime = millis();

      int currentThreshold = (int)(rainTotal / inThreshold);

      if (currentThreshold > lastBuzzThreshold) {
        tone(BUZZER_PIN, 1000);
        buzzerActive = true;
        buzzerStartTime = millis();
        lastBuzzThreshold = currentThreshold;
      }
    }
  }

  lastRainSensorState = currentRainState;

  if (buzzerActive && (millis() - buzzerStartTime >= buzzerDuration)) {
    noTone(BUZZER_PIN);
    buzzerActive = false;
  }

  if (millis() - rainStartTime >= rainDayLength) {
    tipCount = 0;
    rainTotal = 0.0;
    lastBuzzThreshold = 0;
    rainStartTime = millis();
  }
}