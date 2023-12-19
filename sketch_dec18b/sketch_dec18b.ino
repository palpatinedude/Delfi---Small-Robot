// Motor A connections
int ENA = 9; // L293D Enable Pin
int IN1 = 8; // L293D IN1 Pin
int IN2 = 7; // L293D IN2 Pin

void setup()
{
  pinMode(ENA, OUTPUT); // Set ENA as OUTPUT
  pinMode(IN1, OUTPUT); // Set IN1 as OUTPUT
  pinMode(IN2, OUTPUT); // Set IN2 as OUTPUT

  digitalWrite(IN1, LOW); // Make the Arduino Pin 8 Low
  digitalWrite(IN2, LOW); // Make the Arduino Pin 7 Low
}


void loop() {

  // Rotate Motor Clockwise for 4 Seconds
  analogWrite(ENA, 255); // Enable the L293D IC
  digitalWrite(IN1, HIGH); // Make PIN 8 of the Arduino High
  digitalWrite(IN2, LOW); // Make PIN 7 of the Arduino LOW
  delay(4000); // wait for 4 Se

  // Rotate Motor counter-Clockwise for 4 Seconds
  digitalWrite(IN1, LOW); // Make PIN 8 of the Arduino LOW
  digitalWrite(IN2, HIGH);// Make PIN 7 of the Arduino HIGH
  delay(4000);

  // Stop Rotating the Motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(1000);

  // Turn on motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);


  // Accelerate from minimum to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(ENA, i);
    delay(20);
  }


   delay(2000);
  // Decelerate from maximum speed to minimum
  for (int i = 255; i >= 0; --i) {
    analogWrite(ENA, i);
    delay(20);
  }

  // Now turn off motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(1000);
}