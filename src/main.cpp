#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Arduino.h>

#define RST_PIN D1
#define SDA_PIN D2
#define BUZZER_PIN D3
#define RELAY_PIN D4

// put function declarations here:
int myFunction(int, int);
const int sensorPin = A0;
const char* ssid = "Kali-Linux";
const char* password = "#M4de$gu5$Nd1empat3Mpat6_M3i2023";
#define BOTtoken "XXXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
#define CHAT_ID "XXXXXXXXXX"

MFRC522 rfid(SS_PIN, RST_PIN);
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  configTime(0, 0, "pool.ntp.org");
  client.setTrustAnchors(&cert);

  // connecting to wifi config
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot started up", "");
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() { 
  bool is_open = false;
  // put your main code here, to run repeatedly:
  if(!mfrc522.PICC_IsNewCardPresent()){
    return;
  }

  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }

  Serial.print("UID tag :");
  String content = "";
  byte letter;

  for(byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Pesan : ");
  content.toUpperCase();

  int sensorValue = analogRead(sensorPin);

  if(content.substring(1) == "D9 DF 60 B9"){
    is_open = true;
    digitalWrite(RELAY_PIN, LOW);
    delay(5000); // delay untuk akses buka pintu
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    // send notification to telegram berhasil membuka pintu
    bot.sendMessage(CHAT_ID, "Yashh..Door Opened!!", "");
  } else if (is_open == false && sensorValue > 625){
    is_open = true;
    delay(2000);
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    // send notification to telegram gagal membuka pintu
    bot.sendMessage(CHAT_ID, "Warning..Door Opened without authorization!", "");
  } else {
    is_open = false;
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}