#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Servo.h>

// radar sensor

#define TRIG_PIN 5
#define ECHO_PIN 6
#define MAX_DISTANCE 200

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;

float coefficients[] = {1.011, -0.893}; // calibration coefficients
int distance = 100;

// bluetooth 

SoftwareSerial BT(11, 12); // rx, tx
boolean BTconnected = false;
const byte BTpin = 2;
char choice;
char det;
char dataIn;

// motors

// motor A
int enA = 3;
int in1 = 4;
int in2 = 7;

// motor B
int enB = 9;
int in3 = 8;
int in4 = 10;

// functions
void stopMotor();
void turnRight(int speed);
void turnLeft(int speed);
void moveForward(int speed);
void moveBackward(int speed); 
void moveWithSpeed(int speed);
char check();

void setup() {
  Serial.begin(9600);

  // first connect with the bluetooth device
  pinMode(BTpin, INPUT);
  Serial.println("Arduino is ready");
  Serial.println("Connect the HC-05 to an Android device to continue");

   while (!BTconnected)
    {
      if ( digitalRead(BTpin)==HIGH)  { BTconnected = true;};
    }
 
    Serial.println("HC-05 is now connected");
    Serial.println("");
    BT.begin(9600);  

  // initialize radar 
  Serial.println(" ----------------  INITIALIZE RADAR   ---------------------");
  myservo.attach(13); // Servo attached to pin 13
  myservo.write(115);
  delay(2000);

  // initialize robot
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.println(" Test Motors !");
  stopMotor();
  delay(2000);
}

void loop(){
  det = check(); 
  switch(det){
      case 'F':
        Serial.println("Go forward");
        moveForward(100);
        det = check();
        break;

      case 'B':
        Serial.println("Go backward");
        moveBackward(100);
        det = check();
        break;

      case 'L':
        Serial.println("Turn left");
        turnLeft(100);
        det = check();
        break;

      case 'R':
        Serial.println("Turn right");
        turnRight(100);
        det = check();
        break;

      case 'A':
        Serial.println("Avoid obstacles mode");
        det = check();
        break;

      case 'W':
        Serial.println("Follow wall mode");
        det = check();
        break;

      case 'S':
        Serial.println("Stop");
        det = check();
        break;

      case 'X':
        Serial.println("Exit from mode");
        det = check();
        break;

      default:
        
        break;
   }
}


void moveForward(int speed) {
  moveWithSpeed(speed);
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW); 
}

void moveBackward(int speed) {
  moveWithSpeed(speed);
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH); 
}

void turnLeft(int speed) {
  moveWithSpeed(speed); 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 
}

void turnRight(int speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  moveWithSpeed(speed); 
}
void stopMotor() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
}

void moveWithSpeed(int speed) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

char check(){
  if (BT.available() > 0){// if there is valid data in the serial port
  dataIn = BT.read();// stores data into a varialbe
 
//check the code
    if (dataIn == 'F'){//Forward
      choice = 'F';
    }
    else if (dataIn == 'B'){//Backward
      choice = 'B';
    }
    else if (dataIn == 'L'){//Left
      choice = 'L';
    }
    else if (dataIn == 'R'){//Right
      choice = 'R';
    }
    else if (dataIn == 'I'){//Froward Right
      choice = 'I';
    }
    else if (dataIn == 'J'){//Backward Right
      choice = 'J';
    }
    else if (dataIn == 'G'){//Forward Left
      choice = 'G';
    }    
    else if (dataIn == 'H'){//Backward Left
      choice = 'H';
    }
    else if (dataIn == 'S'){//Stop
      choice = 'S';
    }
    /*
    else if (dataIn == '0'){//Speed 0
      vel = 0;
    }
    else if (dataIn == '1'){//Speed 25
      vel = 25;
    }
    else if (dataIn == '2'){//Speed 50
      vel = 50;
    }
    else if (dataIn == '3'){//Speed 75
      vel = 75;
    }
    else if (dataIn == '4'){//Speed 100
      vel = 100;
    }
    else if (dataIn == '5'){//Speed 125
      vel = 125;
    }
    else if (dataIn == '6'){//Speed 150
      vel = 150;
    }
    else if (dataIn == '7'){//Speed 175
      vel = 175;
    }
    else if (dataIn == '8'){//Speed 200
      vel = 200;
    }
    else if (dataIn == '9'){//Speed 225
      vel = 225;
    }   
    else if (dataIn == 'b'){//Extra On
      choice = 'b';
    }
    else if (dataIn == 'm'){//Extra On
      choice = 'm';
    }*/
  }
  return choice;
}