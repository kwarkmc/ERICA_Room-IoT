int Relay_1 = 3;
int input = 0;

void setup() {
  pinMode(Relay_1, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    input = Serial.read();
    if(input == 1) {
      digitalWrite(Relay_1, HIGH);
    }
    else {
      digitalWrite(Relay_1, LOW);
    }
  }
}
