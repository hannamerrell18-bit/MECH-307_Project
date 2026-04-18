#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>

#define TCAADDR 0x70

#define SEALEVELPRESSURE_HPA (1013.25)
#define BME_ADDRESS 0x77
Adafruit_BME280 bme; //create BME 280 sensor object

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
 Wire.begin(); //fail safe for beginning I2C comm; most libraries have it, but good habit to use in code
 
 tcaselect(2);
 if (!display.begin(SSD1309_SWITCHCAPVCC, SCREEN_ADDRESSS)) {
  Serial.println(F("SSD1309 allocation failed"));
  while(1); // basically an infinite loop, functions same as a while(true) loop
 }

 tcaselect(3);
 if(!bme.begin(BME_ADDRESS)) {   // default I2C address is 0x76
  Serial.println("Could not find valid BME280 sensor, check wiring!");
  while(1);
 }

 display.clearDisplay();
 display.display();
}

void loop() {
  // read sensor on channel 3 (0x77)
  tcaselect(3); 
  Serial.println("Reading BME 280 on channel 3");

  float tempC = bme.readTemperature();
  float tempF = tempC * (9.0 / 5.0) + 32.0; //convert celsius to fahrenheit
  float pressure_hPa = bme.readPressure() / 100.0F; 
  float pressure_inHg = pressure_hPa * 0.02953; //convert hPa to inHg (inches of Mercury) 
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

  //Update display on channel 2
  tcaselect(2);
  Serial.println("Writing OLED on channel 2");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);         // 6x8 pixels per character
  display.setTextColor(SSD1309_PIXEL_ON);       // turn pixels on

  display.print(F("Temp. = "));
  display.print(tempF);
  display.println(F(" *F"));
  display.println();

  display.print(F("Press. = "));
  display.print(pressure_hPa);
  display.println(F(" hPa"));
  display.setCursor(54, 32);
  display.print(pressure_inHg);
  display.println(F(" inHg"));
  display.println();

  display.print(F("Humid. = "));
  display.print(humidity);
  display.println(F("%"));

  display.display();              // push buffer to screen

  delay(5000);
}
