#include <Servo.h>

Servo wasteServo;

const int trigPin = 12;
const int echoPin = 11;
const int moisturePin = A0; 
const int servoPin = 8; 

const int wetWasteThreshold = 600; 
const int ultrasonicDistanceCM = 15; 

const int neutralPosition = 90; 
const int wetWastePosition = 160;
const int dryWastePosition = 20;

enum State { IDLE, SORTING, RESETTING };
State currentState = IDLE;

unsigned long sortingStartTime = 0;
const unsigned long sortingHoldTime = 3000; 
const unsigned long resetHoldTime = 1000; 

int getStableMoistureReading() {
  const int readingsCount = 5; 
  long totalMoisture = 0;
  for (int i = 0; i < readingsCount; i++) {
    totalMoisture += analogRead(moisturePin);
    delay(10); 
  }
  return totalMoisture / readingsCount;
}

int getStableDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); 
  if (duration == 0) {
    return 999; 
  }
  int distance = duration * 0.034 / 2;
  
  if (distance <= 1 || distance > 200) {
    return 999; 
  }
  return distance;
}

void setup() {
  Serial.begin(9600); 
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  
  wasteServo.attach(servoPin); 
  wasteServo.write(neutralPosition);
  delay(1000); 
  wasteServo.detach();

  Serial.println("Arduino Waste Segregator Ready.");
}

void loop() {
  switch (currentState) {
    case IDLE:
      runIdleState();
      break;
    
    case SORTING:
      runSortingState();
      break;
      
    case RESETTING:
      runResettingState();
      break;
  }
}

void runIdleState() {
  if (!wasteServo.attached()) {
    int distance = getStableDistance();

    if (distance == 999) {
      Serial.println("Invalid sensor reading. Awaiting object...");
      delay(200);
      return;
    }

    if (distance <= ultrasonicDistanceCM) {
      Serial.println("Object detected. Analyzing waste type...");
      
      int averageMoisture = getStableMoistureReading();
      
      Serial.print("Moisture reading: ");
      Serial.println(averageMoisture);
      
      wasteServo.attach(servoPin);
      
      if (averageMoisture < wetWasteThreshold) {
        Serial.println("--> WET waste detected.");
        wasteServo.write(wetWastePosition); 
      } else {
        Serial.println("--> DRY waste detected.");
        wasteServo.write(dryWastePosition); 
      }
      
      currentState = SORTING;
      sortingStartTime = millis(); 
    } else {
      Serial.println("Awaiting object...");
      delay(500); 
    }
  }
}

void runSortingState() {
  if (millis() - sortingStartTime >= sortingHoldTime) {
    Serial.println("Sorting complete. Returning to neutral position.");
    wasteServo.write(neutralPosition);
    
    currentState = RESETTING;
    sortingStartTime = millis(); 
  }
}

void runResettingState() {
  if (millis() - sortingStartTime >= resetHoldTime) {
    Serial.println("Reset complete. Ready for next object.");
    wasteServo.detach();
    currentState = IDLE;
  }
}