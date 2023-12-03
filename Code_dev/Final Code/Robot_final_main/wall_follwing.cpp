#include <Arduino.h>
#include "line_following.h"
#include "distance.h"

void wall_follow(float distance){
  int baseSpeed = 75;
  float Kp = 1;
  float error = sensor_1() - distance;
  float pid = Kp*error;
  leftmotor(baseSpeed+pid);
  rightmotor(baseSpeed+20-pid);
}