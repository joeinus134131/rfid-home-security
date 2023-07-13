#include <SPI.h>
#include <RFID.h>
#include <Arduino.h>

#define SS_PIN D4 
#define RST_PIN D3

// put function declarations here:
int myFunction(int, int);
const int relayPin = 8;
const int buzzerPin = 9;
const int sensorPin = A0;
const char* ssid = "Kali-Linux";
const char* password = "kaliroot";
const char* botToken = "";
const int telegramChatID = ;

RFID rfid(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(9600);
  rfid.init();
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rfid = true;
  if(rfid){
    digitalWrite(relayPin, LOW);
    delay(1000);
    int sensorValue = analogRead(sensorPin);
    Serial.print(sensorValue);
    if(sensorValue > 0){
      delay(5000);
      digitalWrite(buzzerPin, HIGH);
      // send notification to telegram
    } else {
      digitalWrite(relayPin, HIGH);
    }
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}