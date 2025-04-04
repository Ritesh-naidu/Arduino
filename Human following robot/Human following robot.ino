#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

#define LEFT A5
#define RIGHT A1
#define TRIGGER_PIN A2
#define ECHO_PIN A3
#define MAX_DISTANCE 200

// Right IR sensor connected to analog pin A2 of Arduino Uno:
// Left IR sensor connected to analog pin A3 of Arduino Uno:
// Trigger pin connected to analog pin A1 of Arduino Uno:
// Echo pin connected to analog pin A0 of Arduino Uno:
// Maximum ping distance:

unsigned int distance = 0;        // Variable to store ultrasonic sensor distance:
unsigned int Right_Value = 0;     // Variable to store Right IR sensor value:
unsigned int Left_Value = 0;      // Variable to store Left IR sensor value:
int d = 10;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and max distance

// Create motor objects
AF_DCMotor Motor1(1, MOTOR12_1KHZ);
AF_DCMotor Motor2(2, MOTOR12_1KHZ);
AF_DCMotor Motor3(3, MOTOR34_1KHZ);
AF_DCMotor Motor4(4, MOTOR34_1KHZ);

Servo myservo;   // Create servo object to control the servo
int pos = 0;     // Variable to store the servo position

void setup() {
  Serial.begin(9600);         // Initialize serial communication at 9600 bps
  myservo.attach(10);         // Servo attached to pin 10 of Arduino UNO

  for (pos = 90; pos <= 180; pos += 1) {
    myservo.write(pos);       // Move from 90 to 180 degrees
    delay(15);                // Wait 15ms for the servo to reach the position
  }

  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);       // Move from 180 to 0 degrees
    delay(15);
  }

  for (pos = 0; pos <= 90; pos += 1) {
    myservo.write(pos);       // Move from 0 to 90 degrees
    delay(15);
  }

  pinMode(RIGHT, INPUT);      // Set analog pin RIGHT as input
  pinMode(LEFT, INPUT);       // Set analog pin LEFT as input

  stop();
}

// the loop function runs forever
void loop() {
  delay(50);                                      // Wait 50ms between pings
  distance = sonar.ping_cm();                     // Get distance in cm
  Serial.print("distance");
  Serial.println(distance);                       // Print distance

  Right_Value = !digitalRead(RIGHT);              // Read Right IR sensor
  Left_Value = !digitalRead(LEFT);                // Read Left IR sensor

  Serial.print("RIGHT");
  Serial.println(Right_Value);
  Serial.print("LEFT");
  Serial.println(Left_Value);

  if ((distance > 1) && (distance < d)) {
    // Move Forward
    Motor1.setSpeed(130);
    Motor1.run(FORWARD);
    Motor2.setSpeed(130);
    Motor2.run(FORWARD);
    Motor3.setSpeed(130);
    Motor3.run(FORWARD);
    Motor4.setSpeed(130);
    Motor4.run(FORWARD);
  }
  else if ((Right_Value == 1) && (Left_Value == 0)) {
    // Turn Right
    Motor1.setSpeed(150);
    Motor1.run(FORWARD);
    Motor2.setSpeed(150);
    Motor2.run(FORWARD);
    Motor3.setSpeed(150);
    Motor3.run(BACKWARD);
    Motor4.setSpeed(150);
    Motor4.run(BACKWARD);
    delay(150);
  }
  else if ((Right_Value == 0) && (Left_Value == 1)) {
    // Turn Left
    Motor1.setSpeed(150);
    Motor1.run(BACKWARD);
    Motor2.setSpeed(150);
    Motor2.run(BACKWARD);
    Motor3.setSpeed(150);
    Motor3.run(FORWARD);
    Motor4.setSpeed(150);
    Motor4.run(FORWARD);
    delay(150);
  }
  else if (distance > d) {
    stop();
  }
}

void stop() {
  // Stop
  Motor1.setSpeed(0);
  Motor1.run(RELEASE);
  Motor2.setSpeed(0);
  Motor2.run(RELEASE);
  Motor3.setSpeed(0);
  Motor3.run(RELEASE);
  Motor4.setSpeed(0);
  Motor4.run(RELEASE);
}
