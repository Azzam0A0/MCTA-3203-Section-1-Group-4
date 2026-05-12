#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(4, 5); // RX, TX

// --- PIN MAPPING UPDATE ---
// If Red shows Blue and Blue shows Red, we swap the pin assignments here:
const int redPin = 11;   // Changed from 9 to 11 to fix the swap
const int greenPin = 10; // Green remains the same
const int bluePin = 9;   // Changed from 11 to 9 to fix the swap

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  while (!huskylens.begin(mySerial)) {
    Serial.println(F("Begin failed! Check Protocol Settings (Serial 9600)."));
    delay(500);
  }
  Serial.println("HuskyLens Ready! Color Mapping Corrected.");
}

void setRGB(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void loop() {
  if (!huskylens.request()) {
    setRGB(0, 0, 0); 
    return;
  }

  // Check if there is a valid detection
  if (huskylens.available()) {
    bool learnedObjectFound = false;

    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();

      // Only act if the ID is 1 or higher (Learned IDs)
      if (result.command == COMMAND_RETURN_BLOCK && result.ID > 0) {
        learnedObjectFound = true;
        
        switch (result.ID) {
          case 1: // Trained as Red
            Serial.println("Detected: RED");
            setRGB(255, 0, 0); 
            break;
          case 2: // Trained as Blue
            Serial.println("Detected: BLUE");
            setRGB(0, 0, 255);
            break;
          case 3: // Trained as Green
            Serial.println("Detected: GREEN");
            setRGB(0, 255, 0);
            break;
          case 4: // Trained as Yellow
            Serial.println("Detected: YELLOW");
            setRGB(255, 255, 0);
            break;
          case 5: // Trained as Purple
            Serial.println("Detected: PURPLE");
            setRGB(255, 0, 255);
            break;
          default:
            setRGB(0, 0, 0);
            break;
        }
      }
    }

    // If only the white box (ID 0) was seen, turn LED off
    if (!learnedObjectFound) {
      setRGB(0, 0, 0);
    }

  } else {
    // No objects in view
    setRGB(0, 0, 0);
  }
}