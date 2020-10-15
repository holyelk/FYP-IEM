void setup() {
  // put your setup code here, to run once:
   pinMode(12, INPUT);
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (digitalRead(12) == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

}
