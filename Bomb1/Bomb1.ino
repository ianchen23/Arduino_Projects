/******************************************************
 * Segment display connections:
 * PIN IO: short to PIN +
 * PIN +: 5v
 * PIN -: GND
 * PIN D: A4
 * PIN C: A5
 ******************************************************/

const int yellow=8;
const int red=9;
const int blue=10;
const int white=11;
int yellowValue = HIGH;
int redValue = HIGH;
int blueValue = HIGH;
int whiteValue = HIGH;
int yellowNo = 0;
int redNo = 0;
int blueNo = 0;
int whiteNo = 0;

#include "Wire.h" // Enable this line if using Arduino Uno, Mega, etc.
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();
int t0 = 500;
int t=t0;

void setup() {
  Serial.begin(9600);
  pinMode(yellow,INPUT_PULLUP);
  pinMode(red,INPUT_PULLUP);
  pinMode(blue,INPUT_PULLUP);
  pinMode(white,INPUT_PULLUP);
  matrix.begin(0x70);
}

void loop() {
  yellowValue = digitalRead(yellow);
  redValue = digitalRead(red);
  blueValue = digitalRead(blue);
  whiteValue = digitalRead(white);
  if (yellowValue == HIGH && yellowNo == 0){
    yellowNo = 1;
    if (redNo==0||blueNo==0||whiteNo==0){
      t0=0;
    }
    else {
      exit(0);
    }
  }

  if (redValue == HIGH && redNo == 0){
    redNo = 1;
  }  

  if (blueValue == HIGH && blueNo == 0){
    blueNo = 1;
    if (redNo==0){
      t0=t0-100;
    }
  }  

  if (whiteValue == HIGH && whiteNo == 0){
    whiteNo = 1;
    if (redNo==0||blueNo==0){
      t0=t0-100;
    }
  }
  if(t<0){
    t=0;
  }
  uint16_t blinkcounter = 0;
  matrix.writeDigitNum(0, (t / 1000));
  matrix.writeDigitNum(1, (t / 100) % 10);
  matrix.drawColon(true);
  matrix.writeDigitNum(3, (t / 10) % 10);
  matrix.writeDigitNum(4, t % 10);
  matrix.writeDisplay();
  Serial.println(t);
  t=t0-millis()/100;
  if(t%100==99){
    t0=t0-40;
  }
}
