#ifndef GYRO_READINGS
#define GYRO_READINGS
#include <Wire.h>
#include <Arduino.h>
#include "gyro_readings.h"

void TCA9548A_g(uint8_t bus);
void kalman_1d(float KalmanState, float KalmanUncertainty, float KalmanInput, float KalmanMeasurement);
void gyro_signals(void);
void setup_gyro();
float get_angle();

#endif