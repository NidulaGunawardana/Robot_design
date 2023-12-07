#ifndef COLOR_SENSOR
#define COLOR_SENSOR

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "color_sensor.h"

void TCA9548A_c(uint8_t bus);
void setup_color_sensor();
void reaad_color();

#endif