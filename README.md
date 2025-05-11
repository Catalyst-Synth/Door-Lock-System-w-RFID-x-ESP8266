# 🔐 Door Lock System with RFID & ESP8266

Prototipe sistem pengunci pintu digital menggunakan **RFID + ESP8266**, dengan indikator **LED**, **buzzer**, dan **mini servo** sebagai mekanisme pembukaan. Sistem ini dirancang untuk akses menggunakan kartu RFID bawaan, dan dibangun di atas **breadboard** sebagai tahapan awal uji coba.

## 📌 Fitur Utama

- 📶 Identifikasi pengguna menggunakan kartu RFID
- 🔄 Pembukaan pintu menggunakan **mini servo** (bukan solenoid)
- 🔊 Buzzer sebagai alarm atau notifikasi
- 💡 LED indikator status akses (diterima/ditolak)
- 🌐 Potensial dikembangkan ke sistem berbasis web / IoT karena menggunakan ESP8266

## 🧰 Hardware yang Digunakan

- ESP8266 (NodeMCU atau sejenis)
- RFID Reader RC522 + kartu/tagnya
- Mini Servo (SG90)
- LED (merah & hijau)
- Buzzer
- Breadboard & kabel jumper
- Power supply (USB atau adaptor 5V)

## ⚙️ Cara Kerja Singkat

1. RFID Reader membaca UID dari kartu
2. Jika UID cocok dengan yang terdaftar di program:
   - LED hijau menyala
   - Servo bergerak membuka kunci
   - Buzzer berbunyi singkat (akses diterima)
3. Jika UID tidak cocok:
   - LED merah menyala
   - Buzzer berbunyi lebih lama (akses ditolak)
   - Servo tidak bergerak

## 💻 Software & Library

- Arduino IDE
- Board ESP8266 (install via Board Manager)
- Library:
  - `MFRC522` untuk RFID
  - `Servo.h` untuk kontrol servo
  - `SPI.h` (dependensi RFID)
  
> Semua library dapat di-install melalui Library Manager Arduino IDE.

## 🔖 Lisensi

Proyek ini open-source dan bebas digunakan untuk keperluan edukasi maupun pengembangan sistem keamanan berbasis IoT.
