#include <Arduino.h>

//define variable names for driver pins of motor 1 (right)
#define EN1 23
#define INA_1 4
#define INB_1 5
#define encSpeedright
//define variable names for driver pins of motor 2 (left)
#define EN2 24
#define INA_2 6
#define INB_2 7
#define encSpeedleft

// function declrarions
void portFix();
void rightmotor(float speed);
void leftmotor(float speed);
float line();
void calibrate();

//Sensor calibration data store arrays
int sensMax[8] = {0,0,0,0,0,0,0,0};
int sensMin[8] = {0,0,0,0,0,0,0,0};

void setup() {
  Serial.begin(9600);
  portFix();
  calibrate();
}

void loop() {

  // int Kp = 4;
  // int baseSpeed = 60;

  float error = line();
  Serial.println(error);

  // float p = error*Kp;

  // float pid = Kp*p;

  // rightmotor(baseSpeed - pid);
  // leftmotor(baseSpeed + pid);

}

// Initializing the I/O ports
void portFix() {

  // Initializing the Inputs of the line following sensor panel
  for (int i = A0; i <= A7; ++i) {
    pinMode(i, INPUT);
  }

  //Initializing the Outputs of Motor 1
  pinMode(EN1,OUTPUT);
  pinMode(INA_1,OUTPUT);
  pinMode(INB_1,OUTPUT);

  //Initializing the Outputs of Motor 2
  pinMode(EN2,OUTPUT);
  pinMode(INA_2,OUTPUT);
  pinMode(INB_2,OUTPUT);
}

// Right motor working 
void rightmotor(float speed){
  int err_margin = 5;
  digitalWrite(EN1,HIGH);
  if(speed>0){
    //Forward rotation
    digitalWrite(INB_1,LOW);
    speed = speed;
  }
  else if(speed<0){
    //Backward rotation
    digitalWrite(INB_1,HIGH);
    speed = -speed;
  }
  //Setting speed
  analogWrite(INA_1,speed);
  
}

// Left motor working 
void leftmotor(float speed){
  digitalWrite(EN2,HIGH);
  if(speed>0){
    //Forward rotation
    digitalWrite(INB_2,HIGH);
    speed = speed;
  }
  else if(speed<0){
    //Backward rotation
    digitalWrite(INB_2,LOW);
    speed = -speed;
  }
  //Setting speed
  analogWrite(INA_2,speed);
  
}

float line(){
  int sensVals[8]; // List of sensory data
  int k = 0;
  int weighted_total = 0;
  int total = 0;

  for (int j = A0; j <= A7; ++j) {
    sensVals[k] = analogRead(j);
    k++;
  }

  for (int k=0; k<=7; k++){
    sensVals[k] = map(sensVals[k],sensMin[k],sensMax[k],0,1);
    weighted_total += sensVals[k] * k;
    total += sensVals[k];
  }

  if (total == 0){
    total = 1;
  }

  return weighted_total/total - 3.5;
}

void calibrate(){
  int l = 0;

  for (int l=0; l<=99; l++)
    for (int j = A0; j <= A7; ++j) {
      if (sensMax[l] < analogRead(j)){
        sensMax[l] = analogRead(j);
      }
      if (sensMin[l] > analogRead(j)){
        sensMin[l] = analogRead(j);
      }
      l++;
    }
    delay(50);

}