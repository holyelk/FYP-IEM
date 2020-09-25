/* Me_Arm_Servo_Calibration_V1
 * by Robo Pi
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define FREQUENCY             50 // Variables for the PCA9685 board

// The PCA9685 board I2C address is 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40); 

String str_input = ""; // Used for Serial input from monitor
int int_Char; // Used for Serial input
int base_angle; //  Base angle
int u_arm_angle; //  Upper arm angle 
int l_arm_angle; // Lower arm angle
int claw_angle; // Claw angle

// Servo PCA9685 board pins
int servo_pin;
int base = 0; 
int u_arm = 1; 
int l_arm = 2; 
int claw = 3;

void setup() 
{ 
  Serial.begin(9600); // Use Serial monitor 
  pwm.begin(); // start Adafruit object
  pwm.setPWMFreq(FREQUENCY); // set frequency
} 
 
void loop() 
{ 
  Serial.println("Enter 0, 1, 2, or 3 for Base, U_arm, L_arm or Claw"); 
  while (Serial.available() == 0){} // wait for input
  str_input = Serial.readString(); 
    //  Add input rrror checking routine here ~~~ To be done later ~~~
  servo_pin = str_input.toInt();
  move_Arm(servo_pin);       
}

void move_Arm(int motorOut)
{
  int pulse_width = 300;
  while(true)
  {
      Serial.println("Enter 1 or 2 to inc or dec angle, or 3 to end");
      while (Serial.available() == 0){} // wait for input
      str_input = Serial.readString();
      int_Char = str_input.substring(0,1).toInt();
      //Serial.println(int_Char,DEC); 

    switch (int_Char)
    {
      case 1: 
        pulse_width = pulse_width - 10;
        Serial.print("Pulse Width = ");
        Serial.println(pulse_width,DEC);
        pwm.setPWM(motorOut, 0, pulse_width);
        break;
      case 2: 
        pulse_width = pulse_width + 10;
        Serial.print("Pulse Width = ");
        Serial.println(pulse_width,DEC);
        pwm.setPWM(motorOut, 0, pulse_width);
        break;
      case 3: 
        return;    
      }
    }
  }
