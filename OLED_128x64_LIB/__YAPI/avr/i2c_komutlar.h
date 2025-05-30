#pragma once
#if defined(__AVR__)

#include <stdint.h>
#include <avr/io.h>

#define F_CPU_ 16000000UL
#define I2C_FREQ_ 100000UL

static inline bool i2c_kur()
{
    TWSR = 0x00; // Prescaler = 1
    TWBR = ((F_CPU_ / I2C_FREQ_) - 16) / 2;
    return true;
}

static inline void i2c_baslat(void)
{
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
}

static inline void i2c_durdur(void)
{
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

static inline void i2c_yaz(uint8_t veri)
{
    TWDR = veri;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ;
}

#endif