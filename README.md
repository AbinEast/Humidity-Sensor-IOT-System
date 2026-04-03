# Sistem Monitoring Kelembapan Perpustakaan

Proyek simulasi Internet of Things (IoT) untuk memantau suhu dan kelembapan ruang penyimpanan dokumen arsip guna mencegah kerusakan kertas akibat jamur atau udara kering.

## Teknologi yang Digunakan
* **Microcontroller:** ESP32 (Simulasi via Wokwi)
* **Sensor:** DHT22 (Sensor Suhu & Kelembapan)
* **Platform Cloud:** Blynk IoT
* **Environment:** Visual Studio Code + PlatformIO

## Cara Menjalankan Simulasi
1. Clone repository ini : `git clone https://github.com/UsernameAnda/monitoring-arsip-iot.git`
2. Buka folder proyek di Visual Studio Code.
3. Pastikan ekstensi PlatformIO dan Wokwi Simulator sudah terinstal.
4. Klik ikon Build (✓) di bawah PlatformIO.
   <img width="1293" height="1034" alt="Screenshot 2026-04-03 180416" src="https://github.com/user-attachments/assets/40e57f5c-ef3b-408b-b244-a0587e1d94f3" />
5. Buka file `diagram.json`, tekan `Ctrl+Shift+P`, lalu pilih `Wokwi: Start Simulator`.
