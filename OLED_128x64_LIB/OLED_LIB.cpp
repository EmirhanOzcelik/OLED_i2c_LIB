#include "OLED_LIB.h"
#include "__YAPI/ssd1306_.h"

oled::oled(uint8_t ekran_x_, uint8_t ekran_y_)
{
    __EKRAN_GENISLIK = ekran_x_;
    __EKRAN_YUKSEKLIK = ekran_y_;
    __SSD_PAKET_MAX = __EKRAN_GENISLIK * (__EKRAN_YUKSEKLIK / 8);
    
    ayarla.ayar_priv = this;
    ayarla.bitmap.ayar_bitmap_priv = this;
    geometri.geometri_priv = this;
    mod.mod_priv = this;
    arkaplan.arkaplan_priv = this;
    font.font_priv = this;
    font.sec.sec_font_priv = this;

    geometri.cerceve.cerceve_priv = this;
    geometri.cerceve.ici_bos.ici_bos_priv = this;
    geometri.cerceve.ici_dolu.ici_dolu_priv = this;

    geometri.cizgi.cizgi_priv = this;
    geometri.cizgi.sil.sil_cizgi_priv = this;
    geometri.cizgi.ciz.ciz_cizgi_priv = this;

    buffer = new uint8_t[__SSD_PAKET_MAX]; // satır başına 1 byte
    memset(buffer, 0, __SSD_PAKET_MAX);
}
oled::~oled()
{
    delete[] buffer;
}

bool oled::kur()
{
#if defined(__AVR__)
    i2c_kur();
#elif defined(ESP8266) || defined(ESP32)
    if (!i2c_kur())
        return false;
#endif
    komut_gonder(__SSD_EKRAN_KAPAT);          // Ekranı kapat
    komut_gonder(__SSD_SARJ_POMPASI);         // Şarj pompası kontrolü
    komut_gonder(__SSD_SARJ_POMPASI_AC);      // Şarj pompasını aç
    komut_gonder(__SSD_BELLEK_MODU);          // Bellek adresleme modu seç
    komut_gonder(__SSD_YATAY_ADRESLEME);      // Yatay adresleme modu
    komut_gonder(__SSD_COKLAMA_AYARLA);       // Çoklama oranı ayarla
    komut_gonder(__SSD_64_CIZGI);             // 64 satır için
    komut_gonder(__SSD_GORUNTU_KAYDIRMA);     // Görüntü kaydırma
    komut_gonder(__SSD_KAYDIRMA_YOK);         // Kaydırma yok
    komut_gonder(__SSD_COM_PIN_YAPILANDIR);   // COM pin yapılandırması
    komut_gonder(__SSD_COM_PIN_DEGERI);       // COM pin değeri
    komut_gonder(__SSD_SAAT_ORANI_AYARLA);    // Saat oranı ayarla
    komut_gonder(__SSD_SAAT_ORANI);           // Saat oranı
    komut_gonder(__SSD_ONSARJ_SURESI);        // Ön şarj süresi
    komut_gonder(__SSD_ONSARJ_DEGERI);        // Ön şarj değeri
    komut_gonder(__SSD_COM_TERS_TARAMA);      // COM satırlarını ters tara
    komut_gonder(__SSD_SEGMENT_TERS);         // Segmentleri ters tara
    komut_gonder(__SSD_NORMAL_GORUNTU);       // Normal görüntü modu
    komut_gonder(__SSD_TUM_EKRAN_ACIK_DEGIL); // Belleğe göre ekran gösterimi
    komut_gonder(__SSD_KONTRAST_AYARLA);      // Kontrast ayar komutu
    komut_gonder(__SSD_KONTRAST_DEGERI);      // Kontrast değeri
    komut_gonder(__SSD_EKRAN_AC);             // Ekranı aç
    sil();
    font.sec.yazi();
    guncelle();
    return true;
}
void oled::sil() { memset(buffer, 0, __SSD_PAKET_MAX); }
void oled::guncelle()
{
    for (uint8_t sayfa = 0; sayfa < (__EKRAN_YUKSEKLIK / 8); sayfa++)
    {
        komut_gonder(__SSD_SAYFA_ADRESI_BAZ + sayfa);
        komut_gonder(0x00); 
        komut_gonder(0x10); 
        veri_gonder(&buffer[sayfa * __EKRAN_GENISLIK], __EKRAN_GENISLIK);
    }
}
inline void oled::komut_gonder(uint8_t cmd)
{
#if defined(__AVR__)
    i2c_baslat();
    i2c_yaz(__SSD_ADRES << 1); 
    i2c_yaz(0x00);            
    i2c_yaz(cmd);            
    i2c_durdur();
#elif defined(ESP8266) || defined(ESP32)
    Wire.beginTransmission(__SSD_ADRES);
    Wire.write(0x00);
    Wire.write(cmd);
    Wire.endTransmission();
#endif
}
inline void oled::veri_gonder(uint8_t *data, size_t len)
{
#if defined(__AVR__)
    i2c_baslat();
    i2c_yaz(__SSD_ADRES << 1); 
    i2c_yaz(0x40);           
    const uint8_t *p = data;
    const uint8_t *end = p + len;
    while (p < end)
        i2c_yaz(*p++);
    i2c_durdur();
#elif defined(ESP8266) || defined(ESP32)
    const uint8_t *p = data;
    const uint8_t *end = p + len;
    while (p < end)
    {
        Wire.beginTransmission(__SSD_ADRES);
        Wire.write(0x40);
        for (uint8_t i = 0; i < 32 && p < end; i++)
            Wire.write(*p++);
        Wire.endTransmission();
    }
#endif
}
void oled::pixel_ac(uint8_t x, uint8_t y)
{
    if (x < __EKRAN_GENISLIK && y < __EKRAN_YUKSEKLIK)
        buffer[((y) >> 3) * __EKRAN_GENISLIK + (x)] |= (1 << ((y) & 0x07));
}
void oled::pixel_kapa(uint8_t x, uint8_t y)
{
    if (x < __EKRAN_GENISLIK && y < __EKRAN_YUKSEKLIK)
        buffer[((y) >> 3) * __EKRAN_GENISLIK + (x)] &= ~(1 << ((y) & 0x07));
}
bool oled::pixel_kontrol(uint8_t x, uint8_t y)
{
    uint8_t *p = buffer + x + (y >> 3) * __EKRAN_GENISLIK;
    return (*p & (1 << (y & 7))) != 0;
}
