#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 if(!bme.begin(0x77)) {   // default I2C address is 0x76
  Serial.println("Could not find valid BME280 sensor, check wiring!");
  while(1);
 }
 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Temperature = ");
  Serial.print((bme.readTemperature() * (9/5)) + 32);      // Convert Celsius to Fahrenheit
  Serial.println(" *F");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);      // Convert Pa to hPa
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");

  delay(1000);
}
