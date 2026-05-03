#include <Arduino.h>
#include <Servo.h>
#include "servo_functions.h"

#define SERVO_PIN 9

Servo solarServo;

int servoPosition = 0;

// Demo timing
unsigned long sweepTime = 30000;
unsigned long waitTime = 30000;
int steps = 180;
unsigned long stepDelayTime = sweepTime / steps;
unsigned long returnDelay = 15;

ServoState servoState = SERVO_SWEEPING;
unsigned long lastServoUpdate = 0;
unsigned long waitStartTime = 0;

void initServoTracker() {
  solarServo.attach(SERVO_PIN);
  solarServo.write(servoPosition);
}

void updateServoTracker() {
  unsigned long currentMillis = millis();

  if (servoState == SERVO_SWEEPING) {
    if (currentMillis - lastServoUpdate >= stepDelayTime) {
      lastServoUpdate = currentMillis;

      if (servoPosition < 180) {
        servoPosition++;
        solarServo.write(servoPosition);
      } else {
        servoState = SERVO_RETURNING;
      }
    }
  }
  else if (servoState == SERVO_RETURNING) {
    if (currentMillis - lastServoUpdate >= returnDelay) {
      lastServoUpdate = currentMillis;

      if (servoPosition > 0) {
        servoPosition--;
        solarServo.write(servoPosition);
      } else {
        servoState = SERVO_WAITING;
        waitStartTime = currentMillis;
      }
    }
  }
  else if (servoState == SERVO_WAITING) {
    if (currentMillis - waitStartTime >= waitTime) {
      servoState = SERVO_SWEEPING;
      lastServoUpdate = currentMillis;
    }
  }
}