#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>

#include "globals.h"
#include "mux_functions.h"
#include "display_functions.h"

void setup() {
  Serial.begin(115200);
  Wire.begin();

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

  tcaselect(2);
  display.clearDisplay();
  display.display();
  delay(3000);

  writeStationWelcome();
  delay(2000);
}

void loop() {
  tcaselect(3);
  Serial.println("Reading BME 280 on channel 3");

  float tempC = bme.readTemperature();
  float tempF = tempC * (9.0 / 5.0) + 32.0;
  float pressure_hPa = bme.readPressure() / 100.0F;
  float pressure_inHg = pressure_hPa * 0.02953;
  float humidity = bme.readHumidity();

  Serial.print("Temp: ");
  Serial.print(tempF);
  Serial.println(" F");

  Serial.print("Press.: ");
  Serial.print(pressure_hPa);
  Serial.print(" hPa / ");
  Serial.print(pressure_inHg);
  Serial.println(" inHg");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.println("Writing OLED on channel 2");
  Serial.println();

  writeWeatherStationDisplay(tempF, pressure_hPa, humidity);

  delay(5000);
}