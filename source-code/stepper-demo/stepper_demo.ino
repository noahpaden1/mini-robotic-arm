#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);  // initialize stepper

int potPin = A0;  // potentiometer connected to A0
int potValue = 0; // variable to store the potentiometer value
int lastPotValue = 0; // variable to store the last potentiometer value
int motorSpeed = 0; // variable to store motor speed
int minSpeed = 10; // minimum motor speed (rpm)
int maxSpeed = 100; // maximum motor speed (rpm)
int threshold = 50    ;  // minimum change in potentiometer value to move the motor

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  lastPotValue = analogRead(potPin);  // initialize lastPotValue
}

void loop() {
  // read the potentiometer value (0 to 1023):
  potValue = analogRead(potPin);
  Serial.println(potValue);

  // Calculate the difference between the current and last potentiometer values
  int potDifference = potValue - lastPotValue;

  // Only act if the change in potentiometer value is greater than the threshold:
  if (abs(potDifference) >= threshold) {
    // map the potentiometer difference to a speed range:
    motorSpeed = map(abs(potDifference), 0, 1023, minSpeed, maxSpeed);

    // set the motor speed:
    myStepper.setSpeed(motorSpeed);

    // determine the direction based on the potentiometer movement:
    if (potDifference > 0) {
      // rotate clockwise if the potentiometer value increases
      Serial.print("Clockwise, Speed: ");
      Serial.println(motorSpeed);
      myStepper.step(stepsPerRevolution / 10); // small steps to match potentiometer rotation
    }
    else if (potDifference < 0) {
      // rotate counterclockwise if the potentiometer value decreases
      Serial.print("Counterclockwise, Speed: ");
      Serial.println(motorSpeed);
      myStepper.step(-stepsPerRevolution / 10); // small steps to match potentiometer rotation
    }

    // update the last potentiometer value:
    lastPotValue = potValue;
  }

  delay(100); // small delay to avoid overly fast updates
}
