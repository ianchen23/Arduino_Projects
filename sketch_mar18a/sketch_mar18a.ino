int n = 0;

  void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Good day sir!");
  pinMode(2, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (n == 0){
    digitalWrite(2, LOW);
    if (digitalRead(3) == LOW) Serial.println("OK1");
    if (digitalRead(5) == LOW) Serial.println("Wrong"); 
    if (digitalRead(7) == LOW) Serial.println("Wrong"); 
    if (digitalRead(9) == LOW) Serial.println("Wrong"); 
    delay(50);
    digitalWrite(2, HIGH);
    n = 1;
  }
  if (n == 1){
    digitalWrite(4, LOW);
    if (digitalRead(3) == LOW) Serial.println("Wrong");
    if (digitalRead(5) == LOW) Serial.println("OK2"); 
    delay(50);
    digitalWrite(4, HIGH);
    n = 0;
  }  
}
