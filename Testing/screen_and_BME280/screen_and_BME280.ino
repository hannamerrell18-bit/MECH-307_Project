#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>

#define TCAADDR 0x70

#define SEALEVELPRESSURE_HPA (1013.25)
#define BME_ADDRESS 0x77
Adafruit_BME280 bme;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESSS 0x3c     // initialize the SSD1309 - use the address 0x3c (default for most modules)
DIYables_OLED_SSD1309 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // create display object (pass -1 when no reset pin detected)

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 
 tcaselect(3);
 if(!bme.begin(BME_ADDRESS)) {   // default I2C address is 0x76
  Serial.println("Could not find valid BME280 sensor, check wiring!");
  while(1);
 }
 
  tcaselect(2);
if (!display.begin(SSD1309_SWITCHCAPVCC, SCREEN_ADDRESSS)) {
  Serial.println(F("SSD1309 allocation failed"));
  while(1); // basically an infinite loop, functions same as a while(true) loop
}

}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);         // 6x8 pixels per character
  display.setTextColor(SSD1309_PIXEL_ON);       // turn pixels on

  display.print(F("Temp = "));
  display.print((bme.readTemperature() * (9/5))+ 32);  // Convert Celsius to Fahrenheit
  
  Serial.println(bme.readTemperature() * (9/5) + 32);    // Convert Celsius to Fahrenheit
  
  display.println(" *F");
  display.println();
  display.print(F("Press. = "));
  display.print(bme.readPressure() / 100.0F);      // Convert Pa to hPa
  display.println(" hPa");
  display.println();
  display.print(F("Humid. = "));
  display.print((bme.readHumidity()));
  display.println("%");
  display.display();              // push buffer to screen

  delay(5000);
}
