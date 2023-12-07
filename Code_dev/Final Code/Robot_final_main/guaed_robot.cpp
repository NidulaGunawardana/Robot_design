#include "HardwareSerial.h"
#include <Arduino.h>
#include "distance.h"
#include "guaed_robot.h"

int sensor_detection[5] = { 0, 0, 0, 0, 0 };
int dir = 0;

void detect_guard() {
  float sensor1 = 0;
  float sensor2 = 0;
  float sensor3 = 0;
  float sensor4 = 0;
  float sensor5 = 0;

  for (int k = 0; k < 2; k++) {
    sensor1 += sensor_2();
    delay(1);
  }
  sensor1 = sensor1 / 2;

  for (int k = 0; k < 2; k++) {
    sensor2 += sensor_3();
    delay(1);
  }
  sensor2 = sensor2 / 2;

  for (int k = 0; k < 2; k++) {
    sensor3 += sensor_4();
    delay(1);
  }
  sensor3 = sensor3 / 2;

  for (int k = 0; k < 2; k++) {
    sensor4 += sensor_5();
    delay(1);
  }
  sensor4 = sensor4 / 2;

  for (int k = 0; k < 2; k++) {
    sensor5 += sensor_6();
    delay(1);
  }
  sensor5 = sensor5 / 2;


  // Serial.print((String)sensor1 + " ");
  // Serial.print((String)sensor2 + " ");
  // Serial.print((String)sensor3 + " ");
  // Serial.print((String)sensor4 + " ");
  // Serial.print((String)sensor5 + " ");
  // Serial.println("");
  if (sensor1 < 450) {
    if (sensor_detection[3] == 1 && sensor_detection[4] == 0) {
      dir++;
      sensor_detection[0] = 0;
      sensor_detection[1] = 0;
      sensor_detection[2] = 0;
      sensor_detection[3] = 0;
      sensor_detection[4] = 0;
    } else if (sensor_detection[4] == 0 && sensor_detection[3] == 0) {
      dir--;
      sensor_detection[0] = 0;
      sensor_detection[1] = 0;
      sensor_detection[2] = 0;
      sensor_detection[3] = 0;
      sensor_detection[4] = 1;
    }


  } else if (sensor2 < 400) {
    if (sensor_detection[2] == 1 && sensor_detection[4] == 0) {
      dir++;
    } else if (sensor_detection[4] == 1 && sensor_detection[2] == 0) {
      dir--;
    }
    sensor_detection[0] = 0;
    sensor_detection[1] = 0;
    sensor_detection[2] = 0;
    sensor_detection[3] = 1;
    sensor_detection[4] = 0;
  } else if (sensor3 < 250) {
    if (sensor_detection[1] == 1 && sensor_detection[3] == 0) {
      dir++;
    } else if (sensor_detection[3] == 1 && sensor_detection[1] == 0) {
      dir--;
    }
    sensor_detection[0] = 0;
    sensor_detection[1] = 0;
    sensor_detection[2] = 1;
    sensor_detection[3] = 0;
    sensor_detection[4] = 0;
  } else if (sensor4 < 400) {
    if (sensor_detection[0] == 1 && sensor_detection[2] == 0) {
      dir++;
    } else if (sensor_detection[2] == 1 && sensor_detection[0] == 0) {
      dir--;
    }
    sensor_detection[0] = 0;
    sensor_detection[1] = 1;
    sensor_detection[2] = 0;
    sensor_detection[3] = 0;
    sensor_detection[4] = 0;
  } else if (sensor5 < 475) {
    if (sensor_detection[1] == 1 && sensor_detection[0] == 0) {
      dir--;
      sensor_detection[0] = 0;
      sensor_detection[1] = 0;
      sensor_detection[2] = 0;
      sensor_detection[3] = 0;
      sensor_detection[4] = 0;
    } else if (sensor_detection[1] == 0 && sensor_detection[0] == 0) {
      dir++;
      sensor_detection[0] = 1;
      sensor_detection[1] = 0;
      sensor_detection[2] = 0;
      sensor_detection[3] = 0;
      sensor_detection[4] = 0;
    }
  }
  if (dir > 4) {
    dir = 5;
  } else if (dir < -4) {
    dir = -5;
  }
  for (int i = 0; i < 5; i++) {
    Serial.print((String)sensor_detection[i] + " ");
  }
  Serial.print(dir);
  Serial.println("");

  // sensor_detection[0] = 0;
  // sensor_detection[1] = 0;
  // sensor_detection[2] = 0;
  // sensor_detection[3] = 0;
  // sensor_detection[4] = 0;
}
