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
void linefollow();

#endif