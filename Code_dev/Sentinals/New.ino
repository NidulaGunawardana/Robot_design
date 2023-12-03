#include <Arduino.h>
// #include "Motordriver.h"

// define variable names for driver pins of motor 1 (right)
#define EN1 23
#define INA_1 4
#define INB_1 5

// define variable names for driver pins of motor 2 (left)
#define EN2 24
#define INA_2 6
#define INB_2 7

int pos1 = 0;
int pos2 = 0;
int prev_pos1 = 0;
float moving_avg1;
int prev_pos2 = 0;
float moving_avg2;
float speedSet1;

// function declrarions

// Sensor calibration data store arrays
int sensMax[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int sensMin[8] = {100, 100, 100, 100, 100, 100, 100, 100};

// Motordriver motor1 = Motordriver();

void readEncoder1()
{
  int b = digitalRead(ENCB_1);
  if (b > 0)
  {
    pos1++;
  }
  else
  {
    pos1--;
  }
}

void readEncoder2()
{
  int b = digitalRead(ENCB_2);
  if (b > 0)
  {
    pos2++;
  }
  else
  {
    pos2--;
  }
}

float getSpeed1()
{
  int moving_avg1 = 0;
  for (int i = 0; i < 5; i++)
  {
    moving_avg1 += (pos1 - prev_pos1);
    prev_pos1 = pos1;
    delay(10);
  }
  moving_avg1 = map(moving_avg1, 0, 100, 0, 255);
  return moving_avg1;
}

float getSpeed2()
{
  int moving_avg2 = 0;
  for (int i = 0; i < 5; i++)
  {
    moving_avg2 += (pos2 - prev_pos2);
    prev_pos2 = pos2;
    delay(10);
  }
  moving_avg2 = map(moving_avg2, 0, 100, 0, 255);
  return moving_avg2;
}

void setSpeed1(int speedToSet, int motor, int dir, int side)
{
  int speed = speedToSet;
  float now_speed = getSpeed1();
  float error = speed - now_speed;
  digitalWrite(EN1,HIGH);
  analogWrite(motor, speed + error);
  digitalWrite(dir, side);
  

  Serial.println((String)now_speed + " " + (String)speed + " " + (String)error);
}

void setSpeed2(int speedToSet, int motor, int dir, int side)
{
  int speed = speedToSet;
  float now_speed = getSpeed2();
  float error = speed - now_speed;
  digitalWrite(EN2,HIGH);
  analogWrite(motor, speed + error);
  digitalWrite(dir, side);
  

  Serial.println((String)now_speed + " " + (String)speed + " " + (String)error);
}

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
  // motor1.setPin(ENCA_1);
  attachInterrupt(digitalPinToInterrupt(ENCA_1), readEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA_2), readEncoder2, RISING);
}

void loop()
{

  int speedRRead = map(analogRead(A8), 0, 1023, 0, 100);

  setSpeed1(speedRRead, INA_1, INB_1, HIGH);
  setSpeed2(speedRRead, INA_2, INB_2, HIGH);
  // Serial.println(speedRRead);
}