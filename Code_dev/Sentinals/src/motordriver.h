#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
#include <Arduino.h>
void pinSetup(int INA_1, int INB_1, int EN_1, int ENCA_1, int ENCB_1);
void readEncoder();
float getSpeed();
void setSpeed(int speedToSet,int motor,int dir,int side);
#endif
