#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Constants for the servo pulse widths
#define SERVOMIN 99   // Minimum pulse length out of 4096
#define SERVOMAX 500  // Maximum pulse length out of 4096

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz

  delay(10);  // Wait for servos to get ready
}

void loop() {
  // Read the potentiometer values
  int pot1 = analogRead(A2);  // Potentiometer connected to A2
  int pot2 = analogRead(A3);  // Potentiometer connected to A3
  int pot3 = analogRead(A6);  // Potentiometer connected to A6 (changed from A0)
  int pot4 = analogRead(A1);  // Potentiometer connected to A1

  // Map the potentiometer values to servo pulse width
  int servo1Pos = map(pot1, 0, 1023, SERVOMIN, SERVOMAX);  // For Servo 1 (Channel 0)
  int servo2Pos = map(pot2, 0, 1023, SERVOMIN, SERVOMAX);  // For Servo 2 (Channel 1)
  int servo3Pos = map(pot3, 0, 1023, SERVOMIN, SERVOMAX);  // For Servo 3 (Channel 2)
  int servo4Pos = map(pot4, 0, 1023, SERVOMIN, SERVOMAX);  // For Servo 4 (Channel 3)

  // Set the PWM signal for the servos
  pwm.setPWM(0, 0, servo1Pos);  // Control Servo 1 (Channel 0)
  pwm.setPWM(1, 0, servo2Pos);  // Control Servo 2 (Channel 1)
  pwm.setPWM(2, 0, servo3Pos);  // Control Servo 3 (Channel 2)
  pwm.setPWM(3, 0, servo4Pos);  // Control Servo 4 (Channel 3)

  // Add a short delay
  delay(20);
}
