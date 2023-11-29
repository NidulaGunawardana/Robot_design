#include <Arduino.h>

#define ENCA 18 // Yellow
#define ENCB 19 // White
#define EN1 24
#define INA_1 6
#define INB_1 7

int pos = 0;
int prev_pos = 0;
float moving_avg;
float speedSet;

float getSpeed();

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(INA_1,OUTPUT);
pinMode(INB_1,OUTPUT);
pinMode(EN1,OUTPUT);
pinMode(ENCA,INPUT);
pinMode(ENCB,INPUT);
pinMode(A8,INPUT);

digitalWrite(EN1,HIGH);
digitalWrite(INB_1,HIGH);

attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int speed = 60;
  float now_speed = getSpeed();
  float error = speed - now_speed;

  
  analogWrite(INA_1,speed + error);

  Serial.println((String)now_speed + " " + (String)speed);
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b>0){
    pos++;
  }
  else{
    pos--;
  }
}

float getSpeed(){
  moving_avg = 0;
  for (int i=0;i<5;i++){
    moving_avg += (pos - prev_pos);
    prev_pos = pos;
    delay(10);
  }
  moving_avg = map(moving_avg,0,100,0,255);
  return moving_avg;
}