#include "mbed.h"


Serial pc( USBTX, USBRX );
AnalogOut Aout(DAC0_OUT);
AnalogIn Ain(A0);
DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
BusOut display(D6, D7, D9, D10, D11, D5, D4);
DigitalOut dp(D8);

char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int sample = 512;
int i;
float n = 0;
int f;
float ADCdata[512];


int main(){
  for (i = 0; i < sample; i++){
    ADCdata[i] = Ain;
    wait(1./sample);
  }

  for (i = 0; i < sample; i++){
    pc.printf("%1.3f\r\n", ADCdata[i]);
    wait(0.01);
  }

  for (i = 0; i < sample-1; i++) {
    if( (ADCdata[i]-0.4) * (ADCdata[i+1]-0.3) <= 0)
      n++;
  }

  f=(int)(n/2+0.5);

  while (1) {
    if(Switch == 1){
      redLED = 1;
      greenLED = 0;
      display = 0x00;
      dp = 0;
      if(f>0){
        for (float j=0; j<2; j+=0.05 ) {
          Aout = 0.5 + 0.5*sin(j*3.14159);
          wait(0.025/f);
        }
      }
    }

    else{
      greenLED = 1;
      redLED = 0;
      if(f<100){
        display = table[f/10];
        dp = 0;
        wait(1);
        display = table[f%10];
        dp = 1;
        wait(1);
      }
      else{
        display = table[f/100];
        dp = 0;
        wait(1);
        display = table[(f/10)%10];
        dp = 0;
        wait(1);
        display = table[f%10];
        dp = 1;
        wait(1);
      }
    }
  }
}