//Creation of global objects

#include "globals.h"

Adafruit_BME280 bme;
DIYables_OLED_SSD1309 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);