

#include "arduinoFFT.h"
#include <Arduino.h>

arduinoFFT FFT;
/*
These values can be changed in order to evaluate the functions
*/
#define CHANNEL A8
const uint16_t samples = 128; //This value MUST ALWAYS be a power of 2
const double samplingFrequency = 3000; //Hz, must be less than 10000 due to ADC

unsigned int sampling_period_us;
unsigned long microseconds;

/*
These are the input and output vectors
Input vectors receive computed results from FFT
*/
double vReal[samples];
double vImag[samples];

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void setup_mic()
{
  sampling_period_us = round(1000000*(1.0/samplingFrequency));
 
}

double read_max_frequency()
{
  /*SAMPLING*/
  microseconds = micros();
  for(int i=0; i<samples; i++)
  {
      vReal[i] = analogRead(CHANNEL);
      vImag[i] = 0;
      while(micros() - microseconds < sampling_period_us){
        //empty loop
      }
      microseconds += sampling_period_us;
  }
  FFT = arduinoFFT(vReal, vImag, samples, samplingFrequency); /* Create FFT object */
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);	/* Weigh data */
  FFT.Compute(FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(); /* Compute magnitudes */
  double x = FFT.MajorPeak();
  return x;
}
