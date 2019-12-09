int ledPin1 = 9;
int ledPin2 = 8;
int inputPin = 7; // 센서 신호 핀
int pirState = LOW; // 센서의 초기 상태는 움직임이 없음을 가정한다.
int val = 0; // 센서 신호의 판별을 위한 변수

void setup() {
    pinMode(inputPin, INPUT);
    Serial.begin(9600);
}

void loop() {
    val = digitalWrite(inputPin);

    if(val == HIGH) {
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, LOW);
        if(pirState == LOW) {
            Serial.println("Welcome!");
            pirState = HIGH;
        }
    }
    else {
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, HIGH);
        if(pirState == HIGH) {
            Serial.println("Good Bye!");
            pirState = LOW;
        }
    }
}