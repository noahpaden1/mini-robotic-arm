// Libraries Included
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Stepper.h>

// Servo control parameters
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // Initializes PWN motor driver (PCA-9685)
#define SERVOMIN 99   // Min pulse length 
#define SERVOMAX 500  // Max pulse length

// Stepper motor settings
const int stepsPerRevolution = 200;  // Steps per revolution for the stepper motor
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);  // Initialize stepper motor with pins 8, 9, 10, and 11

// Stepper motor control
int stepperPotPin = A0;  // Potentiometer connected to A0 for stepper motor control
int stepperPotValue = 0; // Stores the potentiometer value for the stepper motor
int lastPotValue = 0;    // Stores the last potentiometer value
int motorSpeed = 0;      // Stores motor speed
int minSpeed = 10;       // Minimum motor speed 
int maxSpeed = 100;      // Maximum motor speed 
int threshold = 50;      // Threshold to cancel out any noise for stepper motor

void setup() {
  // Servo setup
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  

  // Stepper motor setup
  lastPotValue = analogRead(stepperPotPin);  
  delay(10);  // Small delay so servos can boot up
}

void loop() {
  // Potentiometer values for servos
  int pot1 = analogRead(A2);  
  int pot2 = analogRead(A3);  
  int pot3 = analogRead(A6);  
  int pot4 = analogRead(A1);  

  // Potentiometer values to servo pulse length
  int servo1Pos = map(pot1, 0, 1023, SERVOMIN, SERVOMAX);  
  int servo2Pos = map(pot2, 0, 1023, SERVOMIN, SERVOMAX);  
  int servo3Pos = map(pot3, 0, 1023, SERVOMIN, SERVOMAX);  
  int servo4Pos = map(pot4, 0, 1023, SERVOMIN, SERVOMAX);  

  // Intializes PWM signal for the servos
  pwm.setPWM(0, 0, servo1Pos);  
  pwm.setPWM(1, 0, servo2Pos);  
  pwm.setPWM(2, 0, servo3Pos);  
  pwm.setPWM(3, 0, servo4Pos);  

  // Stepper motor control
  stepperPotValue = analogRead(stepperPotPin);  // Read the potentiometer for the stepper motor
  int potDifference = stepperPotValue - lastPotValue;  // Find difference from last value

  // If statement that checks threshold (Used for removing noise from potentiameter)
  if (abs(potDifference) >= threshold) {  
    motorSpeed = map(abs(potDifference), 0, 1023, minSpeed, maxSpeed);  // Retrieving pot difference to motor speed
    myStepper.setSpeed(motorSpeed);  // Seting motor speed

    // These if/if-else statements build off of previous if and determine if stepper goes clockwise or counter clockwise
    if (potDifference > 0) { 
      Serial.print("Clockwise, Speed: ");
      Serial.println(motorSpeed);
      myStepper.step(stepsPerRevolution / 10);  
    } else if (potDifference < 0) {
      Serial.print("Counterclockwise, Speed: ");
      Serial.println(motorSpeed);
      myStepper.step(-stepsPerRevolution / 10);  
    }

    lastPotValue = stepperPotValue;  // Updates variable that tracks previous pot value to current 
  }

  // This delay removes any type of overlay that could confuse and mess up smooth turns for stepper
  delay(100);
}
