# Automated-River-Cleaning-Robot
The Automatic River-Cleaning Robot uses ultrasonic sensors for obstacle detection and garbage monitoring, a conveyor belt to collect waste, and motors for autonomous navigation. It avoids collisions, adjusts movements, and stops the conveyor when the bin is full, ensuring efficient and eco-friendly river cleaning.

Key Features
Sonar Sensor with Servo: Sweeps to detect obstacles and objects.
Garbage Level Detection: Uses a separate sonar sensor to detect when the garbage bin is full.
Movement Control: Motors control forward, backward, and turning movements.
Conveyor Belt System: Runs when the garbage bin is not full.
Component Initialization
Libraries Used:

Servo.h: Controls the servo motor for the sonar sensor.
AFMotor.h: Controls the motors using Adafruit Motor Shield.
NewPing.h: Handles ultrasonic distance measurement.
Defined Pins:

TRIG_PIN and ECHO_PIN: Ultrasonic sensor for obstacle detection.
GARBAGE_TRIG_PIN and GARBAGE_ECHO_PIN: Ultrasonic sensor for garbage level detection.
SERVO_PIN: Servo motor for the sonar sensor.
Motors:

motorLeft and motorRight: Control the robot's movement.
conveyorMotor1 and conveyorMotor2: Run the conveyor belt.
Variables:

garbageFull: Tracks whether the garbage bin is full.
servoDirection and servoAngle: Control the sweeping motion of the sonar sensor.
Functions
1. setup()
Initializes the servo motor and sets its initial position to 90°.
Begins the serial monitor for debugging purposes.
2. loop()
Garbage Level Check:

Calls checkGarbageLevel() to measure the garbage bin level.
If the bin is full, the conveyor belt stops; otherwise, it keeps running.
Sonar Sensor Sweep:

Sweeps the servo to detect objects at different angles using sweepServo().
Measures distance using readPing().
Obstacle Detection:

If an obstacle is within 15 cm, the robot moves backward for 3 seconds and turns left.
Otherwise, it continues moving forward.
3. readPing()
Reads the sonar sensor's distance measurement.
Defaults to 250 cm if no object is detected.
4. checkGarbageLevel()
Measures garbage height using the second sonar sensor.
If the height is ≤10 cm, sets garbageFull to true (bin full); otherwise, it's false.
5. sweepServo()
Gradually sweeps the servo motor from 0° to 180° and back.
Updates the servo position every 100 ms.
6. Movement Functions
moveForward():
Runs both motors forward at max speed.
moveBackward():
Runs both motors backward at max speed for 2 seconds.
turnLeft():
Stops the left motor and runs the right motor backward for 5 seconds, then resumes forward movement.
7. Conveyor Belt Functions
runConveyorBelt():
Runs both conveyor motors forward at the defined speed.
stopConveyorBelt():
Stops both conveyor motors.
Robot Logic
Obstacle Avoidance:

The servo sweeps to detect objects.
If an obstacle is detected within 15 cm, the robot moves backward and turns left.
If no obstacle is detected, the robot moves forward.
Garbage Collection:

If the garbage bin is not full, the conveyor belt continuously runs to collect garbage.
If the bin is full, the conveyor belt stops.
Potential Improvements
Dynamic Obstacle Avoidance: Use more complex algorithms for smoother movement.
Garbage Bin Alert: Add a sound or light indicator for a full bin.
Improved Efficiency: Optimize motor delays for faster response.
This code provides basic automation for a river-cleaning robot, balancing simplicity with functionality.
