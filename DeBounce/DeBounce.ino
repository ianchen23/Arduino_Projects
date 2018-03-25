int lastButtonState = LOW;
int buttonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;
const buttonPin = 13;

void setup() {
  // put your setup code here, to run once:

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
        ledState = !ledState;
      }
    }
  }
  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}
