const int segmentA = 8; // from 0 to 8
const int segmentB = 9; // from 1 to 9
const int segmentC = 12; 
const int segmentD = 3; 
const int segmentE = 13; 
const int segmentF = 11; 
const int segmentG = 2; 

const int pushInc = 7; 
const int pushR = 5; 

int count = 0; 

void setup() {
  pinMode(segmentA, OUTPUT); 
  pinMode(segmentB, OUTPUT); 
  pinMode(segmentC, OUTPUT); 
  pinMode(segmentD, OUTPUT); 
  pinMode(segmentE, OUTPUT); 
  pinMode(segmentF, OUTPUT); 
  pinMode(segmentG, OUTPUT); 
  
  pinMode(pushInc, INPUT_PULLUP); 
  pinMode(pushR, INPUT_PULLUP); 

  displayNumber(count); 
}

void loop() {
  if (digitalRead(pushInc) == LOW) {
    count++;
    if (count > 9) count = 0; 
    displayNumber(count);
    delay(250); 
  }

  if (digitalRead(pushR) == LOW) {
    count = 0;
    displayNumber(count);
    delay(250); 
  }
}

void clearDisplay() {
  digitalWrite(segmentA, LOW); 
  digitalWrite(segmentB, LOW); 
  digitalWrite(segmentC, LOW); 
  digitalWrite(segmentD, LOW); 
  digitalWrite(segmentE, LOW); 
  digitalWrite(segmentF, LOW); 
  digitalWrite(segmentG, LOW); 
}

void displayNumber(int num) {
  clearDisplay(); 

  switch (num) {
    case 0:
      digitalWrite(segmentA, HIGH); digitalWrite(segmentB, HIGH); 
      digitalWrite(segmentC, HIGH); digitalWrite(segmentD, HIGH); 
      digitalWrite(segmentE, HIGH); digitalWrite(segmentF, HIGH); 
      break;
    case 1:
      digitalWrite(segmentB, HIGH); digitalWrite(segmentC, HIGH); 
      break;
    case 2:
      digitalWrite(segmentA, HIGH); digitalWrite(segmentB, HIGH); 
      digitalWrite(segmentG, HIGH); digitalWrite(segmentE, HIGH); 
      digitalWrite(segmentD, HIGH); 
      break;
    case 3:
      digitalWrite(segmentA, HIGH); digitalWrite(segmentB, HIGH); 
      digitalWrite(segmentC, HIGH); digitalWrite(segmentD, HIGH); 
      digitalWrite(segmentG, HIGH); 
      break;
    case 4:
      digitalWrite(segmentB, HIGH); digitalWrite(segmentC, HIGH); 
      digitalWrite(segmentF, HIGH); digitalWrite(segmentG, HIGH); 
      break;
    case 5:
      digitalWrite(segmentA, HIGH); digitalWrite(segmentF, HIGH); 
      digitalWrite(segmentG, HIGH); digitalWrite(segmentC, HIGH); 
      digitalWrite(segmentD, HIGH); 
      break;
    case 6:
      digitalWrite(segmentA, HIGH); digitalWrite(segmentF, HIGH); 
      digitalWrite(segmentE, HIGH); digitalWrite(segmentC, HIGH); 
      digitalWrite(segmentD, HIGH); digitalWrite(segmentG, HIGH); 
      break;
    case 7:
      digitalWrite(segmentA, HIGH); digitalWrite(segmentB, HIGH); 
      digitalWrite(segmentC, HIGH); 
      break;
    case 8:
      digitalWrite(segmentA, HIGH); digitalWrite(segmentB, HIGH); 
      digitalWrite(segmentC, HIGH); digitalWrite(segmentD, HIGH); 
      digitalWrite(segmentE, HIGH); digitalWrite(segmentF, HIGH); 
      digitalWrite(segmentG, HIGH); 
      break;
    case 9:
      digitalWrite(segmentA, HIGH); digitalWrite(segmentB, HIGH); 
      digitalWrite(segmentC, HIGH); digitalWrite(segmentD, HIGH); 
      digitalWrite(segmentF, HIGH); digitalWrite(segmentG, HIGH); 
      break;
  }
}
