int en = 9;
int in1 = 7;
int in2 = 8;

void setup() {
  delay(2000);
  Serial.begin(9600); 
  Serial.println("ArduinoBymyself - ROVERBot");
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en,INPUT);
}

void loop() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(2000);
  digitalWrite(in1, LOW);
  delay(1000);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);
  digitalWrite(in2, LOW);
  delay(1000);
}