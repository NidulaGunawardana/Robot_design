#include <Servo.h>

Servo lift ; // lifing servo servo2 >> attach to 12
Servo grip; // gripping servo >> attach to 11

void servoPortFix(){
  lift.attach(12);
  grip.attach(11);
}
void griplift(){ //grip an object and lift it
  gripperOpen();
  armDown();
  gripperClose();
  armLift();
}

void gripDrop(){ //release a gripped object
  armDown();
  gripperOpen();
  armLift();
}

void gripperOpen(){ //open the gripper
  for (int i = 0;i <= 170; i++){
    grip.write(i);
    delay(12);
  }
}

void gripperClose(){ // close the gripper
  for (int i = 170;i >= 0; i--){
    grip.write(i);
    delay(12);
  }
}

void armLift(){ //lift the whole arm
  for (int i = 95;i <= 140; i++){
    lift.write(i);
    delay(12);
  }
}

void armDown(){ //drop the whole arm
  for (int i = 140;i >= 95; i--){
    lift.write(i);
    delay(12);
  }
}

void initialPos(int vertical, int gripPos){ //initial position initializer
  grip.write(gripPos);
  lift.write(vertical);
} 

void searchPos(){
  lift.write(110);
  grip.write(170);
}