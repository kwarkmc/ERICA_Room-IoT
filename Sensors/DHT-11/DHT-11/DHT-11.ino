#include "DHT.h"
#define DHT_PIN 2
#define DHTTYPE DHT11

DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  Serial.print("Humidity : ");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temperature : ");
  Serial.print(t);
  Serial.println("C");
}
