#include "display_functions.h"
#include "globals.h"
#include "mux_functions.h"

void writeWeatherStationDisplay(float tempF, float pressure_hPa, float humidity) {
  tcaselect(2);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1309_PIXEL_ON);

  display.println("Weather");
  display.println();

  display.print("Temp = ");
  display.print(tempF);
  display.println(" *F");
  display.println();

  display.print("Press. = ");
  display.print(pressure_hPa);
  display.println(" hPa");
  display.println();

  display.print("Humid. = ");
  display.print(humidity);
  display.println("%");

  display.display();
}

void writeRainGaugeDisplay(float rainTotal, int tipCount) {
  tcaselect(2);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1309_PIXEL_ON);

  display.println("Rain Gauge");
  display.println();

  display.print("Rain: ");
  display.print(rainTotal, 2);
  display.println(" mm");
  display.println();

  display.print("Tips: ");
  display.println(tipCount);

  display.display();
}

void writeServoDisplay(int servoPosition, int servoState) {
  tcaselect(2);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1309_PIXEL_ON);

  display.println("Solar Tracker");
  display.println();

  display.print("Angle: ");
  display.println(servoPosition);
  display.println();

  display.print("Mode: ");

  if (servoState == 0) {
    display.println("East -> West");
  }
  else if (servoState == 1) {
    display.println("West -> East");
  }
  else if (servoState == 2) {
    display.println("Waiting");
  }

  display.display();
}

void writeStationWelcome() {
  tcaselect(2);
  display.clearDisplay();
  display.setCursor(15, 10);
  display.setTextSize(2);
  display.setTextColor(SSD1309_PIXEL_ON);
  display.print("Welcome!");
  display.display();
}