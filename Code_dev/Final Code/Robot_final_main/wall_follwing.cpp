#include <Arduino.h>
#include "line_following.h"
#include "distance.h"
#include "wall_following.h"


float last_error_wall = 0;

void wall_follow(float distance,int direction){
  int baseSpeed = 60;
  float Kp = 1;
  float Kd = 1;
  float error;
  float pid;
  float leftspeed;
  float rightspeed;

  float left_sensor_val = sensor_7() - 15;
  float right_sensor_val = sensor_1() - 20;

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
  if (rightspeed>255){
    rightspeed = 255;
  }
  if (leftspeed>255){
    leftspeed = 255;
  }

  leftmotor(leftspeed);
  rightmotor(rightspeed);
  last_error_wall = error;
  delay(1);
}

void rightWallFollowSet(){

  leftmotor(0);
  rightmotor(0);
  delay(1000);
  leftmotor(80);
  rightmotor(-80);
  delay(390);
  leftmotor(0);
  rightmotor(0);
  delay(1000);
  leftmotor(65);
  rightmotor(90);
  delay(100);
  leftmotor(0);
  rightmotor(0);
  delay(1000);

}