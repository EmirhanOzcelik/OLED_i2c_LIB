#pragma once

#include "Arduino.h"
#include "__YAPI/ssd1306_.h"

#define ORTA 254
#define SOL 0
#define SAG 128

#define __OLED_GENELFONT_XPIX 6
#define __OLED_GENELFONT_YPIX 8

#if defined(ARDUINO_ARCH_AVR)
#include "__YAPI/avr/i2c_komutlar.h"
#elif defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
#include "__YAPI/esp/i2c_komutlar.h"
#elif defined(ARDUINO_ARCH_STM32)
#include "__YAPI/arm/i2c_komutlar.h"
#else
#error "Desteklenmeyen mimari"
#endif

class oled
{
private: //_____________________________Ek sınıflar______________________________
    friend class ayarla;
    friend class geometri;
    friend class cizgi;
    friend class cerceve;
    friend class mod;
    friend class arkaplan;
    friend class font;
    class font
    {
    private:
        oled *font_priv;
        friend class oled;

    public:
        class sec
        {
        private:
            oled *sec_font_priv;
            friend class oled;

        public:
            void yazi() { sec_font_priv->font_sec(0); }
            void buyukSayi() { sec_font_priv->font_sec(2); }
            void minikSayi() { sec_font_priv->font_sec(1); }
        } sec;
    };
    class arkaplan
    {
    private:
        friend class oled;
        oled *arkaplan_priv;

    public:
        void paragraf_goruntuleyici(const char *metin, uint8_t azaltici, uint8_t arttirici, uint8_t max_ekran_satiri = 7);
        void paragraf_goruntuleyici(const String &metin, uint8_t azaltici, uint8_t arttirici, uint8_t max_ekran_satiri = 7);
    };
    class mod
    {
    private:
        friend class oled;
        oled *mod_priv;

    public:
        void yaz(const char *k, int32_t a, uint8_t x, uint8_t y);
        void yaz(const String &k, int32_t a, uint8_t x, uint8_t y);
        void yaz(char k, int32_t a, uint8_t x, uint8_t y);
        void altSatira_ortali_yaz(const char *k, int32_t a, uint8_t x, uint8_t y, bool buyuk = 0);
        void altSatira_ortali_yaz(const String &yazi, int32_t sayi, uint8_t x, uint8_t y, bool buyuk);
        void saat(uint8_t x, uint8_t y, uint8_t saat, uint8_t dk, uint8_t sn = 254);
        void saat_orta(uint8_t x, uint8_t y, uint8_t saat, uint8_t dk, uint8_t sn = 254);
        void saat_buyuk(uint8_t x, uint8_t y, uint8_t saat, uint8_t dk, uint8_t sn = 254);
        void tarih(uint8_t x, uint8_t y, uint8_t gun, uint8_t ay, uint16_t yil);
        void tarih(uint8_t x, uint8_t y, const char *haftaninGun, uint8_t gun, uint8_t ay, uint16_t yil, bool alta_yaz = 1);
        void tarih(uint8_t x, uint8_t y, const char *ay_isim, const char *haftaninGun, uint8_t gun, uint8_t ay, uint16_t yil, bool alta_yaz = 1);
    };
    class ayarla
    {
    private:
        friend class oled;
        oled *ayar_priv;

    public:
        void arkaplan_siyah();
        void arkaplan_beyaz();
        void parlaklik(uint8_t deger);
        void ekran_ac();
        void ekran_kapa();
        void ters_cevir();
        void duze_cevir();
        void renkleri_ters_cevir();
        void renkleri_normale_cevir();
        class bitmap
        {
        private:
            friend class oled;
            oled *ayar_bitmap_priv;
            // Yazdırma modları
            const uint8_t OKUMA_YATAY = 0;
            const uint8_t OKUMA_DIKEY = 1;

            // Flip (ayna) modları
            const uint8_t FLIP_YOK = 0;
            const uint8_t FLIP_X = 1;
            const uint8_t FLIP_Y = 2;
            const uint8_t FLIP_XY = 3;

            // Döndürme modları
            const uint8_t DONME_0 = 0;
            const uint8_t DONME_90 = 1;
            const uint8_t DONME_180 = 2;
            const uint8_t DONME_270 = 3;
            uint8_t _yazdirma_mod = __OKUMA_YATAY; // __OKUMA_DIKEY - byte okuma yazma modu
            uint8_t _flip_mod = __FLIP_YOK;        // __FLIP_X __FLIP_XY __FLIP_Y - aynalama
            uint8_t _donme_mod = __DONME_0;        // __DONME_180 __DONME_270 __DONME_90 - Dondurme

        public:
            void ayarlari_sifirla() { _yazdirma_mod = OKUMA_YATAY, _flip_mod = FLIP_YOK, _donme_mod = DONME_0; }
            void okuma_mod_yatay() { _yazdirma_mod = OKUMA_YATAY; }
            void okuma_mod_dikey() { _yazdirma_mod = OKUMA_DIKEY; }

            void aynalama_yok() { _flip_mod = FLIP_YOK; }
            void aynalama_x() { _flip_mod = FLIP_X; }
            void aynalama_y() { _flip_mod = FLIP_Y; }
            void aynalama_xy() { _flip_mod = FLIP_XY; }

            void donme_0() { _donme_mod = DONME_0; }
            void donme_90() { _donme_mod = DONME_90; }
            void donme_180() { _donme_mod = DONME_180; }
            void donme_270() { _donme_mod = DONME_270; }
        } bitmap;
    };
    class geometri
    {
    private:
        friend class oled;
        oled *geometri_priv;

    public:
        bool nokta_kontrol(uint8_t x, uint8_t y);
        void nokta_ciz(uint8_t x, uint8_t y);
        void nokta_sil(uint8_t x, uint8_t y);
        void yay_ciz(int cx, int cy, int r, float start_angle_deg, float end_angle_deg, uint8_t kalinlik = 1);
        void yay_sil(int cx, int cy, int r, float start_angle_deg, float end_angle_deg, uint8_t kalinlik = 1);
        void yatay_aynala(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
        void dikey_aynala(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
        void dogrusal_egim_ciz(int x0, int y0, float m, int uzunluk, uint8_t kalinlik = 1);
        void dogrusal_egim_sil(int x0, int y0, float m, int uzunluk, uint8_t kalinlik = 1);
        class cizgi
        {
        private:
            friend class oled;

            oled *cizgi_priv;

        public:
            class sil
            {
            private:
                friend class oled;

                oled *sil_cizgi_priv;

            public:
                void cizgi_(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t kalinlik = 1);
                void yatay(uint8_t x, uint8_t y, uint8_t uzunluk, uint8_t kalinlik = 1);
                void dikey(uint8_t x, uint8_t y, uint8_t uzunluk, uint8_t kalinlik = 1);
            } sil;
            class ciz
            {
            private:
                friend class oled;
                oled *ciz_cizgi_priv;

            public:
                void cizgi_(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t kalinlik = 1);
                void yatay(uint8_t x, uint8_t y, uint8_t uzunluk, uint8_t kalinlik = 1);
                void dikey(uint8_t x, uint8_t y, uint8_t uzunluk, uint8_t kalinlik = 1);
            } ciz;

        } cizgi;
        class cerceve
        {
        private:
            friend class oled;

            oled *cerceve_priv;

        public:
            class ici_dolu
            {
            private:
                friend class oled;

                oled *ici_dolu_priv;

            public:
                void dikdortgen_ciz(uint8_t x, uint8_t y, uint8_t h, uint8_t w);
                void dikdortgen_sil(uint8_t x, uint8_t y, uint8_t h, uint8_t w);
                void ucgen_ciz(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
                void ucgen_sil(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
                void cember_ciz(uint8_t merkez_x, uint8_t merkez_y, uint8_t r);
                void cember_sil(uint8_t merkez_x, uint8_t merkez_y, uint8_t r);
                void elips_ciz(int cx, int cy, int a, int b);
                void elips_sil(int cx, int cy, int a, int b);
                void daire_dilimi_ciz(int cx, int cy, int r, float start_angle_deg, float end_angle_deg);
                void daire_dilimi_sil(int cx, int cy, int r, float start_angle_deg, float end_angle_deg);

            } ici_dolu;
            class ici_bos
            {
            private:
                friend class oled;

                oled *ici_bos_priv;

            public:
                void ucgen_ciz(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
                void ucgen_sil(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
                void cember_ciz(uint8_t merkez_x, uint8_t merkez_y, uint8_t r, uint8_t kalinlik);
                void cember_sil(uint8_t merkez_x, uint8_t merkez_y, uint8_t r, uint8_t kalinlik);
                void elips_ciz(int cx, int cy, int a, int b, uint8_t kalinlik);
                void elips_sil(int cx, int cy, int a, int b, uint8_t kalinlik);
                void daire_dilimi_ciz(int cx, int cy, int r, float start_angle_deg, float end_angle_deg, uint8_t kalinlik);
                void daire_dilimi_sil(int cx, int cy, int r, float start_angle_deg, float end_angle_deg, uint8_t kalinlik);
                void dikdortgen_ciz(uint8_t x, uint8_t y, uint8_t h, uint8_t w, uint8_t kalinlik = 1);
                void dikdortgen_sil(uint8_t x, uint8_t y, uint8_t h, uint8_t w, uint8_t kalinlik = 1);
            } ici_bos;
        } cerceve;
    };

public: //________________________________oled main public___________________________
    ayarla ayarla;
    mod mod;
    geometri geometri;
    arkaplan arkaplan;
    font font;
    oled(uint8_t ekran_x_ = 128, uint8_t ekran_y_ = 64);
    ~oled();
    bool kur();
    void guncelle();
    void sil();
    void yaz(const String &str, uint8_t x, uint8_t y);
    void yaz(int sayi, uint8_t x, uint8_t y);
    void yaz(float sayi, uint8_t x, uint8_t y, uint8_t hassasiyet);
    void bitmap_ciz(uint8_t x, uint8_t y, uint8_t genislik, uint8_t yukseklik, const uint8_t *veri);

private: //____________________________oled main private_____________________________
    uint8_t __EKRAN_YUKSEKLIK;
    uint8_t __EKRAN_GENISLIK;
    uint16_t __SSD_PAKET_MAX;
    uint8_t __SATIR_MAX_KARAKTER_GENELFONT = (__EKRAN_GENISLIK / (__OLED_GENELFONT_XPIX + 1));

    uint8_t *buffer;
    // uint8_t _harfler_arasi_bosluk = 1;

    void hizalama_uygula(uint8_t &x, uint8_t y, uint8_t metin_uzunlugu);
    void yaz_(uint8_t x, uint8_t y, const char *yazi, bool hizli_modd = 1);
    void karakter_yaz(uint8_t x, uint8_t y, char ch, bool hizli_mod = false);
    void komut_gonder(uint8_t cmd);
    void veri_gonder(uint8_t *data, size_t len);
    void pixel_ac(uint8_t x, uint8_t y);
    void pixel_kapa(uint8_t x, uint8_t y);
    bool pixel_kontrol(uint8_t x, uint8_t y);

protected: //____________________________font private_____________________________
    enum font_isim
    {
        FONT_YAZI_GENEL,
        FONT_MINISAYI,
        FONT_BUYUKSAYI
    };
    font_isim font_isim_;
    const uint8_t *_font;    // seçiil font işaretçisi
    uint8_t genislik;        // Her karakterin genişliği (piksel)
    uint8_t yukseklik;       // Yükseklik (genelde 8 veya 16 piksel)
    uint8_t ilk_karakter;    // İlk karakterin ASCII kodu (genelde 32)
    uint8_t karakter_sayisi; // Fonttaki toplam karakter sayısı
    void font_sec(uint8_t num);
};
