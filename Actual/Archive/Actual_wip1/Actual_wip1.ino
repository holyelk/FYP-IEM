#include <Wire.h>
//PCA9685 Library
#include <Adafruit_PWMServoDriver.h>
// 7 segment Library
#include <TM1637Display.h>
//HuskyLens library
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
//Debounce library
#include <Button.h>
//non blocking Delay library
#include <avdweb_VirtualDelay.h>

//PCA9685 pinout VCC->5V, GND->GND, SDA->SDA, SCL->SCL
//L/R Button pinout 6 & 5
//Launch button pinout 4
//Reset score button pinout 22
//7 Segment pinout CLK->2 & DIO->3
//Score counter pinout human_counter->10 & com_counter->11
//HUSKYLENS green line >> Pin 51; blue line >> Pin 49

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  560 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

//7 segment
#define CLK 2
#define DIO 3

//Score counter sensor
#define human_counter 10
#define com_counter 11

TM1637Display display(CLK, DIO);

HUSKYLENS huskylens;
SoftwareSerial mySerial(51, 49); // RX, TX
void printResult(HUSKYLENSResult result);

// servo number
uint8_t servonum[] = {0, 1, 4};

//Pulse length for servo angle
uint16_t pulselength;

int inPin[] = {5, 6};   // choose the input pin (for a pushbutton) for servonum

int buttonVal[] = {0, 0};     // variable for reading the pin status
int numOfButtons = 2;

Button buttonLaunch(4); // Connect your button between pin 4 and GND


//7 Segment user and com scores
int user_score = 0;
int com_score = 0;

VirtualDelay singleDelay;

void setup() {

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  //initialize huskylens serial protocol
  Serial.begin(9600);
  mySerial.begin(9600);

  //Initialize 7 Segment
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  display.setBrightness(4, true);
  display.clear();

  //initialize buttons and internal resistor. One side to ground. other to pin
  pinMode(inPin[0], INPUT);
  digitalWrite(inPin[0], HIGH);
  pinMode(inPin[1], INPUT);
  digitalWrite(inPin[1], HIGH);
  pinMode(inPin[2], INPUT);
  digitalWrite(inPin[2], HIGH);

  //initialize score counter pins
  pinMode(12, INPUT);
  pinMode(11, INPUT);

  //Initialize debounce
  buttonLaunch.begin();

  //Set score to be 0:0
  refreshScore();

  delay(10);
}

void loop() {

  //loop through all buttons to see if pressed
  for (int thisButton = 0; thisButton < numOfButtons; thisButton++) {
    buttonVal[thisButton] = digitalRead(inPin[thisButton]);  // read input value

    switch (thisButton) {
      case 0:
        if (buttonVal[thisButton] == LOW) {  //LOW is button pressed
          pulselength = map(150, 0, 180, SERVOMIN, SERVOMAX);
          pwm.setPWM(servonum[thisButton], 0, pulselength);
        } else {
          pulselength = map(90, 0, 180, SERVOMIN, SERVOMAX);
          pwm.setPWM(servonum[thisButton], 0, pulselength);
        }
        break;

      case 1:
        if (buttonVal[thisButton] == LOW) {  //LOW is button pressed
          pulselength = map(20, 0, 180, SERVOMIN, SERVOMAX);
          pwm.setPWM(servonum[thisButton], 0, pulselength);
        } else {
          pulselength = map(80, 0, 180, SERVOMIN, SERVOMAX);
          pwm.setPWM(servonum[thisButton], 0, pulselength);
        }
        break;

    }
  }

  if (buttonLaunch.pressed()) {
    Serial.println("Button 1 pressed");
    launchBall();
  }

  scoreCounter();

  if (huskylens.available())
  {
    HUSKYLENSResult result = huskylens.read();
    printResult(result);
  }

  if(singleDelay.elapsed()) {
    pulselength = map(142, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servonum[2], 0, pulselength);
  }


}

void launchBall() {


  //148,90
  //for(int degreeVal = 148; degreeVal > 90; degreeVal--){
  pulselength = map(90, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(servonum[2], 0, pulselength);
  singleDelay.start(1000);
  //Serial.println("degreeVal");


  //}

}

void refreshScore() {
  //Function to refresh the scoreboard
  display.showNumberDecEx(com_score, 0, false, 2, 2);
  display.showNumberDecEx(user_score, 0b01000000, false, 2, 0);
}

void scoreCounter() {
  if (digitalRead(human_counter) == LOW) {
    user_score++;
    refreshScore();
    delay(1000);
  }
  if (digitalRead(com_counter) == LOW) {
    com_score++;
    refreshScore();
    delay(1000);
  }

  //Reset launcher
  //pulselength = map(148, 0, 180, SERVOMIN, SERVOMAX);
  //pwm.setPWM(servonum[2], 0, pulselength);
  //Serial.println("reset");
}

void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  }
  else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
  }
  else {
    Serial.println("Object unknown!");
  }
}
