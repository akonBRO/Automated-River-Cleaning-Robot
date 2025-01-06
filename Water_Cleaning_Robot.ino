#include <Servo.h>
#include <AFMotor.h>
#include <NewPing.h>

Servo sonarServo; // Servo for sonar sensor
#define SERVO_PIN 9 // Servo connected to motor shield's servo connector
#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
#define MAX_SPEED 255 // Maximum speed for motors

#define GARBAGE_TRIG_PIN A2
#define GARBAGE_ECHO_PIN A3
#define CONVEYOR_SPEED 200



NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing garbageSonar(GARBAGE_TRIG_PIN, GARBAGE_ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motorLeft(1, MOTOR12_1KHZ); // Left motor
AF_DCMotor motorRight(2, MOTOR12_1KHZ); // Right motor
AF_DCMotor conveyorMotor1(3, MOTOR12_1KHZ); // Conveyor motor 1
AF_DCMotor conveyorMotor2(4, MOTOR12_1KHZ); // Conveyor motor 2

bool garbageFull = false; // Flag for garbage full status
int servoDirection = 1; // Servo sweep direction (1 for right, -1 for left)
int servoAngle = 90; // Initial angle

void setup() {
  Serial.begin(9600); // For debugging if needed
  sonarServo.attach(SERVO_PIN); // Attach to the correct servo pin
  sonarServo.write(servoAngle); // Set initial angle
}

void loop() {
  checkGarbageLevel();

  sweepServo();
  int distance = readPing();

  if (distance <= 15) { // Object detected
    moveBackward();
    delay(3000); // Move backward for 3 seconds
    turnLeft();
  } else {
    moveForward();
  }

  if (!garbageFull) {
    runConveyorBelt();
  } else {
    stopConveyorBelt();
  }
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250; // Default to maximum distance if no object is detected
  }
  return cm;
}

void checkGarbageLevel() {
  delay(5000); // Delay for garbage sonar sensor
  int garbageHeight = garbageSonar.ping_cm();
  if (garbageHeight > 0 && garbageHeight <= 10) { // Adjust threshold as per requirement
    garbageFull = true; // Garbage bin is full
  } else if (garbageHeight > 10) {
    garbageFull = false; // Garbage bin is emptied
  }
}

void sweepServo() {
  servoAngle += servoDirection * 5; // Increment or decrement angle
  if (servoAngle >= 180 || servoAngle <= 0) {
    servoDirection = -servoDirection; // Change direction
  }
  sonarServo.write(servoAngle); // Move the servo to the new angle
  delay(100); // Adjust sweep speed
}

void moveForward() {
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
  motorLeft.setSpeed(MAX_SPEED);
  motorRight.setSpeed(MAX_SPEED);
}

void moveBackward() {
  motorLeft.run(BACKWARD);
  motorRight.run(BACKWARD);
  motorLeft.setSpeed(MAX_SPEED);
  motorRight.setSpeed(MAX_SPEED);
  delay(2000);
}

void turnLeft() {
  motorLeft.run(RELEASE); // Stop the left motor
  motorRight.run(BACKWARD); // Right motor moves forward
  motorRight.setSpeed(MAX_SPEED);
  delay(5000); // Adjust for turning duration
  moveForward(); // Resume forward movement
}

void runConveyorBelt() {
  conveyorMotor1.run(FORWARD);
  conveyorMotor2.run(FORWARD);
  conveyorMotor1.setSpeed(CONVEYOR_SPEED);
  conveyorMotor2.setSpeed(CONVEYOR_SPEED);
}

void stopConveyorBelt() {
  conveyorMotor1.run(RELEASE);
  conveyorMotor2.run(RELEASE);
}