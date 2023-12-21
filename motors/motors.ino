
#define enA  3
#define enB  9

int rightForward = 4;
int rightReverse = 7;

int leftForward = 8;
int leftReverse = 10;

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightReverse, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftReverse, OUTPUT);
  Serial.println(" Test Motors !");
  stopMotor();
  delay(2000);
}

void loop() {
  printDirection("Moving Forward");
  moveForward(200);
  delay(2000);

  printDirection("Moving Backward");
  moveBackward(100);
  delay(2000);
  /*
  printDirection("Turning Right");
  turnRight();
  delay(2000);

  printDirection("Turning Left");
  turnLeft();
  delay(2000);
*/
  printDirection("Stopping");
  stopMotor();
  delay(2000);
}

void moveForward(int speed) {
  moveWithSpeed(speed);
  digitalWrite(rightForward, LOW);  
  digitalWrite(rightReverse, HIGH); 
  digitalWrite(leftForward, HIGH);  
  digitalWrite(leftReverse, LOW); 
  
}

void moveBackward(int speed) {
  digitalWrite(rightForward, HIGH); 
  digitalWrite(rightReverse, LOW); 
  digitalWrite(leftForward, LOW);  
  digitalWrite(leftReverse, HIGH); 
  moveWithSpeed(speed);
}

void turnLeft(int speed) {
  digitalWrite(rightForward, LOW);
  digitalWrite(rightReverse, HIGH);
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftReverse, LOW);
  moveWithSpeed(speed); 
}

void turnRight(int speed) {
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightReverse, LOW);
  digitalWrite(leftForward, LOW);
  digitalWrite(leftReverse, HIGH);
  moveWithSpeed(speed); 
}
void stopMotor() {
  digitalWrite(rightForward, LOW);
  digitalWrite(rightReverse, LOW);
  digitalWrite(leftForward, LOW);
  digitalWrite(leftReverse, LOW);
  analogWrite(enA, 0);
}
void moveWithSpeed(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}
void printDirection(String direction) {
  Serial.println("Direction: " + direction);
}