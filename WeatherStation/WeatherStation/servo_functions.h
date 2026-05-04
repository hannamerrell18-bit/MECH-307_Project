#ifndef SERVO_FUNCTIONS_H
#define SERVO_FUNCTIONS_H

enum ServoState {
  SERVO_SWEEPING,
  SERVO_RETURNING,
  SERVO_WAITING
};

extern int servoPosition;
extern ServoState servoState;

void initServoTracker();
void updateServoTracker();

#endif