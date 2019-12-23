#include <SoftwareSerial.h>

int Relay_Light = 8;
int Relay_AirPurifier = 9;
int input = 0;

SoftwareSerial bluetooth(2, 3);

void setup() {
  Serial.begin(9600);
  while(!Serial) {
    
  }
  Serial.println("Paired!");
  bluetooth.begin(9600);
}

void loop() {
  if(bluetooth.available()) {
    input = Serial.read();
    if(input == '00') {
      digitalWrite(Relay_Light, HIGH);
      Serial.println("Relay_Light On!")
    }
    else if (input == '01') {
      digitalWrite(Relay_Light, LOW);
      Serial.println("Relay_Light OFF!");
    }
    else if (input == '10') {
      digitalWrite(Relay_AirPurifier, LOW);
      Serial.println("Relay_AirPurifier OFF!");
    }
    else if (input == '11') {
      digitalWrite(Relay_AirPurifier, HIGH);
      Serial.println("Relay_AirPurifier ON!");
    }
  }
}
