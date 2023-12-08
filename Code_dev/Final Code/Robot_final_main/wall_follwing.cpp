#include <Arduino.h>
#include "line_following.h"
#include "distance.h"
#include "wall_following.h"
#include "robot_arm.h"


float last_error_wall = 0;
int wall_flag = 0;

void wall_follow(float distance, int direction) {
  int baseSpeed = 60;
  float Kp = 0.5;
  float Kd = 1;
  float error;
  float pid;
  float leftspeed;
  float rightspeed;
  float sens7 = 0;
  float sens1 = 0;

  for (int i = 0; i < 3; i++) {
    sens7 += sensor_7();
    sens1 += sensor_1();
    delayMicroseconds(10);
  }
  sens7 = sens7 / 5;
  sens1 = sens1 / 5;

  if (sens1 > 500) {
    sens1 = 500;
  }
  if (sens7 > 500) {
    sens7 = 500;
  }

  float left_sensor_val = sens7 - 15;
  float right_sensor_val = sens1 - 20;

  if (direction == 1) {  //right sided wall following
    error = right_sensor_val - distance;
    pid = Kp * error + Kd * (error - last_error_wall);
  }

  if (direction == -1) {  //left sided wall following
    error = left_sensor_val - distance;
    pid = -(Kp * error + Kd * (error - last_error_wall));
  }

  leftspeed = baseSpeed - pid;
  rightspeed = baseSpeed + 20 + pid;

  //speed filter
  if (rightspeed < 0) {
    rightspeed = 0;
  }
  if (leftspeed < 0) {
    leftspeed = 0;
  }
  if (rightspeed > 100) {
    rightspeed = 100;
  }
  if (leftspeed > 100) {
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

void rightWallFollowSet() {

  leftmotor(0);
  rightmotor(0);
  delay(1000);
  leftmotor(80);
  rightmotor(-80);
  delay(500);
  leftmotor(0);
  rightmotor(0);
  delay(1000);
}

void leftWallFollowSet() {

  leftmotor(0);
  rightmotor(0);
  delay(1000);
  leftmotor(-80);
  rightmotor(80);
  delay(450);
  leftmotor(0);
  rightmotor(0);
  delay(1000);
}

int objectDetected(float th) {

  if (sensor_4() < th) {
    // right object is detected
    return 1;
  } else {
    return 0;
  }
}

void wall_follow_to_run(int speed, float kp, float kd) {
  searchPos();
  if (objectDetected(180) == 0) {
    linefollow(speed, 0.015, 0.02);
  } else if (objectDetected(180) == 1 && wall_flag == 0) {
    //right wall follow
    rightWallFollowSet();
    // float rightVal = sensor_1();
    // float intialRightVal = rightVal;
    // while (sensor_1() < intialRightVal + 100){
    //   wall_follow(intialRightVal, 1);
    // }
    while (analogRead(A0) > 150 && analogRead(A1) > 150 && analogRead(A2) > 150 && analogRead(A3) > 150 && analogRead(A4) > 150 && analogRead(A5) > 150 && analogRead(A6) > 150) {
      leftmotor(60);
      rightmotor(80);
      delay(2);
    }
    delay(300);
    rightmotor(0);
    leftmotor(0);
    delay(200);
    searchPos();
    wall_flag++;
    delay(200);
  } else if (objectDetected(180) == 1 && wall_flag == 1) {
    //right wall follow
    leftWallFollowSet();
    // float rightVal = sensor_1();
    // float intialRightVal = rightVal;
    // while (sensor_1() < intialRightVal + 100){
    //   wall_follow(intialRightVal, 1);
    // }
    while (analogRead(A0) > 150 && analogRead(A1) > 150 && analogRead(A2) > 150 && analogRead(A3) > 150 && analogRead(A4) > 150 && analogRead(A5) > 150 && analogRead(A6) > 150) {
      leftmotor(60);
      rightmotor(80);
      delay(2);
    }
    delay(300);
    rightmotor(0);
    leftmotor(0);
    delay(200);
    rightTurn();
    searchPos();
    delay(200);
    wall_flag++;
  }
}

void resetFlag() {
  wall_flag = 0;
}