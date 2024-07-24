// include libraries for LCD
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int IR = 4;
// LCD-Backlight
int colorR = 0;
int colorG = 255;
int colorB = 0;
// variables for time between objects
unsigned long lastTime = 0;
unsigned long currentTime = 0;
int counter = 0;
int amountTimes = 5;
int timeList[6] = {0, 0, 0, 0, 0, 0};
int objects = 0; // counts total objects

// stores times in a list and prints
void addTime(){
  objects++;
  if(counter == amountTimes){
    // this code runs every when the counter is at max
    int total = 0;
    for (byte i = 0; i < amountTimes; i++){
      total = total + timeList[i];
    }
    float avg = (total/amountTimes)+0.5;
    int avgRound = (int) avg;
    Serial.println(avgRound); // print avg of last 5 times to the console
    counter = 0;
  }
  else {
    counter++;
  }
  // set time for next measurement
  lastTime = currentTime;
}

void setup(){
  pinMode(IR, INPUT);
  lcd.begin(16, 2); // for a 16 by 2 pixels LCD
  lcd.setRGB(colorR, colorG, colorB);
  Serial.begin(9600);
}

void loop(){
  int receiverState = digitalRead(IR);
  if (receiverState == LOW){
    // this code executes if there is an object
    if (lastTime == 0) {
      // first object detected
      lastTime = millis();
    } else {
      // second object detected
      currentTime = millis();
      unsigned long duration = currentTime - lastTime;
      timeList[counter] = duration;
      addTime();

      // clear LCD and print new time
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(duration);
      lcd.print("ms since obj");
      lcd.setCursor(0, 1);
      lcd.print(objects);
      lcd.print(" in total");
    }
    while (digitalRead(IR) == LOW){
      // do nothing, just wait until the object is gone
    }
  }
  else {
    // this code executes when there is no object
    while (digitalRead(IR) == HIGH){
      // wait for object (this loop prevents console spam)
    }
  }
}
