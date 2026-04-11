#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESSS 0x72     // initialize the SSD1309 - use the address 0x3c (default for most modules)
DIYables_OLED_SSD1309 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // create display object (pass -1 when no reset pin detected)

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 if(!bme.begin(0x73)) {   // default I2C address is 0x76
  Serial.println("Could not find valid BME280 sensor, check wiring!");
  while(1);
 }
 
  if (!display.begin(SSD1309_SWITCHCAPVCC, SCREEN_ADDRESSS)) {
    Serial.println(F("SSD1309 allocation failed"));
    for (;;); // basically an infinite loop, functions same as a while(true) loop
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);         // 6x8 pixels per character
  display.setTextColor(SSD1309_PIXEL_ON);       // turn pixels on

}

void loop() {
  // put your main code here, to run repeatedly:
  display.print(F("Temperature = "));
  display.print((bme.readTemperature() * (9/5)) + 32);      // Convert Celsius to Fahrenheit
  display.println(" *F");
  display.println();
  display.print(F("Pressure = "));
  display.print((bme.readPressure() / 100.0F));      // Convert Pa to hPa
  display.println(" hPa");
  display.println();
  display.print(F("Humidity = "));
  display.print((bme.readHumidity()));
  display.println("%");
  display.display();              // push buffer to screen

  delay(5000);
}
