#ifndef WALL_FOLLOWING
#define WALL_FOLLOWING
#include <Arduino.h>
#include "line_following.h"
#include "distance.h"
#include "wall_following.h"
#include "robot_arm.h"


void wall_follow(float diatance, int direction);
void rightWallFollowSet();
void leftWallFollowSet();
int objectDetected(float th);
void wall_follow_to_run(int speed, float kp, float kd);
void resetFlag();

#endif