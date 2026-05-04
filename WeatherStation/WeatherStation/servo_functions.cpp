#include <Arduino.h>
#include <Servo.h>
#include "servo_functions.h"

#define SERVO_PIN 9
#define SERVO_MIN_ANGLE 20
#define SERVO_MAX_ANGLE 160

Servo solarServo;

int servoPosition = SERVO_MIN_ANGLE;

// Demo timing
unsigned long sweepTime = 30000;
unsigned long waitTime = 30000;
int steps = SERVO_MAX_ANGLE - SERVO_MIN_ANGLE;
unsigned long stepDelayTime = sweepTime / steps;
unsigned long returnDelay = 15;

ServoState servoState = SERVO_SWEEPING;
unsigned long lastServoUpdate = 0;
unsigned long waitStartTime = 0;

void initServoTracker() {
  solarServo.attach(SERVO_PIN);
  solarServo.write(180 - servoPosition);
}

void updateServoTracker() {
  unsigned long currentMillis = millis();

  if (servoState == SERVO_SWEEPING) {
    if (currentMillis - lastServoUpdate >= stepDelayTime) {
      lastServoUpdate = currentMillis;

      if (servoPosition < SERVO_MAX_ANGLE) {
        servoPosition++;
        solarServo.write(180 - servoPosition);
      } else {
        servoState = SERVO_RETURNING;
      }
    }
  }
  else if (servoState == SERVO_RETURNING) {
    if (currentMillis - lastServoUpdate >= returnDelay) {
      lastServoUpdate = currentMillis;

      if (servoPosition > SERVO_MIN_ANGLE) {
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