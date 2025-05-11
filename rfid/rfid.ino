#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9   // Pin RST RFID
#define SS_PIN          10  // Pin SDA RFID
#define BUZZER_PIN      4   // Pin untuk buzzer
#define LED_PIN         5   // Pin untuk LED

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Inisialisasi modul RFID

// Ini adalah UID kartu akses yang benar
byte validUID1[] = {0x43, 0x0A, 0x4F, 0x10};  // UID pertama
byte validUID2[] = {0x04, 0x83, 0x74, 0x12, 0x7A, 0x6A, 0x80}; // UID kedua

void setup() {
  Serial.begin(9600);   // Memulai komunikasi serial
  SPI.begin();          // Memulai SPI bus
  mfrc522.PCD_Init();   // Inisialisasi modul RFID
  
  pinMode(BUZZER_PIN, OUTPUT);  // Set pin buzzer sebagai output
  pinMode(LED_PIN, OUTPUT);     // Set pin LED sebagai output

  Serial.println("Arahkan kartu RFID...");
}

void loop() {
  // Mengecek apakah ada kartu yang terdeteksi
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;  // Jika tidak ada kartu, ulangi loop
  }

  // Membaca kartu yang terdeteksi
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;  // Jika gagal membaca kartu, ulangi loop
  }

  // Menampilkan UID kartu yang terbaca
  Serial.print("UID Kartu: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Membandingkan UID kartu yang dibaca dengan kartu yang valid
  if (checkUID(mfrc522.uid.uidByte, mfrc522.uid.size)) {
    // Jika kartu benar
    Serial.println("ON!");
    digitalWrite(LED_PIN, HIGH);    // Nyalakan LED
    tone(BUZZER_PIN, 1000, 200);    // Bunyi buzzer sekali
    delay(200);
    digitalWrite(LED_PIN, LOW);     // Matikan LED
  } else {
    // Jika kartu salah
    Serial.println("OFF");
    
    // LED berkedip 2 kali
    for (int i = 0; i < 2; i++) {
      digitalWrite(LED_PIN, HIGH);  // Nyalakan LED
      tone(BUZZER_PIN, 1000, 200);  // Bunyi buzzer
      delay(200);
      digitalWrite(LED_PIN, LOW);    // Matikan LED
      delay(200);
    }
  }

  // Menghentikan komunikasi dengan kartu yang terdeteksi
  mfrc522.PICC_HaltA();           // Menghentikan komunikasi dengan kartu
  mfrc522.PCD_StopCrypto1();      // Matikan enkripsi

  delay(100);  // Jeda sebelum memulai pembacaan kartu baru
}

// Fungsi untuk membandingkan UID
bool checkUID(byte *uid, byte uidSize) {
  if (uidSize == 4) { // Jika UID terdiri dari 4 byte
    for (byte i = 0; i < uidSize; i++) {
      if (uid[i] != validUID1[i]) {
        return false;
      }
    }
    return true;
  } else if (uidSize == 7) { // Jika UID terdiri dari 6 byte
    for (byte i = 0; i < uidSize; i++) {
      if (uid[i] != validUID2[i]) {
        return false;
      }
    }
    return true;
  }
  return false; // UID tidak valid
}
