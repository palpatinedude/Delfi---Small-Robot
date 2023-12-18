int en = 9;
int in1 = 7;
int in2 = 8;

void setup() {
  delay(2000);
  Serial.begin(9600);
  Serial.println("ArduinoBymyself - ROVERBot");

  // Set motor control pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Set PWM pin as an output
  pinMode(en, OUTPUT);
}

void loop() {
  // Set motor to rotate forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // Experiment with PWM on pin 9
  analogWrite(en, 128);  // Set PWM duty cycle to 50% (0 to 255)
  delay(2000);

  // Stop the motor for 1 second
  analogWrite(en, 0);
  delay(1000);

  // Set motor to rotate backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Experiment with PWM on pin 9
  analogWrite(en, 200);  // Set PWM duty cycle to 78%
  delay(2000);

  // Stop the motor for 1 second
  analogWrite(en, 0);
  delay(1000);
}
