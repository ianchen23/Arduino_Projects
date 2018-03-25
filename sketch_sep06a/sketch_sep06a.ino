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
const int a=4;

void setup() {
  for(int pin=a;pin<a+8;pin++){
    pinMode(pin,OUTPUT);
  }
  digitalWrite(a+7,LOW);
}

void loop() {
if(digitalRead(keyPin)==HIGH)
{
  digitalWrite(ledPin,HIGH);
}
else
{
  digitalWrite(ledPin,LOW);
}
}

void 7Write(int digit){
  for (int i=0;i<7;i++){
    digitalWrite(i+a,seven_seg_digits[digit][i]);
  }
}
