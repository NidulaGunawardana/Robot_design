#include <Arduino.h>
#include "line_following.h"
#include "distance.h"
#include "wall_following.h"


float last_error_wall = 0;

void wall_follow(float distance,int direction){
  int baseSpeed = 60;
  float Kp = 0.5;
  float Kd = 1;
  float error;
  float pid;
  float leftspeed;
  float rightspeed;
  float sens7 = 0;
  float sens1 = 0;

  for (int i = 0;i<3;i++){
    sens7 += sensor_7();
    sens1 += sensor_1();
    delayMicroseconds(10);
  }
  sens7 = sens7/5;
  sens1 = sens1/5;

  if (sens1 > 500){
    sens1 = 500;
  }
  if (sens7 > 500){
    sens7 = 500;
  }

  float left_sensor_val = sens7 - 15;
  float right_sensor_val = sens1 - 20;

  if (direction == 1){ //right sided wall following
    error = right_sensor_val - distance;
    pid = Kp*error + Kd*(error - last_error_wall);
  }

  if (direction == -1){ //left sided wall following
    error = left_sensor_val - distance;
    pid = -(Kp*error + Kd*(error - last_error_wall));
  }
  
  leftspeed = baseSpeed - pid;
  rightspeed = baseSpeed + 20 + pid;

  //speed filter
  if (rightspeed<0){
    rightspeed = 0;
  }
  if (leftspeed<0){
    leftspeed = 0;
  }
  if (rightspeed>100){
    rightspeed = 100;
  }
  if (leftspeed>100){
    leftspeed = 100;
  }

  leftmotor(leftspeed);
  rightmotor(rightspeed);
  Serial.print(leftspeed);
  Serial.print(" ");
  Serial.println(rightspeed);
  last_error_wall = error;
  delay(1);
}

void rightWallFollowSet(){

  leftmotor(0);
  rightmotor(0);
  delay(1000);
  leftmotor(80);
  rightmotor(-80);
  delay(450);
  leftmotor(0);
  rightmotor(0);
  delay(1000);

}

void leftWallFollowSet(){

  leftmotor(0);
  rightmotor(0);
  delay(1000);
  leftmotor(-80);
  rightmotor(80);
  delay(390);
  leftmotor(0);
  rightmotor(0);
  delay(1000);

}

int objectDetected(float th){
 
  if (sensor_4() < th){
    // right object is detected
    return 1;
  }
  else
  {
    return 0;
  }


}