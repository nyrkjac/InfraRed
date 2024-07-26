// include libraries for LCD
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int IR_pin = 4;
const int LCD_colorR = 0;
const int LCD_colorG = 255;
const int LCD_colorB = 0;
const int amount = 6;  // number of spokes to average
const int debounce_time = 5;  // minimum time between objects in ms

unsigned long lastTime = 0;
unsigned long currentTime = 0;
int timeList[amount];
int counter = 0;
int objects = 1;  // counts total objects (gets first updated with 2nd object)

// initializes list by putting int 0 in each element
void initList() {
  for (byte i = 0; i < amount; i++) {
    timeList[i] = 0;
  }
}

void printLCD(unsigned long duration, int objects) {
  // clear LCD and print new time
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(duration);
  lcd.print("ms since obj");
  lcd.setCursor(0, 1);
  lcd.print(objects);
  lcd.print(" in total");
}

// stores times in a list and prints average every [amount] times
void addTime(unsigned long duration) {
  timeList[counter] = duration;
  if (counter == amount - 1) {
    // this code runs every [amount] times
    int total = 0;
    for (byte i = 0; i < amount; i++) {
      total += timeList[i];
    }
    float avgFloat = static_cast<float>(total) / amount;
    int avgInt = static_cast<int>(avgFloat + 0.5);  // round te nearest int
    Serial.println(avgInt);  // print avg of last [amount] times to the console
    counter = 0;
  } else {
    counter++;
  }
  lastTime = currentTime;  // set time for next measurement
}

void waitForObject() {
  while (digitalRead(IR_pin) == HIGH) {
    // do nothing, just wait for an object
  }
}

void waitForSpace() {
  while (digitalRead(IR_pin) == LOW) {
    // do nothing, just wait for the object to leave
  }
}

void setup() {
  pinMode(IR_pin, INPUT);
  lcd.begin(16, 2);  // for a 16 by 2 pixels LCD
  lcd.setRGB(LCD_colorR, LCD_colorG, LCD_colorB);
  initList();
  Serial.begin(9600);
}

void loop() {
  int receiverState = digitalRead(IR_pin);
  if (receiverState == LOW) {
    // code executes if an object is detected
    currentTime = millis();
    if (lastTime != 0) {
      // calculate time between objects
      unsigned long duration = currentTime - lastTime;
      if (duration > debounce_time) {
        // objects within 5ms of the last one will be ignored. This yields better results with poor sensors
        objects++;
        addTime(duration);
        printLCD(duration, objects);
      }
    }
    waitForSpace();
  } else {
    // code executes when there is no object
    waitForObject();
  }
}
