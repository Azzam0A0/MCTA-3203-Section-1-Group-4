#include <Servo.h>

Servo myservo;      // to control a servo
int pos = 0;        // variable to store the servo position

void setup() {
  Serial.begin(9600); 
  myservo.attach(9);  // attaches the servo on pin 9
}

void loop() {
  // Check if data is available to read from Python
  if (Serial.available() > 0) {
    // Read the incoming integer
    int angle = Serial.parseInt(); 
    
    // Ensure the angle is within safe servo limits
    if (angle >= 0 && angle <= 180) {
      myservo.write(angle);
      delay(15); 
    }
  }
}
