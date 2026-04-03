#include <Arduino.h>

// --- KONFIGURASI BLYNK ---
#define BLYNK_TEMPLATE_ID "TMPL6GCbHgA2S"
#define BLYNK_TEMPLATE_NAME "Monitoring kelembaban"
#define BLYNK_AUTH_TOKEN "JQS9yoMxcYUa8OMQBtFAQwivwm9MFM9T"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// --- KONFIGURASI JARINGAN (WOKWI) ---
const char ssid[] = "Wokwi-GUEST";
const char pass[] = "";

// --- KONFIGURASI HARDWARE ---
const int PIN_DHT = 14;      
const int PIN_LED = 13;      
const int TIPE_DHT = DHT22;  

DHT dht(PIN_DHT, TIPE_DHT);
BlynkTimer timer;

float ambangBatasKelembapan = 65.0; 

// --- FUNGSI BLYNK CALLBACK ---
BLYNK_WRITE(V1) {
  ambangBatasKelembapan = param.asFloat();
  Serial.print("Ambang batas diperbarui: ");
  Serial.println(ambangBatasKelembapan);
}

bool sudahNotifikasi = false; 

// --- FUNGSI PROSES DATA ---
void prosesDataSensor() {
  float kelembapanSaatIni = dht.readHumidity();

  if (isnan(kelembapanSaatIni)) {
    Serial.println("Kesalahan: Gagal membaca data DHT22!");
    return;
  }

  Serial.print("Kelembapan: ");
  Serial.print(kelembapanSaatIni);
  Serial.println(" %RH");

  Blynk.virtualWrite(V0, kelembapanSaatIni);

  if (kelembapanSaatIni > ambangBatasKelembapan) {
    digitalWrite(PIN_LED, HIGH); 
    
    // Hanya kirim notifikasi JIKA belum pernah dikirim
    if (sudahNotifikasi == false) {
      Blynk.logEvent("high_humidity", "Peringatan: Kelembapan ruang arsip melebihi batas!"); 
      sudahNotifikasi = true; // Kunci agar tidak mengirim lagi di detik berikutnya
      Serial.println(">> Notifikasi terkirim ke HP!");
    }
    
  } else {
    digitalWrite(PIN_LED, LOW);
    sudahNotifikasi = false; // Reset kunci jika kondisi sudah kembali aman (< 65%)
  }
}

// --- SETUP & LOOP ---
void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW); 
  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, prosesDataSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}