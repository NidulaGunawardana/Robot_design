#ifndef LINE_FOLLOWING
#define LINE_FOLLOWING
#include <Arduino.h>
#include "line_following.h"

void portFix();
void rightmotor(float speed);
void leftmotor(float speed);
void rightTurn();
void leftTurn();
void calibrate();
void linefollow(int baseSpeed_1,float Kp, float Kd);
void backlinefollow(int baseSpeed_1,float Kp, float Kd);

#endif