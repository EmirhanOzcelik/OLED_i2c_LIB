#include "OLED_LIB.h"
#include "__YAPI/ssd1306_.h"
#include "fontlar.h"

#define fontbyte(x) pgm_read_byte(&cfont.font[x])
#define bitmapbyte(x) pgm_read_byte(&bitmap[x])

void oled::ayarla::arkaplan_siyah()
{
    memset(ayar_priv->buffer, 0x00, ayar_priv->__SSD_PAKET_MAX);
    ayar_priv->guncelle();
}
void oled::ayarla::arkaplan_beyaz()
{
    memset(ayar_priv->buffer, 0xFF, ayar_priv->__SSD_PAKET_MAX);
    ayar_priv->guncelle();
}
void oled::ayarla::parlaklik(uint8_t deger)
{
    ayar_priv->komut_gonder(__SSD_KONTRAST_AYARLA);
    ayar_priv->komut_gonder(deger);
    ayar_priv->guncelle();
}
void oled::ayarla::ekran_ac()
{
    ayar_priv->komut_gonder(__SSD_EKRAN_AC);
}
void oled::ayarla::ekran_kapa()
{
    ayar_priv->komut_gonder(__SSD_EKRAN_KAPAT);
}
void oled::ayarla::ters_cevir()
{
    ayar_priv->komut_gonder(__SSD_SEGMENT_TERS);    // Horizontal segment remap (X ekseni ters çevir)
    ayar_priv->komut_gonder(__SSD_COM_TERS_TARAMA); // COM output scan direction (Y ekseni ters çevir)
}
void oled::ayarla::duze_cevir()
{
    ayar_priv->komut_gonder(__SSD_SEGMENT_NORMAL);    // Normal X ekseni
    ayar_priv->komut_gonder(__SSD_COM_TARAMA_NORMAL); // Normal Y ekseni
}
void oled::ayarla::renkleri_ters_cevir()
{
    ayar_priv->komut_gonder(__SSD_EKRAN_INVERT_ACIK); // Invert display on
}
void oled::ayarla::renkleri_normale_cevir()
{
    ayar_priv->komut_gonder(__SSD_EKRAN_INVERT_KAPALI); // Normal display (invert off)
}
void oled::font_sec(uint8_t num)
{
    switch (num)
    {
    case FONT_YAZI_GENEL:
        _font = genelFont;
        break;
    case FONT_MINISAYI:
        _font = orta_numara;
        break;
    case FONT_BUYUKSAYI:
        _font = buyuk_numara;
        break;
    }
    genislik = pgm_read_byte(&_font[0]);
    yukseklik = pgm_read_byte(&_font[1]);
    ilk_karakter = pgm_read_byte(&_font[2]);
    karakter_sayisi = pgm_read_byte(&_font[3]);
}

///
///
///
///
void oled::karakter_yaz(uint8_t x, uint8_t y, char ch, bool hizli_mod)
{
    if (ch < ilk_karakter || ch >= ilk_karakter + karakter_sayisi)
        return;

    if (x >= __EKRAN_GENISLIK || y >= __EKRAN_YUKSEKLIK)
        return;

    uint8_t max_genislik = (__EKRAN_GENISLIK > x) ? (__EKRAN_GENISLIK - x) : 0;
    uint8_t yazilacak_genislik = (genislik <= max_genislik) ? genislik : max_genislik;

    uint8_t satir_byte_sayisi = (yukseklik + 7) / 8;
    uint16_t index = 4 + (ch - ilk_karakter) * (genislik * satir_byte_sayisi);

    // Sadece hızlı mod ve 8 piksel yüksekliğe kadar olan fontlar için optimize çizim
    if (hizli_mod && yukseklik <= 8 && (y % 8 == 0))
    {
        uint8_t page = y / 8;
        uint16_t buffer_index = page * __EKRAN_GENISLIK + x;

        for (uint8_t i = 0; i < yazilacak_genislik; i++)
        {
            buffer[buffer_index + i] |= pgm_read_byte(&_font[index + i]);
        }
    }
    else
    {
        // Diğer tüm durumlarda normal bitmap çizimi kullan
        bitmap_ciz(x, y, yazilacak_genislik, yukseklik, &_font[index]);
    }
}

void oled::bitmap_ciz(uint8_t x, uint8_t y, uint8_t genislik, uint8_t yukseklik, const uint8_t *veri)
{
    uint8_t flipMod = ayarla.bitmap._flip_mod;
    uint8_t donmeMod = ayarla.bitmap._donme_mod;

    uint8_t byte_height = (yukseklik + 7) / 8;

    for (uint8_t i = 0; i < genislik; i++)
    {
        for (uint8_t b = 0; b < byte_height; b++)
        {
            uint8_t data = pgm_read_byte(veri + i + b * genislik);
            for (uint8_t bit = 0; bit < 8; bit++)
            {
                uint8_t px = i;
                uint8_t py = b * 8 + bit;
                if (py >= yukseklik)
                    continue;

                if (!(data & (1 << bit)))
                    continue;

                // Aynalama işlemleri
                if (flipMod == __FLIP_X || flipMod == __FLIP_XY)
                    px = genislik - 1 - px;
                if (flipMod == __FLIP_Y || flipMod == __FLIP_XY)
                    py = yukseklik - 1 - py;

                // Döndürme işlemleri
                uint8_t ekran_x = x, ekran_y = y;
                switch (donmeMod)
                {
                case __DONME_0:
                    ekran_x += px;
                    ekran_y += py;
                    break;
                case __DONME_90:
                    ekran_x += py;
                    ekran_y += genislik - 1 - px;
                    break;
                case __DONME_180:
                    ekran_x += genislik - 1 - px;
                    ekran_y += yukseklik - 1 - py;
                    break;
                case __DONME_270:
                    ekran_x += yukseklik - 1 - py;
                    ekran_y += px;
                    break;
                }

                if (ekran_x < __EKRAN_GENISLIK && ekran_y < __EKRAN_YUKSEKLIK)
                    pixel_ac(ekran_x, ekran_y);
            }
        }
    }
}