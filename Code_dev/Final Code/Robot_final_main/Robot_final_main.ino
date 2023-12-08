#include <EasyNextionLibrary.h>
#include "distance.h"
#include "line_following.h"
#include "wall_following.h"
#include "gyro_readings.h"
#include "guaed_robot.h"
#include "mic_reading.h"
#include "robot_arm.h"
#include "BeeLineSensorPro.h"
EasyNex disp = EasyNex(Serial);

float speed = 60;  //line- 75 wall - 60 sound - 61
int level = 1;
float kp = 0.041;
float kd = 0.1;
bool measureDistance = false;
bool lineFollowing = false;


void setup() {
  // disp.begin(9600);
  // disp.writeStr("t0.txt", "Please Wait...");
  setID();
  Serial.begin(9600);
  portFix();
  servoPortFix();
  delay(100);
  // setup_gyro();
  setup_mic();
  // disp.writeStr("t0.txt", "Calibrate to begin");
  armLift();
  calibrate();
  searchPos();
  delay(5000);

  // calibrate();
  // delay(5000);
}

void loop() {

  // float distSensors[7] = {sensor_1(),sensor_2(),sensor_3(),sensor_4(),sensor_5(),sensor_6(),sensor_7()};
  // for (int i = 0;i<7;i++){
  //   Serial.print(distSensors[i]);
  //   Serial.print(" ");
  // }
  // Serial.println("");
  // delay(10);


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Serial.println("In the loop");

  // wall_follow_to_run(speed, kp, kd);

  //////////////////////////////////////////////////

  // disp.NextionListen();
  // if (measureDistance == true) {
  //   if (sensor_1() <= 150){
  //     wall_follow(100);
  //   }
  //   else{
  //     linefollow();
  //   }
  // }
  // if (lineFollowing == true) {
  //   linefollow();
  // }

  /////////////////////////////

  // float angle = get_angle();
  // if (angle < -9.00) {
  //   speed = 140;
  // } else if (angle > 8.00) {
  //   speed = 2;
  // } else {
  //   speed = 65;
  // }

  // linefollow(speed);
  // leftmotor(speed);
  // rightmotor(speed + 20);

  //////////////////////////////

  // detect_guard();
  double frequency = read_max_frequency();
  if (frequency > 950 && frequency < 1050) {
    linefollow(speed,0.01,0.02);
  } else {
    leftmotor(0);
    rightmotor(0);
  }
}


//Start button
void trigger0() {
  if (level == 1) {
    disp.writeStr("page task1");
    measureDistance = false;
    lineFollowing = true;
  } else if (level == 2) {
    disp.writeStr("page task2");
    measureDistance = true;
    lineFollowing = false;
  } else if (level == 3) {
    disp.writeStr("page task1");
    measureDistance = false;
    lineFollowing = false;
  } else if (level == 4) {
    disp.writeStr("page task1");
    measureDistance = false;
    lineFollowing = false;
  } else if (level == 5) {
    disp.writeStr("page task1");
    measureDistance = false;
    lineFollowing = false;
  } else if (level == 6) {
    disp.writeStr("page task1");
    measureDistance = false;
    lineFollowing = false;
  } else if (level == 7) {
    disp.writeStr("page task2");
    measureDistance = false;
    lineFollowing = false;
  }
}

//level down
void trigger1() {
  level--;
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("t0.txt", (String)level);
}

// level up
void trigger2() {
  level++;
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("t0.txt", (String)level);
}

// speed down
void trigger3() {
  speed--;
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("t2.txt", (String)speed);
}

// Speed Up
void trigger4() {
  speed++;
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("t2.txt", (String)speed);
}

// calibrate button
void trigger5() {
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("t0.txt", "Calibrating...");
  calibrate();
  delay(7000);
  disp.writeStr("t0.txt", "Calibration Done.");
}

// Home button
void trigger6() {
  speed++;
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("page home");
  disp.writeStr("t0.txt", (String)level);
  disp.writeStr("t2.txt", (String)speed);
}

// goto calibrate menue
void trigger7() {
  measureDistance = false;
  disp.writeStr("page calib");
}

// Settings button
void trigger8() {
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("page settings");
  disp.writeStr("t3.txt", (String)kd);
  disp.writeStr("t2.txt", (String)kp);
}

// Kp up
void trigger9() {
  kp += 0.001;
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("t2.txt", (String)kp);
}

// Kp down
void trigger10() {
  kp -= 0.001;
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("t2.txt", (String)kp);
}

// Kd up
void trigger11() {
  kd += 0.01;
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("t3.txt", (String)kd);
}


// Kd down
void trigger12() {
  kd -= 0.01;
  measureDistance = false;
  lineFollowing = false;
  disp.writeStr("t3.txt", (String)kd);
}

// Task stop button
void trigger13() {
  measureDistance = false;
  lineFollowing = false;
  rightmotor(0);
  leftmotor(0);
}
