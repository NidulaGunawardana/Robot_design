#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
#include <Arduino.h>
class Motordriver
{
private:
    int pos;
    int prev_pos;
    float moving_avg;
    float speedSet;

public:
    void setPin(int pin);
    void readEncoder();
    float getSpeed();
    void setSpeed(int speedToSet, int motor, int dir, int side);
};

#endif
