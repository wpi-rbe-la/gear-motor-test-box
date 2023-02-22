#include <Arduino.h>
#include "Display.h"

#define encode1 16
#define encode2 17

 
long currVal;
long newVal;
long encoderVal;
float adjEffort = 0;

long errorCount;

const char X = 5;

signed char encoderArray[4][4] = {    
    {0, 1, -1, X},
    {-1, 0, X, 1},    
    {1, X, 0, -1},    
    {X, -1, 1, 0}
};


void ISR() {  
    newVal = (digitalRead(encode1) << 1) | digitalRead(encode2);
    signed char value = encoderArray[currVal][newVal];
    if (value == X)   {    
        errorCount++;
    } else {    
        encoderVal += value;  
    }  currVal = newVal;
}

Display disp;

void setup() {
  Serial.begin(115200);
  pinMode(encode1, INPUT);
  pinMode(encode2, INPUT);

  attachInterrupt(encode1, ISR, CHANGE);
  attachInterrupt(encode2, ISR, CHANGE);
  disp.init();
}


unsigned long current_time;
unsigned long timer_end = millis();
unsigned long timerTime = 10;


void loop() {

Serial.print(digitalRead(encode1));
Serial.print(", ");
Serial.print(digitalRead(encode2));
Serial.print(", ");
 Serial.println(encoderVal); //3200 counts per rev
 current_time = millis();

  if(current_time >= timer_end){
    disp.clear();
    disp.format();
    disp.dispDistEncoder(int(encoderVal));
    disp.update();
    timer_end = millis() + timerTime;
  } 



}





