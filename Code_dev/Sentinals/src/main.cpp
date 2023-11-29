#include <Arduino.h>
#include "Motordriver.h"

// define variable names for driver pins of motor 1 (right)
#define EN1 23
#define INA_1 4
#define INB_1 5
#define ENCA_1 2
#define ENCB_1 3
int encSpeedright;
// define variable names for driver pins of motor 2 (left)
#define EN2 24
#define INA_2 6
#define INB_2 7
#define ENCA_2 18
#define ENCB_2 19
int encSpeedleft;

int pos1 = 0;
int pos2 = 0;
int prev_pos = 0;
float moving_avg;
float speedSet;

// function declrarions

// Sensor calibration data store arrays
int sensMax[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int sensMin[8] = {100, 100, 100, 100, 100, 100, 100, 100};

Motordriver motor1 = Motordriver();

void setup()
{
  Serial.begin(9600);
  pinMode(INA_1, OUTPUT);
  pinMode(INB_1, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(ENCA_1, INPUT);
  pinMode(ENCB_1, INPUT);
  pinMode(INA_2, OUTPUT);
  pinMode(INB_2, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(ENCA_2, INPUT);
  pinMode(ENCB_2, INPUT);
  pinMode(A8, INPUT);
  // Serial.println("Setup");
  // pinSetup(INA_1, INB_1, EN1, ENCA_1, ENCB_1);
  // Serial.println("Setup 1");
  // pinSetup(INA_2, INB_2, EN2, ENCA_2, ENCB_2);
  // Serial.println("Setup 2");
  motor1.setPin(ENCA_1);
  attachInterrupt(digitalPinToInterrupt(ENCA_1), motor1.readEncoder, RISING);
  // attachInterrupt(digitalPinToInterrupt(ENCA_2), readEncoder2, RISING);
}

void loop()
{

  int speedRRead = map(analogRead(A8), 0, 1024, 0, 90);

  motor1.setSpeed(speedRRead, INA_1, INB_1, HIGH);
  // setSpeed(speedRRead, INA_2, INB_2, HIGH);
  // Serial.println(speedRRead);
}

// void readEncoder1()
// {
//   int b = digitalRead(ENCB);
//   if (b > 0)
//   {
//     pos1++;
//   }
//   else
//   {
//     pos1--;
//   }
// }

// void readEncoder2()
// {
//   int b = digitalRead(ENCB);
//   if (b > 0)
//   {
//     pos2++;
//   }
//   else
//   {
//     pos2--;
//   }
// }

// float getSpeed(int pos)
// {
//    int moving_avg = 0;
//     for (int i = 0; i < 5; i++)
//     {
//         moving_avg += (pos - prev_pos);
//         prev_pos = pos;
//         delay(10);
//     }
//     moving_avg = map(moving_avg, 0, 100, 0, 255);
//     return moving_avg;
// }

// float getSpeed(int pos)
// {
//    int moving_avg = 0;
//     for (int i = 0; i < 5; i++)
//     {
//         moving_avg += (pos - prev_pos);
//         prev_pos = pos;
//         delay(10);
//     }
//     moving_avg = map(moving_avg, 0, 100, 0, 255);
//     return moving_avg;
// }