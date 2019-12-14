#define SCK_PIN 4
#define IO_PIN 3
#define RST_PIN 2

#include <DS1302.h>

DS1302 rtc(RST_PIN, IO_PIN, SCK_PIN);

void setup() {
  rtc.halt(false);
  rtc.writeProtect(false);
  Serial.begin(9600);

  //rtc.setDOW(SUNDAY);
  //rtc.setTime(20, 03, 0);
  //rtc.setDate(14, 12, 2019);

  //현재 시간을 기입한 다음, 주석처리를 해제하고 업로드한다.
}

void loop() {
  while(1) {
    Serial.print("It is ");
    Serial.print(rtc.getDOWStr());
    Serial.print(" ");
    Serial.print(rtc.getDateStr());
    Serial.print(" ");
    Serial.print("and the time is : ");
    Serial.println(rtc.getTimeStr());

    delay(1000);
  }
}
