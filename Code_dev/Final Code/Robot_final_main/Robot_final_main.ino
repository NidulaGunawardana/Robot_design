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

float speed = 65;  //line- 75 wall - 60 sound - 61
int level = 1;
int allWhiteFlag = 0;
int bypass = 0;
float kp = 0.035;
float kd = 0.026;
bool task1 = false;
bool task2 = false;
bool task3 = false;
bool task4 = false;
bool task5 = false;
bool task6 = false;
bool task7 = false;
bool start = false;



void setup() {
  disp.begin(9600);
  disp.writeStr("t0.txt", "Please Wait...");
  setID();
  // Serial.begin(9600);
  portFix();
  servoPortFix();
  delay(100);
  setup_gyro();
  setup_mic();
  disp.writeStr("t0.txt", "Calibrate to begin");
  armLift();

  // calibrate();
  // searchPos();
  // delay(5000);

  // calibrate();
  // delay(5000);
}

void loop() {
  bool task_detected = (task1 || task2 || task3 || task4 || task5 || task6 || task7);
  if (analogRead(A0) < 60 && analogRead(A1) < 60 && analogRead(A2) < 60 && analogRead(A3) < 60 && analogRead(A4) < 60 && analogRead(A5) < 60 && analogRead(A6) < 60 && analogRead(A7) < 60 && task_detected)  //detection of a straight line junction
  {
    if (bypass != 2){
      rightmotor(90);
      leftmotor(65);
      delay(750);
      rightmotor(0);
      leftmotor(0);
      delay(800);
    }
    else{
      rightmotor(0);
      leftmotor(0);
      delay(800);
    }

    allWhiteFlag++;

    if (allWhiteFlag == 1) {
      level = 1;
      disp.NextionListen();
      trigger0();
      allWhiteFlag++;
    } else if (allWhiteFlag == 2) {
      rightTurn();
      level = 2;
      disp.NextionListen();
      trigger0();
      allWhiteFlag++;
    } else if (allWhiteFlag == 3) {  
      armLift();
      delay(200);
      rightTurn();
      level = 3;
      disp.NextionListen();
      trigger0();
      allWhiteFlag++;
    } else if (allWhiteFlag == 4) {  //defining the ending position
      // rightTurn();
      level = 4;
      disp.NextionListen();
      trigger0();
      allWhiteFlag++;
    }
    else if (allWhiteFlag == 5){
      bypass = 1;
      rightmotor(-90);
      leftmotor(-65);
      delay(400);
      rightmotor(0);
      leftmotor(0);
      delay(800);
      rightTurn();
      armDown();
      gripperOpen();
    }
    else if (allWhiteFlag == 6){
      bypass = 0;
    }
    else if (allWhiteFlag == 7){
      rightmotor(90);
      leftmotor(65);
      delay(300);
      rightmotor(-90);
      leftmotor(65);
      delay(240);
      leftTurn(); 
    }
    else if (allWhiteFlag == 8){
      rightTurn();
    }
  }


  disp.NextionListen();

  if (task1) {
    speed = 60;
    kp = 0.032;
    kd = 0.026;
    linefollow(speed, kp, kd);

  } else if (task2) {
    speed = 59;
    kp = 0.015;
    kd = 0.02;
    wall_follow_to_run(speed, kp, kd);
  } else if (task3) {
    float angle = get_angle();
    if (angle < -5.5) {
      speed = 105;
    } else if (angle > 3) {
      speed = -5;
    } else {
      if (speed > 125 || speed < 15) {
        leftmotor(0);
        rightmotor(0);
        delay(1000);
      }
      speed = 58;
    }

    // speed = 75;
    kp = 0.02;
    kd = 0.026;
    linefollow(speed, kp, kd);
 
  } else if (task4) {
 disp.writeStr("t0.txt", (String)allWhiteFlag);
    if (bypass == 0){
      // speed = 75;
      kp = 0.02;
      kd = 0.026;
      linefollow(speed, kp, kd);
    }
    else if (bypass ==1){
      
      // speed = 75;
      kp = 0.02;
      kd = 0.026;
      while (sensor_4() > 80){
        // speed = 75;
        kp = 0.02;
        kd = 0.026;
        linefollow(speed, kp, kd);
    }
     rightmotor(0);
      leftmotor(0);
      delay(1000);
      gripperClose();
      rightmotor(-90);
      leftmotor(-65);
      delay(3000);
      rightmotor(0);
      leftmotor(0);
      delay(1000);
      gripperOpen();
      delay(300);
      armLift();
      delay(300);

      rightmotor(90);
      leftmotor(65);
      delay(300);
      rightmotor(90);
      leftmotor(-65);
      delay(240);
      rightTurn(); 

      allWhiteFlag = 6;

    }

    else if (bypass == 2){
      while (sensor_4() > 30){
        rightmotor(90);
        leftmotor(65);
      }
    
    }
    

    // gripperOpen();
    // armDown();
    // gripperClose();
    // leftmotor(-65);
    // rightmotor(-90);
    // delay(1000);
  } else if (task5) {
    
    disp.writeStr("t0.txt", (String)sensor_4());
  } else if (task6) {
    double frequency = read_max_frequency();
    disp.writeStr("t0.txt", (String)frequency);
    speed = 55;
    if (frequency < 950 || frequency > 1050) {
      linefollow(speed, 0.009, 0.02);
    } else {
      leftmotor(0);
      rightmotor(0);
    }
  } else if (task7) {
  } else {
    leftmotor(0);
    rightmotor(0);
  }
  disp.NextionListen();





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



  //////////////////////////////

  // detect_guard();
}


//Start button
void trigger0() {
  if (level == 1) {
    task1 = true;
    task2 = false;
    task3 = false;
    task4 = false;
    task5 = false;
    task6 = false;
    task7 = false;
    allWhiteFlag = 0;
    disp.writeStr("page task1");
    delay(100);
  } else if (level == 2) {
    disp.writeStr("page task2");
    resetFlag();
    task1 = false;
    task2 = true;
    task3 = false;
    task4 = false;
    task5 = false;
    task6 = false;
    task7 = false;
    allWhiteFlag = 1;
    delay(100);
  } else if (level == 3) {
    disp.writeStr("page task1");
    task1 = false;
    task2 = false;
    task3 = true;
    task4 = false;
    task5 = false;
    task6 = false;
    task7 = false;
    allWhiteFlag = 2;
  } else if (level == 4) {
    task1 = false;
    task2 = false;
    task3 = false;
    task4 = true;
    task5 = false;
    task6 = false;
    task7 = false;
    allWhiteFlag = 3;
    bypass = 0;
    disp.writeStr("page task1");
  } else if (level == 5) {
    task1 = false;
    task2 = false;
    task3 = false;
    task4 = false;
    task5 = true;
    task6 = false;
    task7 = false;
    disp.writeStr("page task1");
  } else if (level == 6) {
    task1 = false;
    task2 = false;
    task3 = false;
    task4 = false;
    task5 = false;
    task6 = true;
    task7 = false;
    disp.writeStr("page task1");
  } else if (level == 7) {
    task1 = false;
    task2 = false;
    task3 = false;
    task4 = false;
    task5 = false;
    task6 = false;
    task7 = true;
    disp.writeStr("page task2");
  }
}

//level down
void trigger1() {
  level--;
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("t0.txt", (String)level);
}

// level up
void trigger2() {
  level++;
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("t0.txt", (String)level);
}

// speed down
void trigger3() {
  speed--;
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("t2.txt", (String)speed);
}

// Speed Up
void trigger4() {
  speed++;
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("t2.txt", (String)speed);
}

// calibrate button
void trigger5() {
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("t0.txt", "Calibrating...");
  calibrate();
  delay(4000);
  disp.writeStr("t0.txt", "Calibration Done.");
}

// Home button
void trigger6() {
  speed++;
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("page home");
  disp.writeStr("t0.txt", (String)level);
  disp.writeStr("t2.txt", (String)speed);
}

// goto calibrate menue
void trigger7() {
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("page calib");
}

// Settings button
void trigger8() {
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("page settings");
  disp.writeStr("t3.txt", (String)kd);
  disp.writeStr("t2.txt", (String)kp);
}

// Kp up
void trigger9() {
  kp += 0.001;
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("t2.txt", (String)kp);
}

// Kp down
void trigger10() {
  kp -= 0.001;
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("t2.txt", (String)kp);
}

// Kd up
void trigger11() {
  kd += 0.001;
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("t3.txt", (String)kd);
}


// Kd down
void trigger12() {
  kd -= 0.001;
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  disp.writeStr("t3.txt", (String)kd);
}

// Task stop button
void trigger13() {
  task1 = false;
  task2 = false;
  task3 = false;
  task4 = false;
  task5 = false;
  task6 = false;
  task7 = false;
  rightmotor(0);
  leftmotor(0);
}
