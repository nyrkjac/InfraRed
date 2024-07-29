// include libraries for LCD
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int IR = 4;
// LCD-Backlight
int colorR = 0;
int colorG = 0;
int colorB = 0;

void setup(){
  pinMode(IR, INPUT);
  lcd.begin(16, 2); // for a 16 by 2 pixels LCD
  lcd.setRGB(colorR, colorG, colorB);
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("Setup complete");
  delay(1000);
  lcd.clear();
}

void loop(){
  int receiverState = digitalRead(IR);
  if (receiverState == LOW){
    // this code executes if there is an object
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Object detected");
    while (digitalRead(IR) == LOW){
      // do nothing, just wait until the object is gone
    }
  }
  else {
    // this code executes when there is no object
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No object");
    while (digitalRead(IR) == HIGH){
      // wait for object (this loop prevents console spam)
    }
  }
}
