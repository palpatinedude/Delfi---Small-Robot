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

// right motor
#define enA 3
int RightF = 4; // forward
int RightB = 7; // backward

//  left  motor 
#define enB 9
int LeftF = 8; 
int LeftB = 10;

// functions
void stopMotors();
void turnRight();
void turnLeft();
void moveForward();
void moveBackward(); 

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
  pinMode(RightF, OUTPUT);
  pinMode(RightB, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(LeftF, OUTPUT);
  pinMode(LeftB, OUTPUT);
  Serial.println(" Test Motors !");
  stopMotors();
  delay(2000);
}

void loop(){
  det = check(); 
  switch(det){
      case 'F':
        Serial.println("Go forward");
        moveForward();
        break;

      case 'B':
        Serial.println("Go backward");
        moveBackward();
        det = check();
        break;

      case 'L':
        Serial.println("Turn left");
        turnLeft();
        det = check();
        break;

      case 'R':
        Serial.println("Turn right");
        turnRight();
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
        stopMotors();
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


void moveForward() {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(RightF, LOW);
  digitalWrite(RightB, HIGH);
  digitalWrite(LeftF, HIGH);
  digitalWrite(LeftB, LOW);
}

void moveBackward() {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(RightF, HIGH);
  digitalWrite(RightB, LOW);
  digitalWrite(LeftF, LOW);
  digitalWrite(LeftB, HIGH);
}

void turnLeft() {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(RightF, LOW);
  digitalWrite(RightB, HIGH);
  digitalWrite(LeftF, HIGH);
  digitalWrite(LeftB, LOW);
}

void turnRight() {
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(RightF, HIGH);
  digitalWrite(RightB, LOW);
  digitalWrite(LeftF, LOW);
  digitalWrite(LeftB, HIGH);
}

void stopMotors() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(RightF, LOW);
  digitalWrite(RightB, LOW);
  digitalWrite(LeftF, LOW);
  digitalWrite(LeftB, LOW);
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

    else if (dataIn == 'S'){//Stop
      choice = 'S';
    }
    /*
    else if (dataIn == '0'){//150 0
      vel = 0;
    }
    else if (dataIn == '1'){//150 25
      vel = 25;
    }
    else if (dataIn == '2'){//150 50
      vel = 50;
    }
    else if (dataIn == '3'){//150 75
      vel = 75;
    }
    else if (dataIn == '4'){//150 100
      vel = 100;
    }
    else if (dataIn == '5'){//150 125
      vel = 125;
    }
    else if (dataIn == '6'){//150 150
      vel = 150;
    }
    else if (dataIn == '7'){//150 175
      vel = 175;
    }
    else if (dataIn == '8'){//150 200
      vel = 200;
    }
    else if (dataIn == '9'){//150 225
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