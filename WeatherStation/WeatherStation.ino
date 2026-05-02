#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>

#include "globals.h"
#include "mux_functions.h"
#include "display_functions.h"

#define HALL_SENSOR_PIN 7
#define SCREEN_BUTTON_PIN 6

int currentScreen = 0;
const int totalScreens = 2;

int lastButtonReading = HIGH;
int buttonState = HIGH;
const unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

unsigned long lastBMEUpdate = 0;
const unsigned long bmeInterval = 5000;  // 5000 ms = 5 seconds

float tempF = 0.0;
float pressure_hPa = 0.0;
float humidity = 0.0;


void setup() {

  //button define
  //pinMode(buttonPin, INPUT_PULLUP); //button to GND

  Serial.begin(115200);
  Wire.begin();

  //rain gauge setup
  pinMode(HALL_SENSOR_PIN, INPUT);
  pinMode(SCREEN_BUTTON_PIN, INPUT_PULLUP);

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
  if (millis() - lastBMEUpdate >= bmeInterval) {
    lastBMEUpdate = millis();

    tcaselect(3);
    float tempC = bme.readTemperature();
    float tempF = tempC * (9.0 / 5.0) + 32.0;
    float pressure_hPa = bme.readPressure() / 100.0F;
    float pressure_inHg = pressure_hPa * 0.02953;
    float humidity = bme.readHumidity();

    Serial.println("BME280 updated");
    Serial.print("Temp: ");
    Serial.print(tempF);
    Serial.println(" F");

    Serial.print("Press.: ");
    Serial.print(pressure_hPa);
    Serial.println(" hPa");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    Serial.println();
  }

    // Read Hall sensor
    int hallState = digitalRead(HALL_SENSOR_PIN);

    // Read button
    int reading = digitalRead(SCREEN_BUTTON_PIN);

    if (reading != lastButtonReading) {
      lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
        buttonState = reading;

        // Only change screen on button press
        if (buttonState == LOW) {
          currentScreen = (currentScreen + 1) % totalScreens;
        }
      }
    }

  lastButtonReading = reading;

    // Draw current screen
      if (currentScreen == 0) {
        writeWeatherStationDisplay(tempF, pressure_hPa, humidity);
      }
      else if (currentScreen == 1) {
        writeHallSensorDisplay(hallState);
      }



// // Handle button press
//   if (digitalRead(buttonPin) == LOW) { // Button pressed
//     if (currentMillis - lastButtonPress > debounceDelay) {
//       lastButtonPress = currentMillis;

//       // Switch to manual mode and go to next message
//       autoMode = false;
//       currentMessage = (currentMessage + 1) % totalMessages;
//       displayMessage(currentMessage);
//     }
//   }

    delay(50);
}