#include "mbed.h"


Serial pc( USBTX, USBRX );

AnalogOut Aout(DAC0_OUT);

AnalogIn Ain(A0);


int sample = 512;

int i;


float ADCdata[512];


int main(){

  float n = 0;
  int f;
  for (i = 0; i < sample; i++){

    Aout = Ain;

    ADCdata[i] = Ain;

    wait(1./sample);

  }

  for (i = 0; i < sample; i++){

    pc.printf("%1.3f\r\n", ADCdata[i]);

    wait(0.1);

  }

  for ()

}