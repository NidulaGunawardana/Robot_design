#include <EasyNextionLibrary.h>
#include "distance.h"
#include "line_following.h"
#include "wall_following.h"
#include "gyro_readings.h"
#include "guaed_robot.h"
EasyNex disp = EasyNex(Serial);

float speed = 62;
int level = 1;
float kp = 0.041;
float kd = 0.1;
bool measureDistance = false;
bool lineFollowing = false;

void setup() {
  disp.begin(9600);
  disp.writeStr("t0.txt", "Please Wait...");
  setID();
  portFix();
  setup_gyro();
  disp.writeStr("t0.txt", "Calibrate to begin");
  
}

void loop() {

  float distSensors[7] = {sensor_1(),sensor_2(),sensor_3(),sensor_4(),sensor_5(),sensor_6(),sensor_7()};
  for (int i = 0;i<8;i++){
    Serial.print(distSensors[i]);
    Serial.print(" ");
  }
  Serial.println("");
  delay(50);
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
  // if (angle > -9.00) {
  //   Serial.println(angle);
  // }
  //////////////////////////////

  detect_guard();
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
