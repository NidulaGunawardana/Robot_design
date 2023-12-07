#ifndef ROBOT_ARM
#define ROBOT_ARM

#include <Servo.h>
#include <Arduino.h>

void servoPortFix();
void griplift();
void gripDrop();
void gripperOpen();
void gripperClose();
void armLift();
void armDown();
void initialPos(int vertical, int gripPos);
void searchPos();


#endif