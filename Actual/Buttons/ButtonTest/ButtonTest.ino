const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(7);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
