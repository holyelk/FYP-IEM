#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int inPin = 7;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(inPin, INPUT);    // declare pushbutton as input
}

void loop() {
  val = digitalRead(inPin);  // read input value
  if (val == LOW) {  //LOW is button pressed
    myservo.write(180);
  } else {
    myservo.write(0);
  }
  
}
