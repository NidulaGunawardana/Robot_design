#include "Motordriver.h"
#include <Arduino.h>

class Motordriver
{
private:
    int pos = 0;
    int prev_pos = 0;
    float moving_avg;
    float speedSet;
    int encoderPin;

public:
    void setPin(int pin)
    {
        encoderPin = pin;
    }
    void readEncoder()
    {
        int b = digitalRead(encoderPin);
        if (b > 0)
        {
            pos++;
        }
        else
        {
            pos--;
        }
    }

    float getSpeed()
    {
        int moving_avg = 0;
        for (int i = 0; i < 5; i++)
        {
            moving_avg += (pos - prev_pos);
            prev_pos = pos;
            delay(10);
        }
        moving_avg = map(moving_avg, 0, 100, 0, 255);
        return moving_avg;
    }
    void setSpeed(int speedToSet, int motor, int dir, int side)
    {
        int speed = speedSet;
        float now_speed = getSpeed();
        float error = speed - now_speed;
        analogWrite(motor, speed + error);
        digitalWrite(dir, side);

        Serial.println((String)now_speed + " " + (String)speed + " " + (String)error);
    }
};
