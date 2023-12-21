// Motor A connections (Left Motor)

int IN1 = 4; // L293D IN1 Pin for Left Motor
int IN2 = 7; // L293D IN2 Pin for Left Motor
int ENB = 3;

// Motor B connections (Right Motor)
// int ENB = 10; // L293D Enable Pin for Right Motor
// int IN3 = 11; // L293D IN1 Pin for Right Motor
// int IN4 = 12; // L293D IN2 Pin for Right Motor

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Uncomment the following lines if you want to test Motor B
  // pinMode(ENB, OUTPUT);
  // pinMode(IN3, OUTPUT);
  // pinMode(IN4, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // digitalWrite(IN3, LOW);
  // digitalWrite(IN4, LOW);

  // Initialize Serial communication
  Serial.begin(9600);
  delay(1000); // Allow time for Serial Monitor to open
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // digitalWrite(IN3, HIGH); // Uncomment if you want to test Motor B
  // digitalWrite(IN4, LOW);  // Uncomment if you want to test Motor B
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // digitalWrite(IN3, LOW);  // Uncomment if you want to test Motor B
  // digitalWrite(IN4, HIGH); // Uncomment if you want to test Motor B
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // digitalWrite(IN3, HIGH); // Uncomment if you want to test Motor B
  // digitalWrite(IN4, LOW);  // Uncomment if you want to test Motor B
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // digitalWrite(IN3, LOW);  // Uncomment if you want to test Motor B
  // digitalWrite(IN4, HIGH); // Uncomment if you want to test Motor B
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // digitalWrite(IN3, LOW);  // Uncomment if you want to test Motor B
  // digitalWrite(IN4, LOW);  // Uncomment if you want to test Motor B
}

void loop() {
  // Move forward for 2 seconds
  Serial.println("Move Forward");
  moveForward();
  delay(2000);

  // Stop for 1 second
  Serial.println("Stop");
  stopMotors();
  delay(1000);

  // Turn left for 2 seconds
  Serial.println("Turn Left");
  turnLeft();
  delay(2000);

  // Stop for 1 second
  Serial.println("Stop");
  stopMotors();
  delay(1000);

  // Turn right for 2 seconds
  Serial.println("Turn Right");
  turnRight();
  delay(2000);

  // Stop for 1 second
  Serial.println("Stop");
  stopMotors();
  delay(1000);
}
