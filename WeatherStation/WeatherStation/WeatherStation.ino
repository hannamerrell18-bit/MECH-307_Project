#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>
#include <Servo.h>

#include "globals.h"
#include "mux_functions.h"
#include "display_functions.h"


#define HALL_SENSOR_PIN 8
#define SCREEN_BUTTON_PIN 6
#define SERVO_PIN 3

int currentScreen = 0;
const int totalScreens = 3;

int lastButtonReading = HIGH;
int buttonState = HIGH;
const unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

unsigned long lastBMEUpdate = 0;
const unsigned long bmeInterval = 5000;

float tempF = 0.0;
float pressure_hPa = 0.0;
float humidity = 0.0;

// Servo objects and variables
Servo solarServo;
int servoPosition = 0;

// Demo timing
unsigned long sweepTime = 30000;
unsigned long waitTime = 30000;
int steps = 180;
unsigned long stepDelayTime = sweepTime / steps;
unsigned long returnDelay = 15;

enum ServoState {
  SERVO_SWEEPING,
  SERVO_RETURNING,
  SERVO_WAITING
};

ServoState servoState = SERVO_SWEEPING;
unsigned long lastServoUpdate = 0;
unsigned long waitStartTime = 0;

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

void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(HALL_SENSOR_PIN, INPUT);
  pinMode(SCREEN_BUTTON_PIN, INPUT_PULLUP);

  solarServo.attach(SERVO_PIN);
  solarServo.write(servoPosition);

  tcaselect(2);
  if (!display.begin(SSD1309_SWITCHCAPVCC, SCREEN_ADDRESSS)) {
    Serial.println(F("SSD1309 allocation failed"));
    while (1);
  }

  tcaselect(3);
  if (!bme.begin(BME_ADDRESS)) {
    Serial.println("Could not find valid BME280 sensor, check wiring!");
    while (1);
  }

  tcaselect(3);
  float tempC = bme.readTemperature();
  tempF = tempC * (9.0 / 5.0) + 32.0;
  pressure_hPa = bme.readPressure() / 100.0F;
  humidity = bme.readHumidity();

  writeStationWelcome();
  delay(2000);
}

void loop() {
  // Keep servo running in background
  updateServoTracker();

  // Update BME280 occasionally
  if (millis() - lastBMEUpdate >= bmeInterval) {
    lastBMEUpdate = millis();

    tcaselect(3);
    float tempC = bme.readTemperature();
    tempF = tempC * (9.0 / 5.0) + 32.0;
    pressure_hPa = bme.readPressure() / 100.0F;
    humidity = bme.readHumidity();
  }

  int hallState = digitalRead(HALL_SENSOR_PIN);

  int reading = digitalRead(SCREEN_BUTTON_PIN);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        currentScreen = (currentScreen + 1) % totalScreens;
      }
    }
  }

  lastButtonReading = reading;

  if (currentScreen == 0) {
    writeWeatherStationDisplay(tempF, pressure_hPa, humidity);
  }
  else if (currentScreen == 1) {
    writeHallSensorDisplay(hallState);
  }
  else if (currentScreen == 2) {
    writeServoDisplay(servoPosition, servoState);
  }

  delay(50);
}