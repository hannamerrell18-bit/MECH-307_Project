#include <Wire.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>

#define TCAADDR 0x70

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
  Serial.begin(9600);
 
  tcaselect(2);
  if (!display.begin(SSD1309_SWITCHCAPVCC, SCREEN_ADDRESSS)) {
    Serial.println(F("SSD1309 allocation failed"));
    for (;;); // basically an infinite loop, functions same as a while(true) loop
  }

  display.clearDisplay();

  display.setTextSize(1);         // 6x8 pixels per character
  display.setTextColor(SSD1309_PIXEL_ON);       // turn pixels on
  display.setCursor(0, 0);
  display.println(F("Hello world"));
  display.println();
  display.setTextSize(2);         // 12x16 pixels per character
  display.println(F("DIYables"));
  display.setTextSize(1);
  display.println();
  display.println(F("SSD1309 OLED 128x64"));
  display.display();              // push buffer to screen
}

void loop() {
  // put your main code here, to run repeatedly:

}
