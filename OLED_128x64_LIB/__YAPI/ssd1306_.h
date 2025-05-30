#pragma once

// Okuma yönleri
#define __OKUMA_YATAY 0
#define __OKUMA_DIKEY 1

// Flip modları
#define __FLIP_YOK 0
#define __FLIP_X 1
#define __FLIP_Y 2
#define __FLIP_XY 3

// Döndürme modları
#define __DONME_0 0
#define __DONME_90 1
#define __DONME_180 2
#define __DONME_270 3

#if defined(__AVR__)
#define __SSD_ADRES 0x3C

#elif defined(ESP8266) || defined(ESP32)
#define __SSD_ADRES 0x3C

#endif

// Güç ve temel kontrol
#define __SSD_EKRAN_KAPAT 0xAE     // Ekranı kapat
#define __SSD_EKRAN_AC 0xAF        // Ekranı aç
#define __SSD_SARJ_POMPASI 0x8D    // Şarj pompası kontrol komutu
#define __SSD_SARJ_POMPASI_AC 0x14 // Şarj pompasını etkinleştir
#define __SSD_BELLEK_MODU 0x20     // Bellek adresleme modu seçimi
#define __SSD_YATAY_ADRESLEME 0x00 // Yatay adresleme modu

// Sayfa ve adres ayarları
#define __SSD_SAYFA_ADRESI_BAZ 0xB0 // Sayfa adresi başlangıcı
#define __SSD_SUTUN_ADRES_ALT 0x00  // Düşük sütun adresi
#define __SSD_SUTUN_ADRES_UST 0x10  // Yüksek sütun adresi
#define __SSD_ILK_SATIR 0x40        // RAM başlangıç satırı

// Görüntü yönü ve segment ayarları
#define __SSD_COM_TERS_TARAMA 0xC8 // COM satırlarını ters tara
#define __SSD_SEGMENT_TERS 0xA1    // Segmentleri sağdan sola tara

// Ekran efektleri ve görünüm
#define __SSD_NORMAL_GORUNTU 0xA6       // Normal görüntü modu
#define __SSD_TUM_EKRAN_ACIK_DEGIL 0xA4 // Belleğe göre ekran gösterimi
#define __SSD_EKRAN_INVERT_ACIK 0xA7    // invert modunu açar renkleri ters cevirir
#define __SSD_EKRAN_INVERT_KAPALI 0xA6  // invert modunu kapar renkler normal
// Kontrast ve parlaklık
#define __SSD_KONTRAST_AYARLA 0x81 // Kontrast ayar komutu
#define __SSD_KONTRAST_DEGERI 0x7F // Varsayılan kontrast

// Çoklama oranı ve offset
#define __SSD_COKLAMA_AYARLA 0xA8   // Multiplex oranı ayarı
#define __SSD_64_CIZGI 0x3F         // 64 satır (1/64 duty)
#define __SSD_GORUNTU_KAYDIRMA 0xD3 // Görüntü offset ayarı
#define __SSD_KAYDIRMA_YOK 0x00     // Offset yok

// Zamanlama ve sürüş konfigürasyonu
#define __SSD_SAAT_ORANI_AYARLA 0xD5  // Saat oranı ayarı
#define __SSD_SAAT_ORANI 0x80         // Varsayılan saat oranı
#define __SSD_ONSARJ_SURESI 0xD9      // Ön-şarj süresi komutu
#define __SSD_ONSARJ_DEGERI 0xF1      // Ön-şarj süresi değeri
#define __SSD_COM_PIN_YAPILANDIR 0xDA // COM pin yapılandırması
#define __SSD_COM_PIN_DEGERI 0x12     // Alternatif yapılandırma
#define __SSD_VCOM_SEVIYE 0xDB        // VCOMH seviyesini ayarla
#define __SSD_VCOM_DEGERI 0x40        // 0.77 x Vcc

// Bellek adresleme modları
#define __SSD_BELLEK_YATAY_ADRESLEME 0x00 // Yatay adresleme modu
#define __SSD_BELLEK_DIKEY_ADRESLEME 0x01 // Dikey adresleme modu
#define __SSD_BELLEK_SAYFA_ADRESLEME 0x02 // Sayfa adresleme modu (genellikle kullanılır)

// COM çıkış tarama yönü
#define __SSD_COM_TARAMA_NORMAL 0xC0 // COM0 -> COM[N-1], normal tarama
#define __SSD_COM_TERS_TARAMA 0xC8   // COM[N-1] -> COM0, ters tarama

// Segment yeniden eşleme
#define __SSD_SEGMENT_NORMAL 0xA0 // Segment 0 başlangıç
#define __SSD_SEGMENT_TERS 0xA1   // Segment 127 başlangıç (ters)