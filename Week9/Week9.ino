#include "BluetoothSerial.h"
#include <ESP32Servo.h>

BluetoothSerial SerialBT; 
Servo myServo;

// Hardware Pins
const int potpin = 34;    // Potentiometer on GPIO 34 [cite: 33]
const int LED = 12;       // Built-in LED on GPIO 2 [cite: 34]
const int servoPin = 13;  // Servo Signal on GPIO 18 [cite: 66]

// Variables
int potValue = 0; 
char command; 

void setup() {
  Serial.begin(9600);
  
  // --- THIS IS YOUR BLUETOOTH SSID ---
  SerialBT.begin("Group_4"); 
  
  pinMode(LED, OUTPUT); 
  myServo.attach(servoPin); 
  myServo.write(0);         
  
  Serial.println("Bluetooth initialized... Ready to receive commands.");
}

void loop() {
  // 1. Read the Potentiometer (Sensor)
  potValue = analogRead(potpin);

  // 2. Send Potentiometer value to Smartphone Terminal
  SerialBT.print("Sensor Value: "); 
  SerialBT.println(potValue);

  // 3. Check for Bluetooth Commands [cite: 46]
  if (SerialBT.available()) {
    command = SerialBT.read();
    
    Serial.print("Command received: "); 
    Serial.println(command);

    // Control LED and Servo based on commands [cite: 51]
    switch (command) {
      case 'O': // Turn LED ON [cite: 53]
        digitalWrite(LED, HIGH); 
        SerialBT.println("LED is ON");
        break;
      case 'F': // Turn LED OFF [cite: 55]
        digitalWrite(LED, LOW); 
        SerialBT.println("LED is OFF");
        break;
      case 'S': // Move Servo to 90 degrees 
        myServo.write(90);
        SerialBT.println("Servo moved to 90");
        break;
      case 'R': // Reset Servo to 0 degrees 
        myServo.write(0);
        SerialBT.println("Servo reset to 0");
        break;
    }
  }

  delay(1000); // Send data every second [cite: 62]
}