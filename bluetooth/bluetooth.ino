#include <SoftwareSerial.h>

SoftwareSerial BT(11, 12); // RX, TX
boolean BTconnected = false;
const byte BTpin = 2;

void setup() {
  Serial.begin(38400);
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

}

void loop() {

  if (BT.available()) {
    char data = BT.read();

     switch (data) {

      case 'F':
        Serial.println("Go forward");
     
        break;

      case 'B':
        Serial.println("Go backward");
     
        break;

      case 'L':
        Serial.println("Turn left");
      
        break;

      case 'R':
        Serial.println("Turn right");
    
        break;

      case 'A':
        Serial.println("Avoid obstacles mode");
     
        break;

      case 'W':
        Serial.println("Follow wall mode");
        break;

      case 'S':
        Serial.println("Stop");
        break;

      case 'X':
        Serial.println("Exit from mode");

        break;

      default:
  
        break;
   }
}

 /* if (Serial.available()) {
    char data = Serial.read();
    BT.write(data);
  }*/


  delay(1000); 
}

