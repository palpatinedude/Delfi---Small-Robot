/* 
  Author :
      Marianthi Thodi

  Overview: 
     code defines the behavior of a robot car equipped with ultrasonic sensors for obstacle detection, 
     a servo motor for navigation, and Bluetooth communication for remote control.
     The robot can move forward, backward, turn left or right, and enter obstacle avoidance or wall-following modes. 
     The code initializes various components, including the radar system and motors, and continuously checks for user commands received via Bluetooth.
     Obstacle detection triggers corrective actions, and the robot can dynamically adjust its path to avoid collisions. 
     Additionally, there's functionality for wall following, where the robot navigates parallel to a wall based on sensor feedback. 

*/  

#include <SoftwareSerial.h>
#include <Servo.h>

// pin configurations
// radar
const int trig_pin = 5;           
const int echo_pin = 4;           
const int max_distance = 400;      

//left sesnor
const int trig_pin_1 = A5;          
const int echo_pin_1 = A4;         

// bluetooth commmunication
SoftwareSerial BT(11, 12);          
boolean BT_connected = false;       
const int enable_bt = 2;           

// servo
Servo myservo;                     
const int servo_pin = 13;         

// motors control pins , left ,right 
const int left_f = 10;              
const int left_b = 6;               
const int right_f = 9;              
const int right_b = 3;              

bool device_connected = false;       // Bluetooth device connection status
enum RobotState { OFF, ON };        // states
float coefficients[] = {1.011, -0.893};  
RobotState current_state = OFF;      // current state of the robot
long stop_threshold = 20;            // threshold distance for obstacle detection
bool wall;

char choice;                         // variable to store user command
char command;                        // variable to store received command from Bluetooth
char data_in;                         // variable to store incoming Bluetooth data

int num_readings = 5;                 // number of readings for distance measurement averaging

// functions 
void initialize();
void initialize_bluetooth();         // initializes robot
void initialize_radar();              // initializes the ultrasonic sensor and servo motor
void initialize_motors();             // initializes motor control pins
void stop_motors();                   // stops all motors
void move_forward(int speed);         // moves the robot forward
void move_backward(int speed);        // moves the robot backward
void turn_left(int speed);            // turns the robot left
void turn_right(int speed);           // turns the robot right
void avoid_mode();                    // implements obstacle avoidance mode
char check_command();                 // checks for incoming commands from Bluetooth
float measure_distance(int trigger_pin, int echo_pin);  // measures distance using ultrasonic sensor
void find_max_distance(float forward_distance, float right_distance, float left_distance, float& max_distance, String& max_direction);// find max distance
void handle_obstacle(float& distance, int stop_threshold);  // handles obstacle detection and avoidance
void avoidObstacleOrWall(float forwardDistance, float sideDistance,bool isFollowingRightWall);
void followWall(float wallDistance, bool isFollowingRightWall);
void turn_leftoAdjust();
void turn_righttoAdjust();
void measureDistances(float& forwardDistance, float& leftDistance, float& rightDistance);
char findAndTurnToClosestWall(float leftDistance, float rightDistance);
void avoidObstacle(bool isFollowingRightWall);
void moveUntilMaxDistance(float forwardDistance) ;
void wall_follow();
void measure_distances(float& forwardDistance, float& leftDistance, float& rightDistance);

void setup() {
  initialize();
}

void loop() {
  command = check_command();

  switch (command) {
    case 'F':
      // move forward
      Serial.println("Go forward");
      move_forward(127);
      command = check_command();
      break;

    case 'B':
      // move backward
      Serial.println("Go backward");
      move_backward(50);
      command = check_command();
      break;

    case 'L':
      // turn left
      Serial.println("Turn left");
      turn_left(100);
      command = check_command();
      break;

    case 'R':
      // Turn right
      Serial.println("Turn right");
      turn_right(100);
      command = check_command();
      break;

    case 'A':
      // Enter obstacle avoidance mode
      Serial.println("Avoidance mode");
      avoid_mode();
      command = check_command();
      break;

    case 'W':
      // follow wall mode 
      Serial.println("Follow wall mode");
      wall_follow();
      command = check_command();
      break;

    case 'S':
      // stop
      Serial.println("Stop");
      stop_motors();
      command = check_command();
      break;

    case 'X':
      // turn robot ON
      if (current_state == OFF) {
        current_state = ON;
        Serial.println("Received command 'X': Turning robot ON.");
        Serial.print("Current State: ");
        Serial.println(current_state);
        Serial.println("Robot turned ON");
        command = check_command();
      }
      break;

    case 'x':
      // turn robot OFF
      if (current_state == ON) {
        current_state = OFF;
        Serial.println("Received command 'x': Turning robot OFF.");
        Serial.print("Current State: ");
        Serial.println(current_state);
        Serial.println("Robot turned OFF");
        stop_motors();
        Serial.println("Robot is shut down. Press ON to restart.");
        command = check_command();
      }
      break;

    default:
      break;
  }
}

// initializes Bluetooth communication
void initialize_bluetooth() {
  pinMode(enable_bt, INPUT);
  Serial.println("Arduino is ready");
  Serial.println("Connect the HC-05 to an Android device to continue");
  while (!BT_connected) {
    if (digitalRead(enable_bt) == HIGH) {
      BT_connected = true;
    };
  }
  Serial.println("HC-05 is now connected");
  Serial.println("");
  BT.begin(9600);
  while (true) {
    if (BT.available()) {
      char data_in = BT.read();
      if (data_in == 'X') {
        device_connected = true;
        current_state = ON;
        Serial.println("Robot is ON");
        break;
      }
    }
    delay(1000);
  }
}

// initializes ultrasonic sensor and servo motor
void initialize_radar() {
  Serial.println(" ----------------  INITIALIZE RADAR   ---------------------");
  myservo.attach(servo_pin);
  myservo.writeMicroseconds(2300);
  pinMode(trig_pin, OUTPUT);
  pinMode(trig_pin_1, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(echo_pin_1, INPUT);
  delay(2000);
}

// initializes motor control pins
void initialize_motors() {
  pinMode(left_f, OUTPUT);
  pinMode(left_b, OUTPUT);
  pinMode(right_f, OUTPUT);
  pinMode(right_b, OUTPUT);
  stop_motors();
  delay(2000);
}

// stops all motors
void stop_motors() {
  analogWrite(left_f, 0);
  analogWrite(left_b, 0);
  analogWrite(right_f, 0);
  analogWrite(right_b, 0);
}

// moves the robot forward
void move_forward(int speed) {
  analogWrite(left_f, 0);
  analogWrite(left_b, speed);

  digitalWrite(left_f, LOW);
  digitalWrite(left_b, HIGH);

  analogWrite(right_f, 0);
  analogWrite(right_b, speed);

  digitalWrite(right_f, LOW);
  digitalWrite(right_b, HIGH);
}

// moves the robot backward
void move_backward(int speed) {
  analogWrite(left_f, speed);
  analogWrite(left_b, 0);

  digitalWrite(left_f, HIGH);
  digitalWrite(left_b, LOW);

  analogWrite(right_f, speed);
  analogWrite(right_b, 0);

  digitalWrite(right_f, HIGH);
  digitalWrite(right_b, LOW);
}

// turns the robot left
void turn_left(int speed) {
  analogWrite(right_f, 0);
  analogWrite(right_b, speed);
  
  digitalWrite(right_f, LOW);
  digitalWrite(right_b, HIGH);

  analogWrite(left_f, 0);
  analogWrite(left_b, 0);

  digitalWrite(left_f, LOW);
  digitalWrite(left_b, LOW);
}

// turns the robot right
void turn_right(int speed) {
  analogWrite(right_f, 0);
  analogWrite(right_b, 0);

  digitalWrite(right_f, LOW);
  digitalWrite(right_b, LOW);

  analogWrite(left_f, 0);
  analogWrite(left_b, speed);

  digitalWrite(left_f, LOW);
  digitalWrite(left_b, HIGH);
}

// checks for incoming commands from Bluetooth
char check_command() {
  if (BT.available() > 0) {
    data_in = BT.read();

    if (data_in == 'F') {  // forward
      choice = 'F';
    } else if (data_in == 'B') {  // backward
      choice = 'B';
    } else if (data_in == 'L') {  // left
      choice = 'L';
    } else if (data_in == 'R') {  // right
      choice = 'R';
    } else if (data_in == 'S') {  // stop
      choice = 'S';
    } else if (data_in == 'A') {  // avoid obstacles
      choice = 'A';
    } else if (data_in == 'W') {  // follow wall mode 
      choice = 'W';
    } else if (data_in == 'x') {  // turn robot OFF
      choice = 'x';
    } else if (data_in == 'X') {  // turn robot ON
      choice = 'X';
    }
  }
  return choice;
}

// implements obstacle avoidance mode
void avoid_mode() {
  float max_distance = 0.0;
  String max_direction = "";

// look and get distances in order to compare them
  myservo.writeMicroseconds(2300);
  delay(200);
  float forward_distance = measure_distance(trig_pin, echo_pin);
  handle_obstacle(forward_distance, stop_threshold);
  delay(200);
  myservo.writeMicroseconds(1300);
  delay(200);
  float right_distance = measure_distance(trig_pin, echo_pin);
  delay(200);
  float left_distance = measure_distance(trig_pin_1, echo_pin_1);
  delay(200);
  myservo.writeMicroseconds(2300);

  // print distances
  Serial.println("Forward Measurement: " + String(forward_distance) + " cm");
  Serial.println("Right Measurement: " + String(right_distance) + " cm");
  Serial.println("Left Measurement: " + String(left_distance) + " cm");

  find_max_distance(forward_distance, right_distance, left_distance, max_distance, max_direction);

  delay(500);
  if (max_direction == "Right") {
    Serial.println("Move right");
    turn_right(100);
  } else if (max_direction == "Left") {
    Serial.println("Move left");
    turn_left(100);
  } else {
    Serial.println("No close obstacle, continue moving forward");
    move_forward(127);
  }

  delay(800);
  stop_motors();
  delay(800);
  move_forward(50);
  delay(150);
  stop_motors();
  delay(500);
  Serial.println("Next!!!!!!!!!!!!");
}

// measures distance using ultrasonic sensor ,take 5 samples in order to have better measurments
float measure_distance(int trigger_pin, int echo_pin) {
  const int max_distance = 400;
  const int timeout_micros = max_distance * 29 * 2;
  long duration;
  float distance_sum = 0;
  for (int i = 0; i < num_readings; ++i) {
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);
    duration = pulseIn(echo_pin, HIGH, timeout_micros);

    float distance = duration * 0.034 / 2;
    distance_sum += distance;

    delay(10);
  }

  float average_distance = distance_sum / float(num_readings);
  float calibrated_distance = coefficients[0] * average_distance + coefficients[1];

  return calibrated_distance;
}

// finds the maximum distance and corresponding direction
void find_max_distance(float forward_distance, float right_distance, float left_distance, float& max_distance, String& max_direction) {
  if (forward_distance > max_distance) {
    max_distance = forward_distance;
    max_direction = "Forward";
  }
  if (right_distance > max_distance) {
    max_distance = right_distance;
    max_direction = "Right";
  }
  if (left_distance > max_distance) {
    max_distance = left_distance;
    max_direction = "Left";
  }

  Serial.print("Max Distance: ");
  Serial.print(max_distance);
  Serial.print(" cm, Direction: ");
  Serial.println(max_direction);
}

//  initialization function
void initialize() {
  Serial.begin(9600);
  initialize_bluetooth();
  initialize_radar();
  initialize_motors();
}

// handles obstacle detection and avoidance
void handle_obstacle(float& distance, int stop_threshold) {
  if (distance < stop_threshold) {
    distance = 0;
    Serial.println("Obstacle detected. Avoid collision!");
    stop_motors();
    delay(800);
    move_backward(100);
    delay(300);
    stop_motors();
  }
}

void wall_follow(){
   float forwardDistance, leftDistance, rightDistance;
  measureDistances(forwardDistance, leftDistance, rightDistance);
  myservo.writeMicroseconds(2300); 
  delay(200);

  Serial.print("Forward distance: ");
  Serial.println(forwardDistance);
  Serial.print("Left distance: ");
  Serial.println(leftDistance);
  Serial.print("Right distance: ");
  Serial.println(rightDistance);

  char closerWall = findAndTurnToClosestWall(leftDistance, rightDistance);
  delay(2000);
  if (closerWall == 'R'){
    Serial.println("Be parallel with right wall");
    delay(2000);
    turn_left(100);  // have the robot parallel to the wall
    delay(900);
    stop_motors();
    delay(900);
    delay(10000);
    followWall(rightDistance, true);
  } else {
    Serial.println("Be parallel with left wall");
    delay(2000);
    turn_right(100);  // have the robot parallel to the wall
    delay(900);
    stop_motors();
    delay(900);
    delay(10000);
    followWall(leftDistance, false);
  }

  delay(500);
  Serial.println(" %%%%%%%%%%%%% NEXT CHECK %%%%%%%%%%%%%%%%");
  delay(100);
}

// find the closest wall
char findAndTurnToClosestWall(float leftDistance, float rightDistance) {
  float frontDistance = measure_distance(trig_pin, echo_pin);
  if (leftDistance < rightDistance) {
    Serial.println("Turning left to face the closest wall.");
    turn_left(127); // Turn left 90 degrees
    delay(900);
    stop_motors();
    delay(900);
    moveUntilMaxDistance(frontDistance);
    return 'L';

  } else {
    Serial.println("Turning right to face the closest wall.");
    turn_right(127); // Turn left 90 degrees
    delay(900);
    stop_motors();
    delay(900);
    moveUntilMaxDistance(frontDistance);
    return 'R';
  }
}
// wall following functionality about when robot find the closest wall to move vertically towards the wall up to the desired distance
void moveUntilMaxDistance(float forwardDistance) {
  while (forwardDistance > max_distance) {
    move_forward(100);
    delay(100);
    forwardDistance = measure_distance(trig_pin, echo_pin);
  }
  stop_motors();
  delay(2000);
}

// wall and corner separation
void avoidObstacleOrWall(float forwardDistance, float sideDistance,bool isFollowingRightWall) {
  if (isFollowingRightWall) {
    if (forwardDistance < stop_threshold && sideDistance < max_distance) { // obstacle or corner detected
      Serial.println("Avoiding collision or corner while following right wall!");
      avoidObstacle(isFollowingRightWall);

      float rightDistance_func = measure_distance(trig_pin, echo_pin);
      delay(200);
      if (rightDistance_func <= max_distance) { // corner
        Serial.println("Continue following right wall");
        followWall(rightDistance_func, true);
      } else { // obstacle detected
        Serial.println("Detected obstacle after turning left, turning right!");
        turn_right(100); // Turn right 90 degrees
        delay(800);
        stop_motors();
        delay(800);
        move_forward(100); // Move forward a little bit
        delay(500);
        stop_motors();
      }
    }
  } else {
    if (forwardDistance < stop_threshold && sideDistance < max_distance) { // obstacle or corner detected
      Serial.println("Avoiding collision or corner while following left wall!");
       avoidObstacle(!isFollowingRightWall);

      float leftDistance_func = measure_distance(trig_pin_1, echo_pin_1); 
      delay(200);
      if (leftDistance_func <= max_distance) { // corner
        Serial.println("Continue following left wall");
        followWall(leftDistance_func, false);
      } else { // obstacle detected
        Serial.println("Detected obstacle after turning right, turning left!");
        turn_left(100); // Turn left 90 degrees
        delay(800);
        stop_motors();
        delay(800);
        move_forward(127); // Move forward a little bit
        delay(500);
        stop_motors();
      }
    }
  }
}

// process of wall following and avoid obstacles
void followWall(float wallDistance, bool isFollowingRightWall) {
  float frontDistance = measure_distance(trig_pin, echo_pin);
  delay(200);
  if (frontDistance < stop_threshold) {
    Serial.println("Obstacle detected in front, taking evasive action.");
    stop_motors();
    delay(500);
    avoidObstacleOrWall(frontDistance, wallDistance,isFollowingRightWall);
    return;
  }

  if (isFollowingRightWall) {
    Serial.println("Following right wall");
    myservo.writeMicroseconds(1300); 
  } else {
    Serial.println("Following left wall");
    myservo.writeMicroseconds(2300); 
  }

  if (wallDistance >= stop_threshold && wallDistance <= max_distance) {
    Serial.println("Move forward");
    move_forward(100);
    delay(300);
    stop_motors();
    delay(100);
  } else if (wallDistance < stop_threshold) {
    Serial.println("Obstacle or corner detected, turning right to adjust.");
    turn_rightoAdjust();
  } else if (wallDistance > max_distance) {
    Serial.println("No wall detected, turning left to find the wall.");
    turn_leftoAdjust();
  } else {
    return;
  }
}

void measure_distances(float& forwardDistance, float& leftDistance, float& rightDistance) {
  forwardDistance = measure_distance(trig_pin, echo_pin);
  delay(500);
  leftDistance = measure_distance(trig_pin_1, echo_pin_1);
  delay(500);
  myservo.writeMicroseconds(1300);
  delay(500);
  rightDistance = measure_distance(trig_pin, echo_pin);
  delay(500);
  myservo.writeMicroseconds(2300);
}

void turn_rightoAdjust(){
    Serial.println("Turn Right ");
    turn_right(100);
    delay(500);
    move_forward(100);
    delay(200);
    turn_left(70);
    delay(200);
    move_forward(100);
    delay(100);
    stop_motors();
    delay(200);
}

void turn_leftoAdjust(){
    Serial.println("Turn Left");
    turn_left(100);
    delay(200);
    move_forward(100);
    delay(100);
    turn_right(70);
    delay(200);
    move_forward(100);
    delay(100);
    stop_motors();
    delay(200);
}

// process of avoid obstacles
void avoidObstacle(bool isFollowingRightWall) {
  stop_motors();
  delay(400);
  move_backward(100);
  delay(200);

  if (isFollowingRightWall) {
    turn_left(100);
  } else {
    turn_right(100);
  }

  delay(800);
  stop_motors();
  delay(800);
  move_forward(127);
  delay(500);
  stop_motors();
}



