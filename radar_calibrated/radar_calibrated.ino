#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN 5
#define ECHO_PIN 6
#define MAX_DISTANCE 200

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;

float coefficients[] = {1.011, -0.893}; // Calibration coefficients

int distance = 100;

void setup() {
  Serial.begin(9600);
  Serial.println(" ----------------  INITIALIZE RADAR   ---------------------");
  myservo.attach(13); // Servo attached to pin 13
  myservo.write(115);
  delay(2000);
}


void loop() {
  int distanceR = 0;
  int distanceL = 0;

  // Measure distance when servo is facing forward (center position)
  myservo.write(115);
  delay(500); // Allow some time for the servo to settle
  int rawDistanceFront = readPing();
  float calibratedDistanceFront = calibrateDistance(rawDistanceFront);
  Serial.print("Distance in front: ");
  Serial.println(calibratedDistanceFront);

   if (calibratedDistanceFront < 40) {
    Serial.println("Stop! Obstacle detected in front.");
    delay(5000);
  } else {
    // Continue with other measurements
    delay(200);


  // Measure distance when servo is looking to the right
  myservo.write(50);
  delay(500);
  int rawDistanceR = readPing();
  float calibratedDistanceR = calibrateDistance(rawDistanceR);
  Serial.print("Distance on the right: ");
  Serial.println(calibratedDistanceR);

  // Measure distance when servo is looking to the left
  myservo.write(170);
  delay(500);
  int rawDistanceL = readPing();
  float calibratedDistanceL = calibrateDistance(rawDistanceL);
  Serial.print("Distance on the left: ");
  Serial.println(calibratedDistanceL);


  float maxCalibratedDistance = max(calibratedDistanceFront, max(calibratedDistanceR, calibratedDistanceL));

  Serial.print("Max distance is in the ");
  
  if (maxCalibratedDistance == calibratedDistanceFront) {
    Serial.print("front");
 //   myservo.write(115); // Center position
  } else if (maxCalibratedDistance == calibratedDistanceR) {
    Serial.print("right");
 //   myservo.write(50); // Right position
  } else if (maxCalibratedDistance == calibratedDistanceL) {
    Serial.print("left");
   // myservo.write(170); // Left position
  }

  Serial.print(" direction with a distance of ");
  Serial.print(maxCalibratedDistance);
  Serial.println(" cm");

  delay(2000); 
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

float calibrateDistance(int rawDistance) {

  float calibratedDistance = coefficients[0] * rawDistance + coefficients[1];
  return calibratedDistance;
}

