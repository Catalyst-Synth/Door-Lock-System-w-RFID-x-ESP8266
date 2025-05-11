#include <SPI.h>
#include <MFRC522.h>

// Pin konfigurasi
#define RST_PIN         0   // D3 (GPIO0 pada board NodeMCU ESP8266)
#define SS_PIN          15  // D8 (GPIO15 pada board NodeMCU ESP8266)
#define BUZZER_PIN      5   // D1 (GPIO5 pada board NodeMCU ESP8266)
#define LED_PIN         2   // D4 (GPIO2 pada board NodeMCU ESP8266)

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Inisialisasi modul RFID

// UID yang valid
byte validUID1[] = {0x43, 0x0A, 0x4F, 0x10};  // UID pertama
byte validUID2[] = {0x04, 0x83, 0x74, 0x12, 0x7A, 0x6A, 0x80}; // UID kedua

void setup() {
  Serial.begin(9600);
  SPI.begin();  // Mulai SPI bus
  mfrc522.PCD_Init();  // Inisialisasi RFID

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Arahkan kartu RFID...");
}

void loop() {
  // Mengecek apakah ada kartu yang terdeteksi
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return; 
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return; 
  }

  Serial.print("UID Kartu: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (checkUID(mfrc522.uid.uidByte, mfrc522.uid.size)) {
    Serial.println("FAN ON!");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000, 200);
    delay(200);
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.println("FAN SHUTDOWN");
    for (int i = 0; i < 2; i++) {
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, 1000, 200);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(200);
    }
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(100);
}

bool checkUID(byte *uid, byte uidSize) {
  if (uidSize == 4) { 
    for (byte i = 0; i < uidSize; i++) {
      if (uid[i] != validUID1[i]) {
        return false;
      }
    }
    return true;
  } else if (uidSize == 7) {
    for (byte i = 0; i < uidSize; i++) {
      if (uid[i] != validUID2[i]) {
        return false;
      }
    }
    return true;
  }
  return false; 
}
