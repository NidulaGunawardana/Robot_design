#include <Arduino.h>
#include <motordriver.h>

// define variable names for driver pins of motor 1 (right)
#define EN1 23
#define INA_1 4
#define INB_1 5
int encSpeedright;
// define variable names for driver pins of motor 2 (left)
#define EN2 24
#define INA_2 6
#define INB_2 7
int encSpeedleft;

// function declrarions
void portFix();
void rightmotor(float speed);
void leftmotor(float speed);
float line();
void calibrate();


// Sensor calibration data store arrays
int sensMax[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int sensMin[8] = {100, 100, 100, 100, 100, 100, 100, 100};

void setup()
{
  // portFix();
  // digitalWrite(13,LOW);
  // calibrate();
  // digitalWrite(13,HIGH);
  // delay(2000);
  pinSetup(INA_1, INB_1, EN1, 2, 3);
  pinSetup(INA_2, INB_2, EN2, 18, 19);
}

void loop()
{

  setSpeed(70, INA_1, INB_1, HIGH);
  setSpeed(70, INA_2, INB_2, HIGH);

  // int Kp = 4;
  // int baseSpeed = 50;

  // float error = line();
  // float p = error*Kp;

  // float pid = Kp*p;

  // rightmotor(baseSpeed+50);
  // leftmotor(baseSpeed);
}

// // Initializing the I/O ports
// void portFix() {

//   // Initializing the Inputs of the line following sensor panel
//   for (int i = A0; i <= A7; ++i) {
//     pinMode(i, INPUT);
//   }

//   //Initializing the Outputs of Motor 1 (right)
//   pinMode(EN1,OUTPUT);
//   pinMode(INA_1,OUTPUT);
//   pinMode(INB_1,OUTPUT);

//   //Initializing the Outputs of Motor 2 (left)
//   pinMode(EN2,OUTPUT);
//   pinMode(INA_2,OUTPUT);
//   pinMode(INB_2,OUTPUT);

//   //Initializig the Outputs of encoders of Motor 1 (right)

// }

// // Right motor working
// void rightmotor(float speed){
//   int err_margin = 5;
//   int speedSet;
//   digitalWrite(EN1,HIGH);
//   if(speed>0){
//     //Forward rotation
//     digitalWrite(INB_1,LOW);
//     speed = speed;
//   }
//   else if(speed<0){
//     //Backward rotation
//     digitalWrite(INB_1,HIGH);
//     speed = -speed;
//   }
//   //Setting speed
//   // speedSet = speed;
//   // while (encSpeedright < speed - err_margin || encSpeedright > speed + err_margin){
//   //   if (encSpeedright < speed){
//   //     speedSet++;
//   //   }
//   //   else{
//   //     speedSet--;
//   //   }
//   //   analogWrite(INA_1,speedSet);
//   // }

//   analogWrite(INA_1,speed);

// }

// // Left motor working
// void leftmotor(float speed){
//   int err_margin = 5;
//   int speedSet;
//   digitalWrite(EN2,HIGH);
//   if(speed>0){
//     //Forward rotation
//     digitalWrite(INB_2,LOW);
//     speed = speed;
//   }
//   else if(speed<0){
//     //Backward rotation
//     digitalWrite(INB_2,HIGH);
//     speed = -speed;
//   }
//   //Setting speed
//   // speedSet = speed;
//   // while (encSpeedleft < speed - err_margin || encSpeedleft > speed + err_margin){
//   //   if (encSpeedleft < speed){
//   //     speedSet++;
//   //   }
//   //   else{
//   //     speedSet--;
//   //   }
//   //   analogWrite(INA_2,speedSet);
//   // }

//   analogWrite(INA_2,speed);

// }

// //Calculating the error of line following
// float line(){
//   float sensVals[8]; // List of sensory data
//   int k = 0;
//   int weighted_total = 0;
//   int total = 0;

//   for (int j = A0; j <= A7; ++j) {
//     sensVals[k] = analogRead(j);
//     k++;
//   }

//   for (int k=0; k<=7; k++){
//     sensVals[k] = map(sensVals[k],sensMin[k],sensMax[k],0,1000);
//     weighted_total += sensVals[k] * k;
//     total += sensVals[k];
//   }

//   return weighted_total/total;
// }

// //Calibrating the line following sensors for 5 seconds
// void calibrate(){

// for (int m = 0; m <= 299; m++)
// {
//   int l = 0;
//   for (int j = A0; j <= A7; ++j)
//   {
//     if (sensMax[l] < analogRead(j))
//     {
//       sensMax[l] = analogRead(j);
//     }
//     if (sensMin[l] > analogRead(j))
//     {
//       sensMin[l] = analogRead(j);
//     }
//     l++;
//   }
//   delay(50);
// }
// }