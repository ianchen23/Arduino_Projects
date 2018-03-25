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
int yellowValue = HIGH;
int redValue = HIGH;
int blueValue = HIGH;
int whiteValue = HIGH;
int yellowNo = 0;
int redNo = 0;
int blueNo = 0;
int whiteNo = 0;
int ifPlayed = 0;

#include "Wire.h" // Enable this line if using Arduino Uno, Mega, etc.
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include <SPI.h>           // SPI library
#include <SdFat.h>         // SDFat Library
#include <SdFatUtil.h>     // SDFat Util Library
#include <SFEMP3Shield.h>  // Mp3 Shield Library

Adafruit_7segment matrix = Adafruit_7segment();
int t0 = 500;
int t=t0;

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
  matrix.begin(0x70);
  initSD();  // Initialize the SD card
  initMP3Player(); // Initialize the MP3 Shield
  uint8_t result = MP3player.playTrack(1);
}

void loop() {
  yellowValue = digitalRead(yellow);
  redValue = digitalRead(red);
  blueValue = digitalRead(blue);
  whiteValue = digitalRead(white);
  if (yellowValue == HIGH && yellowNo == 0){
    yellowNo = 1;
    if (redNo==0||blueNo==0||whiteNo==0){
      t=-1;
/*      if(ifPlayed==0){
        uint8_t result = MP3player.playTrack(3);
        ifPlayed=1;
      }*/
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
  if(yellowNo==0){
    t=t0-millis()/100;
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
