#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Messages to display
const char* messages[] = {
  "Temp: ",
  "Humidity: ",
  "Pressure: ",
  "Wind speed: ",
  "Panel Pos: ",
  "Rain: "
};
const int totalMessages = sizeof(messages) / sizeof(messages[0]);

// Timing variables
unsigned long previousMillis = 0;
const unsigned long autoInterval = 5000; // Auto-cycle every 3 seconds

// Button settings
const int buttonPin = 21;
bool autoMode = true; // Start in auto mode
int currentMessage = 0;

// Debounce variables
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 500; // ms

void setup() {
  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT_PULLUP); // Button to GND
  lcd.print("Hi! Hold plz...");
}

void loop() {
  unsigned long currentMillis = millis();

  // Handle button press
  if (digitalRead(buttonPin) == LOW) { // Button pressed
    if (currentMillis - lastButtonPress > debounceDelay) {
      lastButtonPress = currentMillis;

      // Switch to manual mode and go to next message
      autoMode = false;
      currentMessage = (currentMessage + 1) % totalMessages;
      displayMessage(currentMessage);
    }
  }

  // Auto mode cycling
  if (autoMode && (currentMillis - previousMillis >= autoInterval)) {
    previousMillis = currentMillis;
    currentMessage = (currentMessage + 1) % totalMessages;
    displayMessage(currentMessage);
  }
}

// Function to display a message on LCD
void displayMessage(int index) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Current weather:");
  lcd.setCursor(0, 1);
  lcd.print(messages[index]);
}

