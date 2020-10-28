#include <Wire.h>
//PCA9685 Library
#include <Adafruit_PWMServoDriver.h>
// 7 segment Library
#include <TM1637Display.h>

//PCA9685 pinout VCC->5V, GND->GND, SDA->SDA, SCL->SCL
//L/R Button pinout 7 & 8
//7 Segment pinout CLK->2 & DIO->3

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

TM1637Display display(CLK, DIO);

// servo number
uint8_t servonum[] = {0, 1};

//Pulse length for servo angle
uint16_t pulselength;

int inPin[] = {7, 8};   // choose the input pin (for a pushbutton) for servonum

int buttonVal[] = {0, 0};     // variable for reading the pin status
int numOfButtons = 2;


//7 Segment user and com scores
int user_score = 0;
int com_score = 0;



void setup() {

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

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

  refreshScore();
}

void refreshScore() {
    //Function to refresh the scoreboard
    display.showNumberDecEx(com_score, 0, false, 2, 2);
    display.showNumberDecEx(user_score, 0b01000000, false, 2, 0);
}
