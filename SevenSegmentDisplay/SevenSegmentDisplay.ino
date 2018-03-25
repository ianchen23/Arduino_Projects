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

void setup() {
  for(int pin=a;pin<a+8;pin++){
    pinMode(pin,OUTPUT);
  }
  digitalWrite(a+7,LOW);
}

void loop() {
  for (int t=0;t<20;t++){
    if(t>9){
      t=0;
    }
    sevenSegWrite(t);
    delay(1000);
  }
}

void sevenSegWrite(int digit){
  for (int i=0;i<7;i++){
    digitalWrite(i+a,seven_seg_digits[digit][i]);
  }
}
