/******************************************************
 * Segment display connections:
 * PIN IO: short to PIN +
 * PIN +: 5v
 * PIN -: GND
 * PIN D: A4
 * PIN C: A5
 ******************************************************/
 
#include "Wire.h" // Enable this line if using Arduino Uno, Mega, etc.
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();
int t = 500;

void setup() {
//#ifndef __AVR_ATtiny85__
  //Serial.begin(9600);
  //Serial.println("7 Segment Backpack Test");
//#endif
  matrix.begin(0x70);
}

void loop() {
  uint16_t blinkcounter = 0;
  matrix.writeDigitNum(0, (t / 1000));
  matrix.writeDigitNum(1, (t / 100) % 10);
  matrix.drawColon(true);
  matrix.writeDigitNum(3, (t / 10) % 10);
  matrix.writeDigitNum(4, t % 10);
  matrix.writeDisplay();
  delay(100);
  if (t%100==0){
    t=t-40;
  }
  t--;
  if(t<0){
    t=0;
  }
}
