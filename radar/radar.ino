#include <Servo.h>

Servo myservo; 

const int trigPin = 2; 
const int echoPin = 3;  
long getDistance();
void moveAndMeasure(int position, const char* direction);

void setup() {
  Serial.begin(9600);
  myservo.attach(9); 
  myservo.writeMicroseconds(1000);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int positions[3] = {1000, 1500, 2000}; 
  const char* directions[3] = {"Right", "Forward", "Left"};  

  for (int i = 0; i < 3; ++i) {
    moveAndMeasure(positions[i], directions[i]);
  }
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; 
  return distance;
}

void moveAndMeasure(int position, const char* direction) {
  myservo.writeMicroseconds(position);
  delay(500); 
  long distance = getDistance();
  Serial.print("Distance (");
  Serial.print(direction);
  Serial.print("): ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(2000);
}
