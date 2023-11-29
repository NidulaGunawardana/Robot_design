#include <Arduino.h>

const int encoderIn = 3;
const int statusLED = 13;
int detectState = 0;

void pins()
{
  pinMode(encoderIn, INPUT);
  pinMode(statusLED, OUTPUT);
}


void encoderTester() {
  // Poll the encoder reading
  detectState = digitalRead(encoderIn);

  if (detectState == HIGH) {
    // If encoder output is high
    digitalWrite(statusLED, HIGH);
    // Turn on the status LED
  }
  else {
    // Else
    digitalWrite(statusLED, LOW);
    // Turn off the status LED
  }
}
