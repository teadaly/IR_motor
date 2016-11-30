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

//our test variable
int PROXIMITY; //from 0 (close) to 1023 (far)


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

  uint8_t SPEED = 200;  //default speed
  int DURATION = 2000;  //default duration

 
}

void loop() {

  PROXIMITY = analogRead(2); //read value from analog pin 2
  Serial.println(PROXIMITY); //print the value on the screen
  
  if(PROXIMITY < 500) { //if someone is close

     SPEED = 255;
     DURATION = 1000;
  }
  
  else { //if no one is close
    
    SPEED = 200;
    DURATION = 2000;

  }
  
  motorOne->setSpeed(SPEED);
  delay(DURATION);
  motorOne->run(RELEASE);
  
  motorTwo->setSpeed(SPEED);
  delay(DURATION);
  motorOne->run(RELEASE);
}


