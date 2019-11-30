int Dust_Input = A0;
int Dust_LED = 2;

float Dust_value = 0.00;

void setup() {
  Serial.begin(115200);
  pinMode(Dust_Input, INPUT);
  pinMode(Dust_LED, OUTPUT);
}

void loop() {
  digitalWrite(Dust_LED, LOW);
  delayMicroseconds(280);
  Dust_value = analogRead(Dust_Input);
  delayMicroseconds(40);
  digitalWrite(Dust_LED, HIGH);
  delayMicroseconds(9860);

  Serial.println(Dust_value);
  delay(1000);
}
