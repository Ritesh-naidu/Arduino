
//Include the servo motor library
#include <Servo.h>
//Define the LDR sensor pins
#define LDR1 A0
#define LDR2 A1
//Define the error value. You can change it as you like
#define error 0
int led = 5;
//Starting point of the servo motor
int Spoint =  90;
//Create an object for the servo motor
Servo servo;

void setup() {
//Include servo motor PWM pin
  servo.attach(9);
  Serial.begin(9600);
  pinMode(led,OUTPUT);
//Set the starting point of the servo
  servo.write(Spoint);

}

void loop() {
//Get the LDR sensor value
  int ldr1 = analogRead(LDR1);
//Get the LDR sensor value
  int ldr2 = analogRead(LDR2);
//Get the difference of these values
  int value1 = abs(ldr1 - ldr2);
  int value2 = abs(ldr2 - ldr1);
   Serial.print(ldr1);
    Serial.print("   ");
   Serial.println(ldr2);

//Check these values using a IF condition
  if ((value1 <= error) || (value2 <= error)) {
    digitalWrite(led,HIGH);
    
  } 
  else {
  if (ldr1 > ldr2) {
    // Decrease Spoint, but ensure it doesn't go below 0
    Spoint = max(0, Spoint - 1);
    Serial.println(Spoint);
    Serial.println("less than 90");
    digitalWrite(led, LOW);
}

if (ldr1 < ldr2) {
    // Increase Spoint, but ensure it doesn't go above 180
    Spoint = min(180, Spoint + 1);
    Serial.println(Spoint);
    Serial.println("greater than 90");
    digitalWrite(led, LOW);
}

  }
//Write values on the servo motor
  servo.write(Spoint);
  delay(80);
}