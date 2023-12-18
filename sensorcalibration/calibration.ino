const int trigPin = 7;
const int echoPin = 2;

// Original optimized coefficients
float coefficients[] = { 1.011, -0.893};

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int recordedDistance = duration * 0.034 / 2;

  // Apply Calibration
  float calibratedDistance = coefficients[0] * recordedDistance + coefficients[1];

  Serial.print("Distance: ");
  Serial.println(static_cast<int>(calibratedDistance));
  
  delay(5000);
}

