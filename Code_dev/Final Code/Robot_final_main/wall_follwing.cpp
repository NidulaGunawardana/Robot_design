#include <Arduino.h>
#include "line_following.h"
#include "distance.h"
#include "wall_following.h"


bool wall_follow(float distance,int direction){
  int baseSpeed = 75;
  float Kp = 1;
  float error;
  float pid;
  float leftspeed;
  float rightspeed;

  float left_sensor_val = sensor_7();
  float right_sensor_val = sensor_1();


  if (right_sensor_val < distance*1.5){
    error = right_sensor_val - distance;
    pid = Kp*error;
  }

  if (direction == 1){
    error = right_sensor_val - distance;
    pid = Kp*error;
  }
  
  leftspeed = baseSpeed - pid;
  rightspeed = baseSpeed + 20 + pid;

  if (rightspeed<0){
    rightspeed = 0;
  }
  if (leftspeed<0){
    leftspeed = 0;
  }

  leftmotor(leftspeed);
  rightmotor(rightspeed);
  delay(5);
}