//Declaration of shared constants and global objects
#ifndef GLOBALS_H
#define GLOBALS_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>

#define TCAADDR 0x70

#define SEALEVELPRESSURE_HPA (1013.25)
#define BME_ADDRESS 0x77

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESSS 0x3C

#define SCREEN_BUTTON_PIN 8
#define RAIN_SENSOR_PIN 6
#define BUZZER_PIN 10


extern Adafruit_BME280 bme;
extern DIYables_OLED_SSD1309 display;

#endif