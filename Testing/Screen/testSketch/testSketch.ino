#include <Wire.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

DIYables_OLED_SSD1309 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("Starting SSD1309 OLED test...");

  // Try SWITCHCAPVCC first
  if (!display.begin(SSD1309_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1309 allocation failed or display not found.");
    while (true);
  }

  Serial.println("Display initialized!");

  display.clearDisplay();

  // Basic text test
  display.setTextSize(1);
  display.setTextColor(SSD1309_WHITE);
  display.setCursor(0, 0);
  display.println("SSD1309 OLED Test");
  display.println("----------------");
  display.println("Hello weather");
  display.println("station!");
  display.display();

  delay(2000);

  // Larger text test
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("HELLO");
  display.println("OLED!");
  display.display();

  delay(2000);

  // Shape test
  display.clearDisplay();

  display.drawRect(0, 0, 128, 64, SSD1309_WHITE);
  display.drawLine(0, 0, 127, 63, SSD1309_WHITE);
  display.drawLine(127, 0, 0, 63, SSD1309_WHITE);

  display.setTextSize(1);
  display.setCursor(35, 28);
  display.println("Shapes!");

  display.display();

  delay(2000);

  // Fill test
  display.clearDisplay();
  display.fillCircle(64, 32, 20, SSD1309_WHITE);
  display.display();

  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Test complete!");
  display.println();
  display.println("If you see this,");
  display.println("your OLED works.");
  display.display();
}

void loop() {
  // Tiny blinking pixel test so you know loop is running
  display.drawPixel(127, 63, SSD1309_WHITE);
  display.display();
  delay(500);

  display.drawPixel(127, 63, SSD1309_BLACK);
  display.display();
  delay(500);
}
