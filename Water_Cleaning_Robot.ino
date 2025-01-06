#include <Servo.h>
#include <AFMotor.h>
#include <NewPing.h>

Servo sonarServo; 
#define SERVO_PIN 9 
#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
#define MAX_SPEED 255 

#define GARBAGE_TRIG_PIN A2
#define GARBAGE_ECHO_PIN A3
#define CONVEYOR_SPEED 200



NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing garbageSonar(GARBAGE_TRIG_PIN, GARBAGE_ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motorLeft(1, MOTOR12_1KHZ); 
AF_DCMotor motorRight(2, MOTOR12_1KHZ);
AF_DCMotor conveyorMotor1(3, MOTOR12_1KHZ); 
AF_DCMotor conveyorMotor2(4, MOTOR12_1KHZ); 

bool garbageFull = false; 
int servoDirection = 1; 
int servoAngle = 90;

void setup() {
  Serial.begin(9600); 
  sonarServo.attach(SERVO_PIN); 
  sonarServo.write(servoAngle); 
}

void loop() {
  checkGarbageLevel();

  sweepServo();
  int distance = readPing();

  if (distance <= 15) { 
    moveBackward();
    delay(3000);
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
    cm = 250; 
  }
  return cm;
}

void checkGarbageLevel() {
  delay(5000);
  int garbageHeight = garbageSonar.ping_cm();
  if (garbageHeight > 0 && garbageHeight <= 10) { 
    garbageFull = true; 
  } else if (garbageHeight > 10) {
    garbageFull = false;
  }
}

void sweepServo() {
  servoAngle += servoDirection * 5;
  if (servoAngle >= 180 || servoAngle <= 0) {
    servoDirection = -servoDirection; 
  }
  sonarServo.write(servoAngle); 
  delay(100); 
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
  motorLeft.run(RELEASE);
  motorRight.run(BACKWARD); 
  motorRight.setSpeed(MAX_SPEED);
  delay(5000); 
  moveForward();
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
