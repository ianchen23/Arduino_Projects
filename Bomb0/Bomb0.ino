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
int t = 100;

void setup() {
  Serial.begin(9600);
  pinMode(yellow,INPUT_PULLUP);
  pinMode(red,INPUT_PULLUP);
  pinMode(blue,INPUT_PULLUP);
  pinMode(white,INPUT_PULLUP);
}

void loop() {
  yellowValue = digitalRead(yellow);
  redValue = digitalRead(red);
  blueValue = digitalRead(blue);
  whiteValue = digitalRead(white);
  if (yellowValue == HIGH && yellowNo == 0){
    yellowNo = 1;
    Serial.println("Yellow");
    if (redNo==0||blueNo==0||whiteNo==0){
      Serial.println("Boom!");
    }
  }

  if (redValue == HIGH && redNo == 0){
    redNo = 1;
    Serial.println("Red");
  }  

  if (blueValue == HIGH && blueNo == 0){
    blueNo = 1;
    Serial.println("Blue");
    if (redNo==0){
      Serial.println("Wrong order!");
    }
  }  

  if (whiteValue == HIGH && whiteNo == 0){
    whiteNo = 1;
    Serial.println("White");
    if (redNo==0||blueNo==0){
      Serial.println("Wrong order!");
    }
  }
}
