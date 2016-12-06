/*
This is a program to test the IR sensor WITH the motors
  
For use with the Adafruit Motor Shield v2 
---->  http://www.adafruit.com/products/1438
 */

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3 or M4. In this case, 1 and 2
Adafruit_DCMotor *motorOne = AFMS.getMotor(1);
Adafruit_DCMotor *motorTwo = AFMS.getMotor(2);

// Digital pin #2 is the same as Pin D2 see http://arduino.cc/en/Hacking/PinMapping168
#define IRpin_PIN PIND
#define IRpin 2
#define drawline delay

//our test variable
int PROXIMITY; //from 0 (near) to 1023 (far)


void setup(void) {
  Serial.begin(9600); //initialize baud rate to 9600
  Serial.println("Ready to control motors via IR");

  AFMS.begin();  //create with the default frequency 1.6KHz

  // Set M1 speed to start, from 0 (off) to 255 (max)
  motorOne->setSpeed(200);
  motorOne->run(FORWARD);
  motorOne->run(RELEASE);


  // Set M2 speed to start, from 0 (off) to 255 (max)
  motorTwo->setSpeed(255);
  motorTwo->run(FORWARD);
  motorTwo->run(RELEASE);

}

void loop() {
  
  uint8_t SPEED = 150;  //STATE 1 speed
  int LENGTH_1 = 1500;  //STATE 1 motor 1 length
  int LENGTH_2 = 2000;  //STATE 1 motor 2 length
  int STATE = 1; //State 1 (far), State 2 (near)

  PROXIMITY = analogRead(2); //read value from analog pin 2
  Serial.println(PROXIMITY); //print the value on the screen

  //Set the proximity state
  if(PROXIMITY > 200) {
    STATE = 2;
    Serial.println(STATE);
  }
  else if(PROXIMITY <= 200) {
    STATE = 1;
    Serial.println(STATE);
  }

  //Set the variables for state 2
  if(STATE == 2) { //if someone is close
     SPEED = 220;
     LENGTH_1 = 700;
     LENGTH_2 = 1000;
  }

  //Draw motorOne line (clear)
  motorOne->run(FORWARD);
  motorOne->setSpeed(SPEED);
  drawline(LENGTH_1);
  motorOne->run(RELEASE);

  //Draw motorTwo line (black)
  motorTwo->run(FORWARD);
  motorTwo->setSpeed(SPEED);
  drawline(LENGTH_2);
  motorTwo->run(RELEASE);
}


