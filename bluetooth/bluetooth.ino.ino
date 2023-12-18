#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); 

char dataIn = 'S';
char determinant;
char det;
int vel = 0;

int check();

void setup() {

  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Initializing...");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
   dataIn= check();  

    switch (dataIn) {
      case 'F':
        Serial.println("Go forward");
        // Handle forward action
        break;

      case 'B':
        Serial.println("Go backward");
        // Handle backward action
        break;

      case 'L':
        Serial.println("Turn left");
        // Handle left action
        break;

      case 'R':
        Serial.println("Turn right");
        // Handle right action
        break;

      case 'A':
        Serial.println("Avoid obstacles mode");
        // Handle avoid obstacles action
        break;

      case 'W':
        Serial.println("Follow wall mode");
        // Handle follow wall action
        break;

      case 'S':
        Serial.println("Stop");
        // Handle stop action
        break;

      case 'X':
        Serial.println("Exit from mode");
        // Handle exit action
        break;

      default:
        // Handle unexpected input
        break;
  }
    
}


int check() {
  if (Serial.available() > 0) {
    dataIn = Serial.read();
    Serial.println(dataIn);}
    else{Serial.println("ep");}

    if (dataIn == 'F') {
      determinant = 'F';
    } else if (dataIn == 'B') {
      determinant = 'B';
    } else if (dataIn == 'L') {
      determinant = 'L';
    } else if (dataIn == 'R') {
      determinant = 'R';
    } else if (dataIn == 'A') {
      determinant = 'A';
    } else if (dataIn == 'W') {
      determinant = 'W';
    } else if (dataIn == 's') {
      determinant = 's';
    } else if (dataIn == 'X') {
      determinant = 'X';
    }
  
  return determinant;
}

