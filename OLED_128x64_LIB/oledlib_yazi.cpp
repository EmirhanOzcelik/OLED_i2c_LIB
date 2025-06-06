#include "OLED_LIB.h"
#include "pgmspace.h"
#include "fontlar.h"

void oled::yaz_(uint8_t x, uint8_t y, const char *yazi, bool hizli_modd)
{
    uint8_t uzunluk = strlen(yazi);
    hizalama_uygula(x, y, uzunluk);

    while (*yazi)
    {
        bool ozel_karakter_islenmedi = true;
        uint8_t current_char_byte_0 = (uint8_t)*yazi;

        if (current_char_byte_0 >= 0xC2 && current_char_byte_0 <= 0xDF)
        {
            uint8_t current_char_byte_1 = (uint8_t)*(yazi + 1);

            switch (current_char_byte_0)
            {
            case 0xC3:
                switch (current_char_byte_1)
                {
                case 0x87:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_buyuk_C);
                    ozel_karakter_islenmedi = false;
                    break;
                case 0x96:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_buyuk_O);
                    ozel_karakter_islenmedi = false;
                    break;
                case 0x9C:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_buyuk_U);
                    ozel_karakter_islenmedi = false;
                    break;
                case 0xA7:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_kucuk_c);
                    ozel_karakter_islenmedi = false;
                    break;
                case 0xB6:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_kucuk_o);
                    ozel_karakter_islenmedi = false;
                    break;
                case 0xBC:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_kucuk_u);
                    ozel_karakter_islenmedi = false;
                    break;
                default:
                    break;
                }
                break;
            case 0xC4:
                switch (current_char_byte_1)
                {
                case 0xB0:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_buyuk_I);
                    ozel_karakter_islenmedi = false;
                    break;
                case 0x9E:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_buyuk_G);
                    ozel_karakter_islenmedi = false;
                    break;
                case 0x9F:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_kucuk_g);
                    ozel_karakter_islenmedi = false;
                    break;
                case 0xB1:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_kucuk_i_noktasiz);
                    ozel_karakter_islenmedi = false;
                    break;
                default:
                    break;
                }
                break;
            case 0xC5:
                switch (current_char_byte_1)
                {
                case 0x9E:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_buyuk_S);
                    ozel_karakter_islenmedi = false;
                    break;
                case 0x9F:
                    bitmap_ciz(x, y, genislik, yukseklik, turkce_kucuk_s);
                    ozel_karakter_islenmedi = false;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }

            if (!ozel_karakter_islenmedi)
            {
                yazi += 2;
                x += genislik + 1;
                continue;
            }
        }

        if (ozel_karakter_islenmedi)
        {
            karakter_yaz(x, y, *yazi, hizli_modd);
            x += genislik + 1;
            yazi++;
        }
    }
}

void oled::yaz(const String &str, uint8_t x, uint8_t y) { yaz_(x, y, (const char *)str.c_str()); }
void oled::yaz(int sayi, uint8_t x, uint8_t y)
{
    char buf[12];
    itoa(sayi, buf, 10);
    yaz_(x, y, buf);
}
void oled::yaz(float sayi, uint8_t x, uint8_t y, uint8_t hassasiyet = 2)
{
    char buf[20];
    dtostrf(sayi, 0, hassasiyet, buf);
    yaz_(x, y, buf);
}
void oled::hizalama_uygula(uint8_t &x, uint8_t y, uint8_t metin_uzunlugu)
{
    const uint8_t font_genislik = genislik;
    uint8_t toplam_genislik = metin_uzunlugu * font_genislik;
    switch (x)
    {
    case SOL:
        break;
    case ORTA:
        if (__EKRAN_GENISLIK > toplam_genislik)
            x = (__EKRAN_GENISLIK - toplam_genislik) / 2;
        else
            x = 0;
        break;
    case SAG:
        if (__EKRAN_GENISLIK > toplam_genislik)
            x = __EKRAN_GENISLIK - toplam_genislik;
        else
            x = 0;
        break;
    }
}

///_________________________________mod___________________________________________
void oled::mod::yaz(const char *k, int32_t a, uint8_t x, uint8_t y)
{
    char buf[32];
    char sayi[12]; 
    ltoa(a, sayi, 10); 
    uint8_t i = 0;
    while (k[i] && i < sizeof(buf) - 1)
    {
        buf[i] = k[i];
        i++;
    }
    if (i < sizeof(buf) - 1)
        buf[i++] = ' ';
    uint8_t j = 0;
    while (sayi[j] && i < sizeof(buf) - 1)
        buf[i++] = sayi[j++];
    buf[i] = '\0';
    mod_priv->yaz(buf, x, y);
}
void oled::mod::yaz(const String &k, int32_t a, uint8_t x, uint8_t y){yaz(k.c_str(), a, x, y);}

void oled::mod::yaz(char k, int32_t a, uint8_t x, uint8_t y)
{
    char buf[2] = {k, '\0'};
    yaz(buf, a, x, y);
}

///_________________________________mod___________________________________________
void oled::mod::altSatira_ortali_yaz(const char *k, int32_t a, uint8_t x, uint8_t y, bool buyuk)
{
    mod_priv->font.sec.yazi();
    mod_priv->yaz_(ORTA, y, k);
    char sayi_buf[16];
    snprintf(sayi_buf, sizeof(sayi_buf), "%d", a);
    if (buyuk)
        mod_priv->font.sec.buyukSayi();
    else
        mod_priv->font.sec.minikSayi();
    uint8_t sayi_y = y + __OLED_GENELFONT_YPIX + 6;
    mod_priv->yaz_(ORTA, sayi_y, sayi_buf);
    mod_priv->font.sec.yazi();
}
void oled::mod::altSatira_ortali_yaz(const String &yazi, int32_t sayi, uint8_t x, uint8_t y, bool buyuk) { altSatira_ortali_yaz(yazi.c_str(), sayi, x, y, buyuk); }
///_________________________________mod___________________________________________

void oled::mod::saat(uint8_t x, uint8_t y, uint8_t saat, uint8_t dk, uint8_t sn)
{
    char buf[16];
    if (sn == 254)
        snprintf(buf, sizeof(buf), "%02d:%02d", saat, dk);
    else
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d", saat, dk, sn);
    mod_priv->yaz_(x, y, buf);
}
void oled::mod::saat_orta(uint8_t x, uint8_t y, uint8_t saat, uint8_t dk, uint8_t sn)
{
    mod_priv->font.sec.minikSayi();
    mod_priv->mod.saat(x, y, saat, dk, sn);
    mod_priv->font.sec.yazi();
}
void oled::mod::saat_buyuk(uint8_t x, uint8_t y, uint8_t saat, uint8_t dk, uint8_t sn)
{
    mod_priv->font.sec.buyukSayi();
    mod_priv->mod.saat(x, y, saat, dk, sn);
    mod_priv->font.sec.yazi();
}
void oled::mod::tarih(uint8_t x, uint8_t y, uint8_t gun, uint8_t ay, uint16_t yil)
{
    if (mod_priv->_font != genelFont)
        mod_priv->font.sec.yazi(); 
    char buf[16];
    snprintf(buf, sizeof(buf), "%02d/%02d/%04d", gun, ay, yil);
    mod_priv->yaz_(x, y, buf); 
    mod_priv->font.sec.yazi(); 
}
void oled::mod::tarih(uint8_t x, uint8_t y, const char *haftaninGun, uint8_t gun, uint8_t ay, uint16_t yil, bool alta_yaz)
{
    if (mod_priv->_font != genelFont)
        mod_priv->font.sec.yazi(); 
    char buf[32];                                        
    snprintf(buf, sizeof(buf), "%02d/%02d/%02d", gun, ay, yil); 
    if (alta_yaz)
    {
        mod_priv->yaz_(x, y, buf); 
        uint8_t haftaninGunLength = strlen(haftaninGun) * mod_priv->genislik;    
        uint8_t center_x = x + (mod_priv->genislik * 10 - haftaninGunLength) / 2; 
        mod_priv->yaz_(center_x, y + 10, haftaninGun);
    }
    else
    {
        mod_priv->yaz_(x, y, buf); 
        uint8_t new_x = x + strlen(buf) * mod_priv->genislik; 
        snprintf(buf, sizeof(buf), "%s%s", " ", haftaninGun);
        mod_priv->yaz_(new_x, y, buf); 
    }

    mod_priv->font.sec.yazi(); // Fontu sıfırla
}

void oled::mod::tarih(uint8_t x, uint8_t y, const char *ay_isim, const char *haftaninGun, uint8_t gun, uint8_t ay, uint16_t yil, bool alta_yaz)
{
    if (mod_priv->_font != genelFont)
        mod_priv->font.sec.yazi(); 
    char tarih_buf[32]; 
    char yil_buf[10];   
    if (alta_yaz)
    {
        snprintf(tarih_buf, sizeof(tarih_buf), "%02d %s %s", gun, ay_isim, haftaninGun);
        mod_priv->yaz_(x, y, tarih_buf); 
        itoa(yil, yil_buf, 10); 
        uint8_t text_width = strlen(yil_buf) * mod_priv->genislik;        
        uint8_t center_x = x + (mod_priv->genislik * 13 - text_width) / 2; 
        mod_priv->yaz_(center_x, y + 10, yil_buf);
    }
    else
    {
        snprintf(tarih_buf, sizeof(tarih_buf), "%s %02d/%02d/%02d", haftaninGun, gun, ay, yil);
        mod_priv->yaz_(x, y, tarih_buf);
    }
    mod_priv->font.sec.yazi(); 
}
