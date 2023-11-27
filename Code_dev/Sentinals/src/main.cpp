#include <Arduino.h>

//define variable names for driver pins of motor 1
#define EN1 23
#define INA_1 4
#define INB_1 5

//define variable names for driver pins of motor 2
#define EN2 24
#define INA_2 6
#define INB_2 7

// function declrarions
void portFix();
void rightmotor(float speed);
void leftmotor(float speed);
float line();

void setup() {
  Serial.begin(9600);
  portFix();
}

void loop() {
  int Kp = 4;
  int baseSpeed = 60;

  float error = line();

  float p = error*Kp;

  float pid = Kp*p;

  rightmotor(baseSpeed - pid);
  leftmotor(baseSpeed + pid);

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
  digitalWrite(EN1,HIGH);
  if(speed>0){
    //Forward rotation
    digitalWrite(INB_1,LOW);
    //Setting speed
    analogWrite(INA_1,speed);
  }
  else if(speed<0){
    //Backward rotation
    digitalWrite(INB_1,HIGH);
    //Setting speed
    analogWrite(INA_1,-speed);
  }
  
}

// Left motor working 
void leftmotor(float speed){
  digitalWrite(EN2,HIGH);
  if(speed>0){
    //Forward rotation
    digitalWrite(INB_2,HIGH);
    //Setting speed
    analogWrite(INA_2,speed);
  }
  else if(speed<0){
    //Backward rotation
    digitalWrite(INB_2,LOW);
    //Setting speed
    analogWrite(INA_2,-speed);
  }
  
}

float line(){
  int threshold = 50; //White-black analog threshold value
  int sensVals[8]; // List of sensory data
  int k = 0;
  int total = 0;
  int elNum = 0;

  for (int j = A0; j <= A7; ++j) {
    sensVals[k] = (threshold < analogRead(j))*k;
    k++;
  }

  for (int k=0; k<=7; k++){
    total += sensVals[k];
    elNum += sensVals[k] > 0;
  }

  if (elNum == 0){
    elNum = 1;
  }

  return total/elNum - 3.5;
}

