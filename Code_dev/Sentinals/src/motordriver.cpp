#include "motordriver.h"

int INA;
int INB;
int EN;
int ENCA;
int ENCB;

int pos = 0;
int prev_pos = 0;
float moving_avg;
float speedSet;

void pinSetup(int INA_1, int INB_1, int EN_1, int ENCA_1, int ENCB_1)
{
    INA = INA_1;
    INB = INB_1;
    EN = EN_1;
    ENCA = ENCA_1;
    ENCB = ENCB_1;

    pinMode(INA, OUTPUT);
    pinMode(INB, OUTPUT);
    pinMode(EN, OUTPUT);
    pinMode(ENCA, INPUT);
    pinMode(ENCB, INPUT);
    // pinMode(A8,INPUT);

    digitalWrite(EN, HIGH);
    digitalWrite(INB, HIGH);

    attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void readEncoder()
{
    int b = digitalRead(ENCB);
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
    moving_avg = 0;
    for (int i = 0; i < 5; i++)
    {
        moving_avg += (pos - prev_pos);
        prev_pos = pos;
        delay(10);
    }
    moving_avg = map(moving_avg, 0, 100, 0, 255);
    return moving_avg;
}

void setSpeed(int speedToSet,int motor,int dir,int side)
{
    int speed = speedSet;
    float now_speed = getSpeed();
    float error = speed - now_speed;
    analogWrite(motor, speed + error);
    digitalWrite(dir,side);

    Serial.println((String)now_speed + " " + (String)speed);
}