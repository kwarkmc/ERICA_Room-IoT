/*
  Repeating Web client

 This sketch connects to a a web server and makes a request
 using a Wiznet Ethernet shield. You can use the Arduino Ethernet shield, or
 the Adafruit Ethernet shield, either one will work, as long as it's got
 a Wiznet Ethernet module on board.

 This example uses DNS, by assigning the Ethernet client with a MAC address,
 IP address, and DNS address.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 19 Apr 2012
 by Tom Igoe
 modified 21 Jan 2014
 by Federico Vanzati

 http://www.arduino.cc/en/Tutorial/WebClientRepeating
 This code is in the public domain.
 */

/* Header 선언 */
#include <SPI.h>
#include <Ethernet.h>

#define SCK_PIN 4
#define IO_PIN 5
#define RST_PIN 6
// Real-Time Clock 모듈 핀

#define DHT_PIN 7
#define DHTTYPE DHT11
// DHT11 온습도 센서 핀

#define DUST_INPUT_PIN A0
#define DUST_LED_PIN 9
// Dust_Sensor 미세먼지 측정 센서 핀

#define IR_PIN 8

/* Global Variable 선언 */

int Mode = 0; // 0->Current Mode|생활 모드, 1->Sleeping Mode|외출, 취침 모드

//Weather_Parsing 부분 Global Variable

String temp; // 온도 Global Variable
String wfEn; // 영문 날씨 Global Variable
String reh; // 습도 Global Variable

/* Dust_Sensing 부분 Global Variable */

float Dust_value = 0.00;
float Dust_voltage = 0.00;
float Dust_density = 0.00;

/* IR 센서 부분 Global Variable */

int pirState = LOW; // 센서의 초기 상태는 움직임이 없음을 가정
int val = 0; // 센서 신호의 판별을 위한 변수이다.

byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xFE, 0xED
};

EthernetClient = client;

char server[] = "www.kma.go.kr";

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 10*1000; // 데이터를 받아오는 주기



void setup() {

    /*PinMode 설정*/

    pinMode(Relay_Air_Purifier, OUTPUT);
    pinMode(Relay_Room_Light, OUTPUT);
    pinMode(Relay_Humidifier, OUTPUT);

    
    Serial.begin(9600);
    while(!Serial) {
        //Serial 포트가 연결될 때 까지 대기
    }

    Serial.println("Initialize Ethernet with DHCP");
    if(Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        if(Ethernet.hardwareStatus() == EthernetNoHardware) {
            Serial.println("ENC28J60 was not found.");
            while(true) {
                delay(1);
            }
        }
        if(Ethernet.linkStatus() == LinkOFF) {
            Serial.println("Ethernet cable is not connected");
        }
        Ethernet.begin(mac);
        Serial.print("My IP address : ");
        Serial.println(Ethernet.localIP());
    } else {
        Serial.print("DHCP assigned IP : ");
        Serial.println(Ethernet.localIP());
    }
    delay(1000);

}

void loop() {
    int i = 0;
    String tmp_str;

    if(millis() - lastConnectionTime > postingInterval) {
        httpRequest();
    }

    void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /wid/queryDFSRSS.jsp?zone=4127152500 HTTP/1.1");
    client.println("Host: www.kma.go.kr");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }

  while(client.available()) {
      String line = client.readStringUntil('\n');

      i = line.indexOf("</temp>");

      if(i>0) {
          tmp_str = "<temp>";
          temp = line.substring(line.indexOf(tmp_str) + tmp_str.length(), i);
          Serial.println(temp);
      }

      i = line.indexOf("</wfEn");

      if(i>0) {
          tmp_str = "<wfEn">;
          wfEn = line.substring(line.indexOf(tmp_str) + tmp_str.length(), i);
          Serial.println(wfEn);
      }

      i = line.indexOf("</reh>");

      if(i>0) {
          tmp_str = "<reh>";
          reh = line.substring(line.indexOf(tmp_str) + tmp_str.length(), i);
          Serial.println(reh);
          break;
      }
  }

    if(Mode == 0) {
      Serial.println("Current Mode!");
      digitalWrite(Relay_Air_Purifier, HIGH);
      digitalWrite(Relay_Room_Light, HIGH);
      digitalWrite(Relay_Humidifier, HIGH);
    } 
    else if (Mode == 1) {
      Serial.println("Sleeping Mode!");
      digitalWrite(Relay_Air_Purifier, LOW);
      digitalWrite(Relay_Room_Light, LOW);
      digitalWrite(Relay_Humidifier, LOW);
    }
}
