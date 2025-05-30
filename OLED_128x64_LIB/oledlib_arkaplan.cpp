#include "OLED_LIB.h"

#define x_baslangic 12
#define IMLEC_X 0
#define IMLEC_OFFSET_Y 0

uint16_t imlec_satiri = 0;
uint16_t imlecc = 0;
uint16_t son_toplam_satir = 0;

void oled::arkaplan::paragraf_goruntuleyici(const char *metin, uint8_t azaltici, uint8_t arttirici, uint8_t max_ekran_satiri)
{
    if (max_ekran_satiri > 7)
        return;
    const uint16_t satir_karakter_sayisi = arkaplan_priv->__SATIR_MAX_KARAKTER_GENELFONT - 2;
    const uint16_t metin_uzunluk = strlen(metin);
    const uint16_t toplam_satir = (metin_uzunluk + satir_karakter_sayisi - 1) / satir_karakter_sayisi;
    if (metin_uzunluk != son_toplam_satir)
    {
        son_toplam_satir = metin_uzunluk;
        imlec_satiri = toplam_satir > 0 ? toplam_satir - 1 : 0;
        imlecc = toplam_satir > max_ekran_satiri ? toplam_satir - max_ekran_satiri : 0;
    }
    if (azaltici > 0 && imlec_satiri > 0)
        imlec_satiri--;
    else if (arttirici > 0 && imlec_satiri < toplam_satir - 1)
        imlec_satiri++;

    if (imlec_satiri < imlecc)
        imlecc = imlec_satiri;
    else if (imlec_satiri >= imlecc + max_ekran_satiri)
        imlecc = imlec_satiri - max_ekran_satiri + 1;
    for (uint8_t c = 0; c < max_ekran_satiri; c++)
    {
        uint16_t satir_index = imlecc + c;
        if (satir_index >= toplam_satir)
        {
            arkaplan_priv->yaz(" ", 0, c * 8);
            arkaplan_priv->yaz(" ", x_baslangic, c * 8);
            continue;
        }
        uint16_t baslangic = satir_index * satir_karakter_sayisi;
        uint16_t bitis = baslangic + satir_karakter_sayisi;
        if (bitis > metin_uzunluk)
            bitis = metin_uzunluk;
        char satir_buf[arkaplan_priv->__SATIR_MAX_KARAKTER_GENELFONT + 1];
        uint16_t uzunluk = bitis - baslangic;
        if (uzunluk > arkaplan_priv->__SATIR_MAX_KARAKTER_GENELFONT)
            uzunluk = arkaplan_priv->__SATIR_MAX_KARAKTER_GENELFONT;
        memcpy(satir_buf, &metin[baslangic], uzunluk);
        satir_buf[uzunluk] = '\0';
        arkaplan_priv->yaz(" ", 0, c * 8);
        arkaplan_priv->yaz(satir_buf, x_baslangic, c * 8);
    }
    uint8_t toplam_gorunur_px = max_ekran_satiri * 8;
    float orani = (toplam_satir > 1) ? (float)imlec_satiri / (toplam_satir - 1) : 0;
    uint8_t imlec_y = (uint8_t)(orani * (toplam_gorunur_px - 1));
    for (uint8_t i = 0; i < toplam_gorunur_px; i++)
        arkaplan_priv->yaz(" ", IMLEC_X, i);
    arkaplan_priv->geometri.cerceve.ici_bos.dikdortgen_ciz(0, 0, toplam_gorunur_px, 6);
    arkaplan_priv->geometri.cerceve.ici_dolu.dikdortgen_ciz(0, imlec_y + IMLEC_OFFSET_Y, 10 - max_ekran_satiri, 6);
}
void oled::arkaplan::paragraf_goruntuleyici(const String &metin, uint8_t azaltici, uint8_t arttirici, uint8_t max_ekran_satiri) { paragraf_goruntuleyici(metin.c_str(), azaltici, arttirici, max_ekran_satiri); }
