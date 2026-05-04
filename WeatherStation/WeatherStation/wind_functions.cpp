#include <Arduino.h>
#include "wind_functions.h"

// ---------------- WIND SPEED ----------------
#define ANEMOMETER_PIN 18

volatile int anemometerPulseCount = 0;
unsigned long lastWindSpeedTime = 0;

const float radius = 0.12;
const float k = 0.9;

float windSpeedMPH = 0.0;
float windSpeedMS = 0.0;

// ---------------- WIND DIRECTION ----------------
#define WINDVANE_CLK 2
#define WINDVANE_DT  3

volatile int encoderPos = 0;
volatile int lastState = 0;

const int totalSteps = 76;
const int numDirections = 8;
const char* directions[numDirections] = {"N","NE","E","SE","S","SW","W","NW"};

const char* windDirection = "N";

// ---------------- INTERRUPTS ----------------
void countAnemometerPulse() {
  anemometerPulseCount++;
}

void updateWindEncoder() {
  int clkState = digitalRead(WINDVANE_CLK);
  int dtState = digitalRead(WINDVANE_DT);

  int state = (clkState << 1) | dtState;
  int delta = 0;

  switch ((lastState << 2) | state) {
    case 0b0001:
    case 0b0111:
    case 0b1110:
    case 0b1000:
      delta = 1;
      break;

    case 0b0010:
    case 0b0100:
    case 0b1101:
    case 0b1011:
      delta = -1;
      break;
  }

  encoderPos += delta;
  lastState = state;
}

void initWindSensors() {
  pinMode(ANEMOMETER_PIN, INPUT_PULLUP);
  pinMode(WINDVANE_CLK, INPUT_PULLUP);
  pinMode(WINDVANE_DT, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ANEMOMETER_PIN), countAnemometerPulse, FALLING);
  attachInterrupt(digitalPinToInterrupt(WINDVANE_CLK), updateWindEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(WINDVANE_DT), updateWindEncoder, CHANGE);

  lastWindSpeedTime = millis();

  int clkState = digitalRead(WINDVANE_CLK);
  int dtState = digitalRead(WINDVANE_DT);
  lastState = (clkState << 1) | dtState;
}

void updateWindSensors() {
  unsigned long currentTime = millis();

  if (currentTime - lastWindSpeedTime >= 1000) {
    noInterrupts();
    int count = anemometerPulseCount;
    anemometerPulseCount = 0;
    interrupts();

    float rps = count / 1.0;
    windSpeedMS = 2 * PI * radius * rps * k;
    windSpeedMPH = windSpeedMS * 2.237;

    lastWindSpeedTime = currentTime;
  }

  noInterrupts();
  int step = encoderPos;
  interrupts();

  step = (step % totalSteps + totalSteps) % totalSteps;
  int dirIndex = (step * numDirections) / totalSteps;
  windDirection = directions[dirIndex];
}