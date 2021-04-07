int motor2pin1 = 2;
int motor2pin2 = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(10, OUTPUT);

  analogWrite (10, 0);
}

void loop() {
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  speedup();
  delay(3000);
  slowdown();
  
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  speedup();
  delay(3000);
  slowdown();
}

void slowdown() {
  for (int i = 80; i >= 0; i --) {
    analogWrite (10, i);
    delay (10);
  }
  delay(100);
  //Controlling speed (0 = off and 255 = max speed):
  //160 is stall at 5v
  //80 is stall at 9v
}

void speedup() {
  for (int i = 0; i <= 80; i ++) {
    analogWrite (10, i);
    delay (10);
  }
  delay(100);
  //Controlling speed (0 = off and 255 = max speed):
  //160 is stall at 5v
  //80 is stall at 9v

}
