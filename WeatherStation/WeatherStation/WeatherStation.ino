#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>

#include "globals.h"
#include "mux_functions.h"
#include "display_functions.h"
#include "rain_functions.h"
#include "servo_functions.h"
#include "wind_functions.h"

#define SCREEN_BUTTON_PIN 6

int currentScreen = 0;
const int totalScreens = 4;

int lastButtonReading = HIGH;
int buttonState = HIGH;
const unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

unsigned long lastBMEUpdate = 0;
const unsigned long bmeInterval = 5000;

float tempF = 0.0;
float pressure_hPa = 0.0;
float humidity = 0.0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  randomSeed(analogRead(A0));

  pinMode(SCREEN_BUTTON_PIN, INPUT_PULLUP);

  initRainGauge();
  initServoTracker();
  initWindSensors();

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
  updateServoTracker();
  updateRainGauge();
  updateWindSensors();

  if (millis() - lastBMEUpdate >= bmeInterval) {
    lastBMEUpdate = millis();

    tcaselect(3);
    float tempC = bme.readTemperature();
    tempF = tempC * (9.0 / 5.0) + 32.0;
    pressure_hPa = bme.readPressure() / 100.0F;
    humidity = bme.readHumidity();
  }

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
    writeRainGaugeDisplay(rainTotal, tipCount);
  }
  else if (currentScreen == 2) {
    writeServoDisplay(servoPosition, servoState);
  }
  else if (currentScreen == 3) {
    writeWindDisplay(windSpeedMPH, windDirection);
  }

  delay(50);
}