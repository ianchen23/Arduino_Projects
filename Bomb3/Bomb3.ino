/******************************************************
 * Segment display connections:
 * PIN IO: short to PIN +
 * PIN +: 5v
 * PIN -: GND
 * PIN D: A4
 * PIN C: A5
 ******************************************************/

const int yellow=14; //connect to ground
const int red=15; //connect to ground
const int blue=16; //connect to ground
const int white=17; //connect to ground
const int triggerPin=0; //connect to ground through triggers (usb ports)
const int powerPin1=5; //connect to ground through power strip
const int powerPin2=10; //connect to relay
int yellowValue = HIGH;
int redValue = HIGH;
int blueValue = HIGH;
int whiteValue = HIGH;
int yellowNo = 1;
int redNo = 0;
int blueNo = 0;
int whiteNo = 0;
int ifPlayed = 0;
int ifDelayed = 1;
int lasttriggerPin = HIGH;

#include "Wire.h" // Enable this line if using Arduino Uno, Mega, etc.
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();
unsigned long t0=500;
long t = 0;

#include <SPI.h>           // SPI library
#include <SdFat.h>         // SDFat Library
#include <SdFatUtil.h>     // SDFat Util Library
#include <SFEMP3Shield.h>  // Mp3 Shield Library

SdFat sd; // Create object to handle SD functions

SFEMP3Shield MP3player; 
const uint8_t volume = 0; // MP3 Player volume 0=max, 255=lowest (off)
const uint16_t monoMode = 1;  // Mono setting 0=off, 3=max

void setup() {
  Serial.begin(9600);
  pinMode(yellow,INPUT_PULLUP);
  pinMode(red,INPUT_PULLUP);
  pinMode(blue,INPUT_PULLUP);
  pinMode(white,INPUT_PULLUP);
  pinMode(triggerPin,INPUT_PULLUP);
  pinMode(powerPin1,OUTPUT);
  pinMode(powerPin2,OUTPUT);
  digitalWrite(powerPin1,LOW);
  digitalWrite(powerPin2,LOW);
  matrix.begin(0x70);
  initSD();  // Initialize the SD card
  initMP3Player(); // Initialize the MP3 Shield
}

void loop() {
  digitalWrite(powerPin2,LOW);
  if (digitalRead(triggerPin) == LOW && lasttriggerPin==HIGH && yellowNo==1) {
    digitalWrite(powerPin1,HIGH);
    ifDelayed=0;
    t0=millis()/1000+500;
    yellowNo=0;
    redNo=0;
    blueNo=0;
    whiteNo=0;
    ifPlayed=0;
    uint8_t result = MP3player.playTrack(1);
  }
  lasttriggerPin=digitalRead(triggerPin);
  
  yellowValue = digitalRead(yellow);
  redValue = digitalRead(red);
  blueValue = digitalRead(blue);
  whiteValue = digitalRead(white);
  if (yellowValue == HIGH && yellowNo == 0){
    yellowNo = 1;
    if (redNo==0||blueNo==0||whiteNo==0){
      t=-1;
    }
    else {
      uint8_t result = MP3player.playTrack(2);
    }
  }

  if (redValue == HIGH && redNo == 0){
    redNo = 1;
  }  

  if (blueValue == HIGH && blueNo == 0){
    blueNo = 1;
    if (redNo==0){
      t0=t0-100;
      uint8_t result = MP3player.playTrack(4);
    }
  }  

  if (whiteValue == HIGH && whiteNo == 0){
    whiteNo = 1;
    if (redNo==0||blueNo==0){
      t0=t0-100;
      uint8_t result = MP3player.playTrack(4);
    }
  }
  if(t<0){
    if(ifPlayed==0){
      uint8_t result = MP3player.playTrack(3);
      ifPlayed=1;
    }
    yellowNo=1;
    t=0;
  }
  uint16_t blinkcounter = 0;
  matrix.writeDigitNum(0, (t / 1000));
  matrix.writeDigitNum(1, (t / 100) % 10);
  matrix.drawColon(true);
  matrix.writeDigitNum(3, (t / 10) % 10);
  matrix.writeDigitNum(4, t % 10);
  matrix.writeDisplay();
 // Serial.println(t);
  if(yellowNo==0){
    t=t0-millis()/1000;
  }
  else{
    if(ifDelayed==0){
      delay(5000);
      digitalWrite(powerPin2,HIGH);
//      Serial.println(ifDelayed);
      delay(120000);
      ifDelayed=1;
      digitalWrite(powerPin1,LOW);
      digitalWrite(powerPin2,LOW);
    }
  }
  if(t%100>59){
    t0=t0-40;
  }
}

void initSD()
{
  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) 
    sd.initErrorHalt();
  if(!sd.chdir("/")) 
    sd.errorHalt("sd.chdir");
}

void initMP3Player()
{
  uint8_t result = MP3player.begin(); // init the mp3 player shield
  if(result != 0) // check result, see readme for error codes.
  {
    // Error checking can go here!
  }
  MP3player.setVolume(volume, volume);
  MP3player.setMonoMode(monoMode);
}
