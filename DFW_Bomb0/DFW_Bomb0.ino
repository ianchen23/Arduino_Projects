 /******************************************************
 * Segment display connections:
 * PIN IO: short to PIN +
 * PIN +: 5v
 * PIN -: GND
 * PIN D: A4
 * PIN C: A5
 ******************************************************
 * Correct pin connections:
 * 2-8, 3-9, 4-10, 5-11
 * Pin 13 controls output (powerstrip)
 ******************************************************/
int n = 0;
int count = 0;
int stat = 0;
int t0 = 6000;
int t = 0;
int password = 7912;

#include "Wire.h" // Enable this line if using Arduino Uno, Mega, etc.
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);
//  Serial.println("Good day sir!");
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
//  pinMode(13, OUTPUT); //controls powerstrip
  matrix.begin(0x70);
  digitalWrite(13,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (n == 0){
    digitalWrite(2, LOW);
    if (digitalRead(8) ==  LOW && digitalRead(9) == HIGH && digitalRead(10) == HIGH && digitalRead(11) == HIGH)
    {      count ++;    }
    else    {      count = 0;    } 
    delay(50);
    digitalWrite(2, HIGH);
    n = 1;
  }
  if (n == 1){
    digitalWrite(3, LOW);
    if (digitalRead(8) == HIGH && digitalRead(9) ==  LOW && digitalRead(10) == HIGH && digitalRead(11) == HIGH)
    {      count ++;    }
    else    {      count = 0;    } 
    delay(50);
    digitalWrite(3, HIGH);
    n = 2;
  } 
  if (n == 2){
    digitalWrite(4, LOW);
    if (digitalRead(8) == HIGH && digitalRead(9) == HIGH && digitalRead(10) ==  LOW && digitalRead(11) == HIGH)
    {      count ++;    }
    else    {      count = 0;    } 
    delay(50);
    digitalWrite(4, HIGH);
    n = 3;
  } 
  if (n == 3){
    digitalWrite(5, LOW);
    if (digitalRead(8) == HIGH && digitalRead(9) == HIGH && digitalRead(10) == HIGH && digitalRead(11) ==  LOW)
    {      count ++;    }
    else    {      count = 0;    } 
    delay(50);
    digitalWrite(5, HIGH);
    n = 0;
  } 
  if (count > 20 && t > 0) //waiting time before success, t = count * 50ms
  {
    count = 70;
//    Serial.println("Success!");
//    digitalWrite(13,HIGH);
    matrix.drawColon(false);
    stat = 1;
    t = password;
  }

  uint16_t blinkcounter = 0;
  matrix.writeDigitNum(0, (t / 1000));
  matrix.writeDigitNum(1, (t / 100) % 10);
  matrix.writeDigitNum(3, (t / 10) % 10);
  matrix.writeDigitNum(4, t % 10);
  matrix.writeDisplay();
  if (stat == 0){
    matrix.drawColon(true);
    t = t0 - millis() / 1000;
    if(t % 100 > 59){
      t0 = t0 - 40;
      t = t - 40;
    }
    if(t < 0){
      t = 0;
    }
  }
}
