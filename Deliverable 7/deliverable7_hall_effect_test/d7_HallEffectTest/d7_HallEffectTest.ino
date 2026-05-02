#include <LiquidCrystal.h>


// LCD Screen
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


// Pins
const int buttonPin = 9;
const int buzzerPin = 8;


// Int. Variables
int tipCount = 0;
float rainTotal = 0;
float lastRainTotal = -1.0; // LCD displays 0mm rainfall


// Calibration
const float mmPerTip = 5.50; // (mm) - need to change after solidworks model is made.
const float floodThreshold = 20.00; // (mm)- I need to do more research on this to confirm


// Timing
unsigned long startTime;
const unsigned long dayLength = 86400000; // Testing: 24hrs. 


// Debounce
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 500; //changed from 200 for new buttons since more sensitive


bool floodTriggered = false;


void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);


  lcd.begin(16, 2);
  lcd.print("Rain (24hr mm)");
 
  startTime = millis();
}


void loop() {
  // BUTTON READ
  if (digitalRead(buttonPin) == LOW) {
    if (millis() - lastPressTime > debounceDelay) {
      tipCount++;
      rainTotal = tipCount * mmPerTip;
      lastPressTime = millis();
    }
  }


  // LCD UPDATE
  if (rainTotal != lastRainTotal) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(rainTotal, 2);
    lcd.print(" mm");
    lastRainTotal = rainTotal;
  }


  //FLOOD ALERT
  if (rainTotal >= floodThreshold && !floodTriggered) {
    floodTriggered = true;
    for (int i = 0; i < 3; i++) { // Buzzes three times. Turns off
      tone(buzzerPin, 1000);
      delay(300);
      noTone(buzzerPin);
      delay(300);
    }
  }


  // 24-HOUR RESET
  if (millis() - startTime >= dayLength) {
    tipCount = 0;
    rainTotal = 0;
    lastRainTotal = -1.0; // Forces the LCD to refresh to 0.00
    floodTriggered = false;
    startTime = millis();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Rain (24hr mm)");
  }
}
