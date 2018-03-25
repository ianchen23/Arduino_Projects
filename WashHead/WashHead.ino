int lastButtonState = LOW;
int buttonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;
int seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                { 0,1,1,0,0,0,0 },  // = 1
                                { 1,1,0,1,1,0,1 },  // = 2
                                { 1,1,1,1,0,0,1 },  // = 3
                                { 0,1,1,0,0,1,1 },  // = 4
                                { 1,0,1,1,0,1,1 },  // = 5
                                { 1,0,1,1,1,1,1 },  // = 6
                                { 1,1,1,0,0,0,0 },  // = 7
                                { 1,1,1,1,1,1,1 },  // = 8
                                { 1,1,1,0,0,1,1 }   // = 9
                               };
const int a=4; // OUTPUT PIN for segment a; all OUTPUT PINs need to be in order (e.g. 4-11)
const int buttonPin=13;
unsigned long t=0;

void setup() {
  for(int pin=a;pin<a+8;pin++){
    pinMode(pin,OUTPUT);
  }
  digitalWrite(a+7,LOW);
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
     lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
     if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        t=millis();
      }
    }
  }
  sevenSegWrite(((millis()-t)/1000)%10);
  lastButtonState = reading;
}

void sevenSegWrite(int digit){
  for (int i=0;i<7;i++){
    digitalWrite(i+a,seven_seg_digits[digit][i]);
  }
}
