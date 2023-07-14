#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 4;
#define BUZZER_PIN D1
#define RELAY_PIN D2

// put function declarations here:
int myFunction(int, int);
const int sensorPin = A0;
const char* ssid = "Kali-Linux";
const char* password = "kaliroot";
const char* botToken = "ewiurweiiweurhwieuoiewjroi";
const int telegramChatID = "21312";

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

byte nuidPICC[4];

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rfid = true;
  if(!rfid){
    int sensorValue = analogRead(sensorPin);
    if(sensorValue > 0){
      digitalWrite(BUZZER_PIN, HIGH);
      // send notification to telegram ada yang masuk
    }
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    // send notification to telegram gagal membuka pintu
  } else {
    digitalWrite(RELAY_PIN, LOW);
    delay(5000); // delay untuk akses buka pintu
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    // send notification to telegram berhasil
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}