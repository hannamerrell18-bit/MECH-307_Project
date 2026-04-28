#include "display_functions.h"
#include "globals.h"
#include "mux_functions.h"

void writeWeatherStationDisplay(float tempF, float pressure_hPa, float humidity) {
  tcaselect(2);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1309_PIXEL_ON);

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

void writeStationWelcome() {
  tcaselect(2);
  display.clearDisplay();
  display.setCursor(15, 10);
  display.setTextSize(2);
  display.setTextColor(SSD1309_PIXEL_ON);
  display.print("Welcome!");
  display.display();
}