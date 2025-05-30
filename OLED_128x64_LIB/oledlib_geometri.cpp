#include "OLED_LIB.h"
template <typename T>
inline void swap_(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
bool oled::geometri::nokta_kontrol(uint8_t x, uint8_t y) { return geometri_priv->pixel_kontrol(x, y); }
void oled::geometri::nokta_ciz(uint8_t x, uint8_t y) { geometri_priv->pixel_ac(x, y); }
void oled::geometri::nokta_sil(uint8_t x, uint8_t y) { geometri_priv->pixel_kapa(x, y); }
void oled::geometri::cizgi::ciz::cizgi_(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t kalinlik)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true)
    {
        for (int i = -kalinlik / 2; i <= kalinlik / 2; i++)
        {
            for (int j = -kalinlik / 2; j <= kalinlik / 2; j++)
            {
                int px = x0 + i;
                int py = y0 + j;
                if (px >= 0 && px < ciz_cizgi_priv->__EKRAN_GENISLIK && py >= 0 && py < ciz_cizgi_priv->__EKRAN_YUKSEKLIK)
                {
                    ciz_cizgi_priv->geometri.nokta_ciz(px, py);
                }
            }
        }

        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
void oled::geometri::cizgi::sil::cizgi_(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t kalinlik)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true)
    {
        for (int i = -kalinlik / 2; i <= kalinlik / 2; i++)
        {
            for (int j = -kalinlik / 2; j <= kalinlik / 2; j++)
            {
                int px = x0 + i;
                int py = y0 + j;
                if (px >= 0 && px < sil_cizgi_priv->__EKRAN_GENISLIK && py >= 0 && py < sil_cizgi_priv->__EKRAN_YUKSEKLIK)
                {
                    sil_cizgi_priv->geometri.nokta_sil(px, py);
                }
            }
        }

        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void oled::geometri::cizgi::ciz::yatay(uint8_t x, uint8_t y, uint8_t uzunluk, uint8_t kalinlik)
{
    if (y >= ciz_cizgi_priv->__EKRAN_YUKSEKLIK)
        return;
    if (y + kalinlik > ciz_cizgi_priv->__EKRAN_YUKSEKLIK)
        kalinlik = ciz_cizgi_priv->__EKRAN_YUKSEKLIK - y;
    if (x >= ciz_cizgi_priv->__EKRAN_GENISLIK)
        return;
    if (x + uzunluk > ciz_cizgi_priv->__EKRAN_GENISLIK)
        uzunluk = ciz_cizgi_priv->__EKRAN_GENISLIK - x;

    for (uint8_t c = 0; c < kalinlik; c++)
    {
        uint8_t y_pos = y + c;
        uint8_t sayfa = y_pos >> 3;
        uint8_t bit = y_pos & 0x07;
        uint8_t mask = 1 << bit;

        for (uint8_t col = x; col < x + uzunluk; col++)
        {
            ciz_cizgi_priv->buffer[col + sayfa * ciz_cizgi_priv->__EKRAN_GENISLIK] |= mask;
        }
    }
}
void oled::geometri::cizgi::ciz::dikey(uint8_t x, uint8_t y, uint8_t uzunluk, uint8_t kalinlik)
{
    if (x >= ciz_cizgi_priv->__EKRAN_GENISLIK || y >= ciz_cizgi_priv->__EKRAN_YUKSEKLIK)
        return;
    if (y + uzunluk > ciz_cizgi_priv->__EKRAN_YUKSEKLIK)
        uzunluk = ciz_cizgi_priv->__EKRAN_YUKSEKLIK - y;
    if (kalinlik == 0)
        return;

    for (uint8_t k = 0; k < kalinlik; k++)
    {
        for (int i = 0; i < uzunluk; i++)
        {
            ciz_cizgi_priv->geometri.nokta_ciz(x + k, y + i);
        }
    }
}
void oled::geometri::cizgi::sil::yatay(uint8_t x, uint8_t y, uint8_t uzunluk, uint8_t kalinlik)
{
    if (y >= sil_cizgi_priv->__EKRAN_YUKSEKLIK)
        return;
    if (y + kalinlik > sil_cizgi_priv->__EKRAN_YUKSEKLIK)
        kalinlik = sil_cizgi_priv->__EKRAN_YUKSEKLIK - y;
    if (x >= sil_cizgi_priv->__EKRAN_GENISLIK)
        return;
    if (x + uzunluk > sil_cizgi_priv->__EKRAN_GENISLIK)
        uzunluk = sil_cizgi_priv->__EKRAN_GENISLIK - x;

    for (uint8_t c = 0; c < kalinlik; c++)
    {
        uint8_t y_pos = y + c;
        uint8_t sayfa = y_pos >> 3;
        uint8_t bit = y_pos & 0x07;
        uint8_t mask = ~(1 << bit);

        for (uint8_t col = x; col < x + uzunluk; col++)
        {
            sil_cizgi_priv->buffer[col + sayfa * sil_cizgi_priv->__EKRAN_GENISLIK] &= mask;
        }
    }
}
void oled::geometri::cizgi::sil::dikey(uint8_t x, uint8_t y, uint8_t uzunluk, uint8_t kalinlik)
{
    if (x >= sil_cizgi_priv->__EKRAN_GENISLIK || y >= sil_cizgi_priv->__EKRAN_YUKSEKLIK)
        return;
    if (y + uzunluk > sil_cizgi_priv->__EKRAN_YUKSEKLIK)
        uzunluk = sil_cizgi_priv->__EKRAN_YUKSEKLIK - y;
    if (kalinlik == 0)
        return;

    for (uint8_t k = 0; k < kalinlik; k++)
    {
        for (int i = 0; i < uzunluk; i++)
        {
            sil_cizgi_priv->geometri.nokta_sil(x + k, y + i);
        }
    }
}
void oled::geometri::cerceve::ici_bos::dikdortgen_ciz(uint8_t x, uint8_t y, uint8_t h, uint8_t w, uint8_t kalinlik)
{
    // Yatay kenarlar (üst ve alt)
    for (uint8_t i = 0; i < kalinlik; i++)
    {
        uint8_t yy = y + i;
        if (yy < ici_bos_priv->__EKRAN_YUKSEKLIK)
        {
            uint8_t s = yy >> 3;
            uint8_t b = 1 << (yy & 7);
            for (uint8_t j = x; j < x + w && j < ici_bos_priv->__EKRAN_GENISLIK; j++)
            {
                ici_bos_priv->buffer[j + s * ici_bos_priv->__EKRAN_GENISLIK] |= b;
            }
        }

        uint8_t yy2 = y + h - 1 - i;
        if (yy2 < ici_bos_priv->__EKRAN_YUKSEKLIK)
        {
            uint8_t s = yy2 >> 3;
            uint8_t b = 1 << (yy2 & 7);
            for (uint8_t j = x; j < x + w && j < ici_bos_priv->__EKRAN_GENISLIK; j++)
            {
                ici_bos_priv->buffer[j + s * ici_bos_priv->__EKRAN_GENISLIK] |= b;
            }
        }
    }

    // Dikey kenarlar (sol ve sağ)
    for (uint8_t i = 0; i < kalinlik; i++)
    {
        uint8_t xx = x + i;
        if (xx < ici_bos_priv->__EKRAN_GENISLIK)
        {
            for (uint8_t j = y; j < y + h && j < ici_bos_priv->__EKRAN_YUKSEKLIK; j++)
            {
                uint8_t s = j >> 3;
                uint8_t b = 1 << (j & 7);
                ici_bos_priv->buffer[xx + s * ici_bos_priv->__EKRAN_GENISLIK] |= b;
            }
        }

        uint8_t xx2 = x + w - 1 - i;
        if (xx2 < ici_bos_priv->__EKRAN_GENISLIK)
        {
            for (uint8_t j = y; j < y + h && j < ici_bos_priv->__EKRAN_YUKSEKLIK; j++)
            {
                uint8_t s = j >> 3;
                uint8_t b = 1 << (j & 7);
                ici_bos_priv->buffer[xx2 + s * ici_bos_priv->__EKRAN_GENISLIK] |= b;
            }
        }
    }
}
void oled::geometri::cerceve::ici_bos::dikdortgen_sil(uint8_t x, uint8_t y, uint8_t h, uint8_t w, uint8_t kalinlik)
{
    // Yatay kenarlar (üst ve alt)
    for (uint8_t i = 0; i < kalinlik; i++)
    {
        uint8_t yy = y + i;
        if (yy < ici_bos_priv->__EKRAN_YUKSEKLIK)
        {
            uint8_t s = yy >> 3;
            uint8_t b = 1 << (yy & 7);
            for (uint8_t j = x; j < x + w && j < ici_bos_priv->__EKRAN_GENISLIK; j++)
            {
                ici_bos_priv->buffer[j + s * ici_bos_priv->__EKRAN_GENISLIK] &= ~b;
            }
        }

        uint8_t yy2 = y + h - 1 - i;
        if (yy2 < ici_bos_priv->__EKRAN_YUKSEKLIK)
        {
            uint8_t s = yy2 >> 3;
            uint8_t b = 1 << (yy2 & 7);
            for (uint8_t j = x; j < x + w && j < ici_bos_priv->__EKRAN_GENISLIK; j++)
            {
                ici_bos_priv->buffer[j + s * ici_bos_priv->__EKRAN_GENISLIK] &= ~b;
            }
        }
    }

    // Dikey kenarlar (sol ve sağ)
    for (uint8_t i = 0; i < kalinlik; i++)
    {
        uint8_t xx = x + i;
        if (xx < ici_bos_priv->__EKRAN_GENISLIK)
        {
            for (uint8_t j = y; j < y + h && j < ici_bos_priv->__EKRAN_YUKSEKLIK; j++)
            {
                uint8_t s = j >> 3;
                uint8_t b = 1 << (j & 7);
                ici_bos_priv->buffer[xx + s * ici_bos_priv->__EKRAN_GENISLIK] &= ~b;
            }
        }

        uint8_t xx2 = x + w - 1 - i;
        if (xx2 < ici_bos_priv->__EKRAN_GENISLIK)
        {
            for (uint8_t j = y; j < y + h && j < ici_bos_priv->__EKRAN_YUKSEKLIK; j++)
            {
                uint8_t s = j >> 3;
                uint8_t b = 1 << (j & 7);
                ici_bos_priv->buffer[xx2 + s * ici_bos_priv->__EKRAN_GENISLIK] &= ~b;
            }
        }
    }
}
void oled::geometri::cerceve::ici_dolu::dikdortgen_ciz(uint8_t x, uint8_t y, uint8_t h, uint8_t w)
{
    if (x >= ici_dolu_priv->__EKRAN_GENISLIK || y >= ici_dolu_priv->__EKRAN_YUKSEKLIK)
        return;

    if (x + w > ici_dolu_priv->__EKRAN_GENISLIK)
        w = ici_dolu_priv->__EKRAN_GENISLIK - x;
    if (y + h > ici_dolu_priv->__EKRAN_YUKSEKLIK)
        h = ici_dolu_priv->__EKRAN_YUKSEKLIK - y;

    for (uint8_t yy = y; yy < y + h; yy++)
    {
        uint8_t s = yy >> 3;
        uint8_t b = 1 << (yy & 7);
        for (uint8_t xx = x; xx < x + w; xx++)
        {
            ici_dolu_priv->buffer[xx + s * ici_dolu_priv->__EKRAN_GENISLIK] |= b;
        }
    }
}
void oled::geometri::cerceve::ici_dolu::dikdortgen_sil(uint8_t x, uint8_t y, uint8_t h, uint8_t w)
{
    if (x >= ici_dolu_priv->__EKRAN_GENISLIK || y >= ici_dolu_priv->__EKRAN_YUKSEKLIK)
        return;

    if (x + w > ici_dolu_priv->__EKRAN_GENISLIK)
        w = ici_dolu_priv->__EKRAN_GENISLIK - x;
    if (y + h > ici_dolu_priv->__EKRAN_YUKSEKLIK)
        h = ici_dolu_priv->__EKRAN_YUKSEKLIK - y;

    for (uint8_t yy = y; yy < y + h; yy++)
    {
        uint8_t s = yy >> 3;
        uint8_t b = 1 << (yy & 7);
        for (uint8_t xx = x; xx < x + w; xx++)
        {
            ici_dolu_priv->buffer[xx + s * ici_dolu_priv->__EKRAN_GENISLIK] &= ~b;
        }
    }
}
void oled::geometri::cerceve::ici_bos::ucgen_ciz(uint8_t x0, uint8_t y0,
                                                 uint8_t x1, uint8_t y1,
                                                 uint8_t x2, uint8_t y2)
{
    ici_bos_priv->geometri.cizgi.ciz.cizgi_(x0, y0, x1, y1);
    ici_bos_priv->geometri.cizgi.ciz.cizgi_(x1, y1, x2, y2);
    ici_bos_priv->geometri.cizgi.ciz.cizgi_(x2, y2, x0, y0);
}
void oled::geometri::cerceve::ici_bos::ucgen_sil(uint8_t x0, uint8_t y0,
                                                 uint8_t x1, uint8_t y1,
                                                 uint8_t x2, uint8_t y2)
{
    ici_bos_priv->geometri.cizgi.sil.cizgi_(x0, y0, x1, y1);
    ici_bos_priv->geometri.cizgi.sil.cizgi_(x1, y1, x2, y2);
    ici_bos_priv->geometri.cizgi.sil.cizgi_(x2, y2, x0, y0);
}
void oled::geometri::cerceve::ici_dolu::ucgen_ciz(uint8_t x0, uint8_t y0,
                                                  uint8_t x1, uint8_t y1,
                                                  uint8_t x2, uint8_t y2)
{
    // Y sırasına göre noktaları sırala
    if (y0 > y1)
    {
        swap_(x0, x1);
        swap_(y0, y1);
    }
    if (y1 > y2)
    {
        swap_(x1, x2);
        swap_(y1, y2);
    }
    if (y0 > y1)
    {
        swap_(x0, x1);
        swap_(y0, y1);
    }

    auto draw_scanline = [&](int y, int xa, int xb)
    {
        if (xa > xb)
            swap_(xa, xb);
        for (int x = xa; x <= xb; x++)
            ici_dolu_priv->geometri.nokta_ciz(x, y);
    };

    auto interpolate = [](int y0, int y1, int x0, int x1, int y)
    {
        if (y1 == y0)
            return x0;
        return x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    };

    for (int y = y0; y <= y2; y++)
    {
        bool lower = y < y1;
        int xa = interpolate(y0, y2, x0, x2, y);
        int xb = lower ? interpolate(y0, y1, x0, x1, y) : interpolate(y1, y2, x1, x2, y);
        draw_scanline(y, xa, xb);
    }
}
void oled::geometri::cerceve::ici_dolu::ucgen_sil(uint8_t x0, uint8_t y0,
                                                  uint8_t x1, uint8_t y1,
                                                  uint8_t x2, uint8_t y2)
{
    // Y sırasına göre noktaları sırala
    if (y0 > y1)
    {
        swap_(x0, x1);
        swap_(y0, y1);
    }
    if (y1 > y2)
    {
        swap_(x1, x2);
        swap_(y1, y2);
    }
    if (y0 > y1)
    {
        swap_(x0, x1);
        swap_(y0, y1);
    }

    auto draw_scanline = [&](int y, int xa, int xb)
    {
        if (xa > xb)
            swap_(xa, xb);
        for (int x = xa; x <= xb; x++)
            ici_dolu_priv->geometri.nokta_sil(x, y);
    };

    auto interpolate = [](int y0, int y1, int x0, int x1, int y)
    {
        if (y1 == y0)
            return x0;
        return x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    };

    for (int y = y0; y <= y2; y++)
    {
        bool lower = y < y1;
        int xa = interpolate(y0, y2, x0, x2, y);
        int xb = lower ? interpolate(y0, y1, x0, x1, y) : interpolate(y1, y2, x1, x2, y);
        draw_scanline(y, xa, xb);
    }
}
void oled::geometri::cerceve::ici_bos::cember_ciz(uint8_t merkez_x, uint8_t merkez_y, uint8_t r, uint8_t kalinlik)
{
    for (int radius = r; radius > (int)r - kalinlik && radius > 0; radius--)
    {
        int x = radius;
        int y = 0;
        int err = 0;

        while (x >= y)
        {
            ici_bos_priv->geometri.nokta_ciz(merkez_x + x, merkez_y + y);
            ici_bos_priv->geometri.nokta_ciz(merkez_x + y, merkez_y + x);
            ici_bos_priv->geometri.nokta_ciz(merkez_x - y, merkez_y + x);
            ici_bos_priv->geometri.nokta_ciz(merkez_x - x, merkez_y + y);
            ici_bos_priv->geometri.nokta_ciz(merkez_x - x, merkez_y - y);
            ici_bos_priv->geometri.nokta_ciz(merkez_x - y, merkez_y - x);
            ici_bos_priv->geometri.nokta_ciz(merkez_x + y, merkez_y - x);
            ici_bos_priv->geometri.nokta_ciz(merkez_x + x, merkez_y - y);

            if (err <= 0)
            {
                y++;
                err += 2 * y + 1;
            }
            if (err > 0)
            {
                x--;
                err -= 2 * x + 1;
            }
        }
    }
}

void oled::geometri::cerceve::ici_bos::cember_sil(uint8_t merkez_x, uint8_t merkez_y, uint8_t r, uint8_t kalinlik)
{
    for (int radius = r; radius > (int)r - kalinlik && radius > 0; radius--)
    {
        int x = radius;
        int y = 0;
        int err = 0;

        while (x >= y)
        {
            ici_bos_priv->geometri.nokta_sil(merkez_x + x, merkez_y + y);
            ici_bos_priv->geometri.nokta_sil(merkez_x + y, merkez_y + x);
            ici_bos_priv->geometri.nokta_sil(merkez_x - y, merkez_y + x);
            ici_bos_priv->geometri.nokta_sil(merkez_x - x, merkez_y + y);
            ici_bos_priv->geometri.nokta_sil(merkez_x - x, merkez_y - y);
            ici_bos_priv->geometri.nokta_sil(merkez_x - y, merkez_y - x);
            ici_bos_priv->geometri.nokta_sil(merkez_x + y, merkez_y - x);
            ici_bos_priv->geometri.nokta_sil(merkez_x + x, merkez_y - y);

            if (err <= 0)
            {
                y++;
                err += 2 * y + 1;
            }
            if (err > 0)
            {
                x--;
                err -= 2 * x + 1;
            }
        }
    }
}
void oled::geometri::cerceve::ici_dolu::cember_ciz(uint8_t merkez_x, uint8_t merkez_y, uint8_t r)
{
    int x = r;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        // Yatay çizgiler ile içi dolu çember çizimi
        for (int dy = -y; dy <= y; dy++)
        {
            ici_dolu_priv->geometri.nokta_ciz(merkez_x + x, merkez_y + dy);
            ici_dolu_priv->geometri.nokta_ciz(merkez_x - x, merkez_y + dy);
        }
        for (int dy = -x; dy <= x; dy++)
        {
            ici_dolu_priv->geometri.nokta_ciz(merkez_x + y, merkez_y + dy);
            ici_dolu_priv->geometri.nokta_ciz(merkez_x - y, merkez_y + dy);
        }

        if (err <= 0)
        {
            y++;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            x--;
            err -= 2 * x + 1;
        }
    }
}
void oled::geometri::cerceve::ici_dolu::cember_sil(uint8_t merkez_x, uint8_t merkez_y, uint8_t r)
{
    int x = r;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        // Yatay çizgiler ile içi dolu çember silimi
        for (int dy = -y; dy <= y; dy++)
        {
            ici_dolu_priv->geometri.nokta_sil(merkez_x + x, merkez_y + dy);
            ici_dolu_priv->geometri.nokta_sil(merkez_x - x, merkez_y + dy);
        }
        for (int dy = -x; dy <= x; dy++)
        {
            ici_dolu_priv->geometri.nokta_sil(merkez_x + y, merkez_y + dy);
            ici_dolu_priv->geometri.nokta_sil(merkez_x - y, merkez_y + dy);
        }

        if (err <= 0)
        {
            y++;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            x--;
            err -= 2 * x + 1;
        }
    }
}
void oled::geometri::cerceve::ici_bos::elips_ciz(int cx, int cy, int a, int b, uint8_t kalinlik)
{
    for (int radius = 0; radius < kalinlik; radius++)
    {
        int aa = a - radius;
        int bb = b - radius;
        if (aa <= 0 || bb <= 0)
            break;

        int x = 0;
        int y = bb;
        int a2 = aa * aa;
        int b2 = bb * bb;
        int crit1 = -(a2 / 4 + aa % 2 + b2);
        int crit2 = -(b2 / 4 + bb % 2 + a2);
        int crit3 = -(b2 / 4 + bb % 2);
        int t = -a2 * y;
        int dxt = 2 * b2 * x;
        int dyt = -2 * a2 * y;

        while (y >= 0 && x <= aa)
        {
            ici_bos_priv->geometri.nokta_ciz(cx + x, cy + y);
            ici_bos_priv->geometri.nokta_ciz(cx - x, cy + y);
            ici_bos_priv->geometri.nokta_ciz(cx - x, cy - y);
            ici_bos_priv->geometri.nokta_ciz(cx + x, cy - y);

            if (t + b2 * x <= crit1 || t + a2 * y <= crit3)
            {
                x++;
                dxt += 2 * b2;
                t += dxt;
            }
            else if (t - a2 * y > crit2)
            {
                y--;
                dyt += 2 * a2;
                t += dyt;
            }
            else
            {
                x++;
                dxt += 2 * b2;
                t += dxt;
                y--;
                dyt += 2 * a2;
                t += dyt;
            }
        }
    }
}
void oled::geometri::cerceve::ici_bos::elips_sil(int cx, int cy, int a, int b, uint8_t kalinlik)
{
    for (int radius = 0; radius < kalinlik; radius++)
    {
        int aa = a - radius;
        int bb = b - radius;
        if (aa <= 0 || bb <= 0)
            break;

        int x = 0;
        int y = bb;
        int a2 = aa * aa;
        int b2 = bb * bb;
        int crit1 = -(a2 / 4 + aa % 2 + b2);
        int crit2 = -(b2 / 4 + bb % 2 + a2);
        int crit3 = -(b2 / 4 + bb % 2);
        int t = -a2 * y;
        int dxt = 2 * b2 * x;
        int dyt = -2 * a2 * y;

        while (y >= 0 && x <= aa)
        {
            ici_bos_priv->geometri.nokta_sil(cx + x, cy + y);
            ici_bos_priv->geometri.nokta_sil(cx - x, cy + y);
            ici_bos_priv->geometri.nokta_sil(cx - x, cy - y);
            ici_bos_priv->geometri.nokta_sil(cx + x, cy - y);

            if (t + b2 * x <= crit1 || t + a2 * y <= crit3)
            {
                x++;
                dxt += 2 * b2;
                t += dxt;
            }
            else if (t - a2 * y > crit2)
            {
                y--;
                dyt += 2 * a2;
                t += dyt;
            }
            else
            {
                x++;
                dxt += 2 * b2;
                t += dxt;
                y--;
                dyt += 2 * a2;
                t += dyt;
            }
        }
    }
}
void oled::geometri::cerceve::ici_dolu::elips_ciz(int cx, int cy, int a, int b)
{
    int a2 = a * a;
    int b2 = b * b;
    int x = 0;
    int y = b;
    int sigma = 2 * b2 + a2 * (1 - 2 * b);

    while (b2 * x <= a2 * y)
    {
        // Tarama çizgileri yatay olarak içi doldur
        for (int i = cx - x; i <= cx + x; i++)
        {
            ici_dolu_priv->geometri.nokta_ciz(i, cy + y);
            ici_dolu_priv->geometri.nokta_ciz(i, cy - y);
        }

        if (sigma >= 0)
        {
            sigma += 4 * a2 * (1 - y);
            y--;
        }
        sigma += b2 * (4 * x + 6);
        x++;
    }

    x = a;
    y = 0;
    sigma = 2 * a2 + b2 * (1 - 2 * a);

    while (a2 * y <= b2 * x)
    {
        // Tarama çizgileri yatay olarak içi doldur
        for (int i = cx - x; i <= cx + x; i++)
        {
            ici_dolu_priv->geometri.nokta_ciz(i, cy + y);
            ici_dolu_priv->geometri.nokta_ciz(i, cy - y);
        }

        if (sigma >= 0)
        {
            sigma += 4 * b2 * (1 - x);
            x--;
        }
        sigma += a2 * (4 * y + 6);
        y++;
    }
}
void oled::geometri::cerceve::ici_dolu::elips_sil(int cx, int cy, int a, int b)
{
    int a2 = a * a;
    int b2 = b * b;
    int x = 0;
    int y = b;
    int sigma = 2 * b2 + a2 * (1 - 2 * b);

    while (b2 * x <= a2 * y)
    {
        // Tarama çizgileri yatay olarak içi sil
        for (int i = cx - x; i <= cx + x; i++)
        {
            ici_dolu_priv->geometri.nokta_sil(i, cy + y);
            ici_dolu_priv->geometri.nokta_sil(i, cy - y);
        }

        if (sigma >= 0)
        {
            sigma += 4 * a2 * (1 - y);
            y--;
        }
        sigma += b2 * (4 * x + 6);
        x++;
    }

    x = a;
    y = 0;
    sigma = 2 * a2 + b2 * (1 - 2 * a);

    while (a2 * y <= b2 * x)
    {
        // Tarama çizgileri yatay olarak içi sil
        for (int i = cx - x; i <= cx + x; i++)
        {
            ici_dolu_priv->geometri.nokta_sil(i, cy + y);
            ici_dolu_priv->geometri.nokta_sil(i, cy - y);
        }

        if (sigma >= 0)
        {
            sigma += 4 * b2 * (1 - x);
            x--;
        }
        sigma += a2 * (4 * y + 6);
        y++;
    }
}
void oled::geometri::cerceve::ici_bos::daire_dilimi_ciz(
    int cx, int cy, int r, float start_angle_deg, float end_angle_deg, uint8_t kalinlik)
{
    // Dereceyi radyana çevir
    float start_rad = start_angle_deg * 3.14159265f / 180.0f;
    float end_rad = end_angle_deg * 3.14159265f / 180.0f;

    // Kalınlık kadar içeri doğru çember dilimleri çiz
    for (int radius = r; radius > (int)r - kalinlik && radius > 0; radius--)
    {
        // Açı aralığında küçük adımlarla noktalar çiz
        for (float angle = start_rad; angle <= end_rad; angle += 0.01f)
        {
            int px = cx + (int)(radius * cosf(angle));
            int py = cy + (int)(radius * sinf(angle));
            ici_bos_priv->geometri.nokta_ciz(px, py);
        }
    }
}
void oled::geometri::cerceve::ici_bos::daire_dilimi_sil(
    int cx, int cy, int r, float start_angle_deg, float end_angle_deg, uint8_t kalinlik)
{
    float start_rad = start_angle_deg * 3.14159265f / 180.0f;
    float end_rad = end_angle_deg * 3.14159265f / 180.0f;

    for (int radius = r; radius > (int)r - kalinlik && radius > 0; radius--)
    {
        for (float angle = start_rad; angle <= end_rad; angle += 0.01f)
        {
            int px = cx + (int)(radius * cosf(angle));
            int py = cy + (int)(radius * sinf(angle));
            ici_bos_priv->geometri.nokta_sil(px, py);
        }
    }
}
void oled::geometri::cerceve::ici_dolu::daire_dilimi_ciz(
    int cx, int cy, int r, float start_angle_deg, float end_angle_deg)
{
    float start_rad = start_angle_deg * 3.14159265f / 180.0f;
    float end_rad = end_angle_deg * 3.14159265f / 180.0f;

    // Açı aralığında küçük adımlarla yarıçap boyunca nokta çiz
    for (float angle = start_rad; angle <= end_rad; angle += 0.01f)
    {
        float cos_a = cosf(angle);
        float sin_a = sinf(angle);

        for (int radius = 0; radius <= r; radius++)
        {
            int px = cx + (int)(radius * cos_a);
            int py = cy + (int)(radius * sin_a);
            ici_dolu_priv->geometri.nokta_ciz(px, py);
        }
    }
}
void oled::geometri::cerceve::ici_dolu::daire_dilimi_sil(
    int cx, int cy, int r, float start_angle_deg, float end_angle_deg)
{
    float start_rad = start_angle_deg * 3.14159265f / 180.0f;
    float end_rad = end_angle_deg * 3.14159265f / 180.0f;

    for (float angle = start_rad; angle <= end_rad; angle += 0.01f)
    {
        float cos_a = cosf(angle);
        float sin_a = sinf(angle);

        for (int radius = 0; radius <= r; radius++)
        {
            int px = cx + (int)(radius * cos_a);
            int py = cy + (int)(radius * sin_a);
            ici_dolu_priv->geometri.nokta_sil(px, py);
        }
    }
}
void oled::geometri::yay_ciz(int cx, int cy, int r, float start_angle_deg, float end_angle_deg, uint8_t kalinlik)
{
    float start_rad = start_angle_deg * 3.14159265f / 180.0f;
    float end_rad = end_angle_deg * 3.14159265f / 180.0f;

    for (int radius = r; radius > (int)r - kalinlik && radius > 0; radius--)
    {
        for (float angle = start_rad; angle <= end_rad; angle += 0.01f)
        {
            int x = cx + (int)(radius * cosf(angle));
            int y = cy + (int)(radius * sinf(angle));
            nokta_ciz(x, y);
        }
    }
}
void oled::geometri::yay_sil(int cx, int cy, int r, float start_angle_deg, float end_angle_deg, uint8_t kalinlik)
{
    float start_rad = start_angle_deg * 3.14159265f / 180.0f;
    float end_rad = end_angle_deg * 3.14159265f / 180.0f;

    for (int radius = r; radius > (int)r - kalinlik && radius > 0; radius--)
    {
        for (float angle = start_rad; angle <= end_rad; angle += 0.01f)
        {
            int x = cx + (int)(radius * cosf(angle));
            int y = cy + (int)(radius * sinf(angle));
            nokta_sil(x, y);
        }
    }
}
void oled::geometri::yatay_aynala(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    if (x1 < x0)
    {
        uint8_t tmp = x0;
        x0 = x1;
        x1 = tmp;
    }
    if (y1 < y0)
    {
        uint8_t tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    for (uint8_t y = y0; y <= y1; y++)
    {
        for (uint8_t x = x0; x <= (x0 + x1) / 2; x++)
        {
            uint8_t x_mirror = x1 - (x - x0);

            bool p1 = nokta_kontrol(x, y);
            bool p2 = nokta_kontrol(x_mirror, y);

            if (p1 != p2)
            {
                if (p2)
                    nokta_ciz(x, y);
                else
                    nokta_sil(x, y);
                if (p1)
                    nokta_ciz(x_mirror, y);
                else
                    nokta_sil(x_mirror, y);
            }
        }
    }
}
void oled::geometri::dikey_aynala(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    if (x1 < x0)
    {
        uint8_t tmp = x0;
        x0 = x1;
        x1 = tmp;
    }
    if (y1 < y0)
    {
        uint8_t tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    for (uint8_t x = x0; x <= x1; x++)
    {
        for (uint8_t y = y0; y <= (y0 + y1) / 2; y++)
        {
            uint8_t y_mirror = y1 - (y - y0);

            bool p1 = nokta_kontrol(x, y);
            bool p2 = nokta_kontrol(x, y_mirror);

            if (p1 != p2)
            {
                if (p2)
                    nokta_ciz(x, y);
                else
                    nokta_sil(x, y);
                if (p1)
                    nokta_ciz(x, y_mirror);
                else
                    nokta_sil(x, y_mirror);
            }
        }
    }
}
void oled::geometri::dogrusal_egim_ciz(int x0, int y0, float m, int uzunluk, uint8_t kalinlik)
{
    float b = y0 - m * x0;

    for (int dx = 0; dx < uzunluk; dx++)
    {
        int x = x0 + dx;
        int y_center = (int)(m * x + b + 0.5f);

        for (int dy = -kalinlik / 2; dy <= kalinlik / 2; dy++)
        {
            int y = y_center + dy;

            if (x >= 0 && x < geometri_priv->__EKRAN_GENISLIK && y >= 0 && y < geometri_priv->__EKRAN_YUKSEKLIK)
                nokta_ciz(x, y);
        }
    }
}

void oled::geometri::dogrusal_egim_sil(int x0, int y0, float m, int uzunluk, uint8_t kalinlik)
{
    float b = y0 - m * x0;

    for (int dx = 0; dx < uzunluk; dx++)
    {
        int x = x0 + dx;
        int y_center = (int)(m * x + b + 0.5f);

        for (int dy = -kalinlik / 2; dy <= kalinlik / 2; dy++)
        {
            int y = y_center + dy;

            if (x >= 0 && x < geometri_priv->__EKRAN_GENISLIK && y >= 0 && y < geometri_priv->__EKRAN_YUKSEKLIK)
                nokta_sil(x, y);
        }
    }
}