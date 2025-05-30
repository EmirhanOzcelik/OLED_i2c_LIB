#pragma once

#if defined(ESP8266) || defined(ESP32)
#include "Arduino.h"
#include <Wire.h>
#define ___TEST 0
#define __SSD_ADRES 0x3C

#if ___TEST == 1
static void i2c_tarayici()
{
    Serial.println("I2C Cihaz Taraniyor...");
    byte hata, adres;
    int bulunanCihazSayisi = 0;

    for (adres = 1; adres < 127; adres++)
    {
        // beginTransmission() ile cihaza sorgu gönderilir
        Wire.beginTransmission(adres);
        // endTransmission() sorgunun sonucunu döndürür (0 = ACK, diğerleri hata)
        hata = Wire.endTransmission();

        if (hata == 0)
        {
            Serial.print("  I2C cihaz adresi: 0x");
            if (adres < 16)
            {
                Serial.print("0"); // Tek haneli adresler için öne sıfır ekle
            }
            Serial.println(adres, HEX);
            bulunanCihazSayisi++;
        }
        else if (hata == 4)
        {
            Serial.print("  Adreste bilinmeyen hata: 0x");
            if (adres < 16)
            {
                Serial.print("0");
            }
            Serial.println(adres, HEX);
        }
    }

    if (bulunanCihazSayisi == 0)
    {
        Serial.println("Hic I2C cihazi bulunamadi.");
    }
    else
    {
        Serial.print("Bitti. Toplam ");
        Serial.print(bulunanCihazSayisi);
        Serial.println(" cihaz bulundu.");
    }
}
#endif
static inline bool i2c_kur()
{
    Wire.begin(SDA, SCL);
    // Wire.setClock(100000);
     Wire.setClock(400000);
    // i2c_tarayici();
    Wire.beginTransmission(__SSD_ADRES);
    if (Wire.endTransmission() == 0)
        return true;
    else
        return false;
}

static inline void i2c_baslat()
{
    Wire.beginTransmission(__SSD_ADRES);
}

static inline void i2c_durdur()
{
    Wire.endTransmission();
}

static inline void i2c_yaz(uint8_t veri)
{
    Wire.write(veri);
}

#endif