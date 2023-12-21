#include <Servo.h>

Servo myservo;

const int trigPin = 5;
const int echoPin = 6;
float coefficients[] = {1.011, -0.893}; // Calibration coefficients

long moveAndMeasure(int position, const char* direction, long stopThreshold);
long getDistance();

void setup() {
  Serial.begin(9600);
  myservo.attach(13); // Change the pin number to the one you're using for the servo
  myservo.writeMicroseconds(1000);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int positions[3] = {1000, 1500, 2000};
  const char* directions[3] = {"Right", "Forward", "Left"};
  long stopThreshold = 40; 

  long maxDistance = 0;
  const char* maxDirection;

  for (int i = 0; i < 3; ++i) {
    long currentDistance = moveAndMeasure(positions[i], directions[i], stopThreshold);
    delay(500);

    if (currentDistance > maxDistance) {
      maxDistance = currentDistance;
      maxDirection = directions[i];
    }
    delay(500);
  }

  // Print the overall maximum distance and move to the corresponding direction
  Serial.print("Max distance is in the ");
  Serial.print(maxDirection);
  Serial.print(" direction with a distance of ");
  Serial.print(maxDistance);
  Serial.println(" cm");

// Move the servo to the direction with the max distance
if (strcmp(maxDirection, "Right") == 0) {
  myservo.writeMicroseconds(1000);
  Serial.println("Moving to the Right");
} else if (strcmp(maxDirection, "Forward") == 0) {
  myservo.writeMicroseconds(1500);
  Serial.println("Moving Forward");
} else if (strcmp(maxDirection, "Left") == 0) {
  myservo.writeMicroseconds(2000);
  Serial.println("Moving to the Left");
}


  delay(2000);
}

long moveAndMeasure(int position, const char* direction, long stopThreshold) {
  myservo.writeMicroseconds(position);
  
  long distance = getDistance();
  Serial.print("Distance (");
  Serial.print(direction);
  Serial.print("): ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long recordedDistance = duration * 0.034 / 2;

  // Apply Calibration
  float calibratedDistance = coefficients[0] * recordedDistance + coefficients[1];

  long stopThreshold = 20; 
  if (calibratedDistance < stopThreshold) {
    Serial.println("Stop");
    delay(3000);
  }

  return calibratedDistance;
}
