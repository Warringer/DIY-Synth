#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <U8g2lib.h>
#include <i2c_t3.h>
#include "rotaryEncoder.h"

namespace Display {

    extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    //extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;

    class Display {
        private:
            boolean refresh;
            uint8_t titleHeight;
            u8g2_uint_t displayWidth;
            u8g2_uint_t displayHeight;
            u8g2_uint_t fontWidth;
            u8g2_uint_t fontHeight;
            uint8_t selected;

            RotaryEncoder::RotaryEncoder *encoder;

            uint8_t centerPos(const char* text, u8g2_uint_t width) { return (width - (strlen(text) * u8g2.getMaxCharWidth())) >> 1; };

        public:
            Display();

            void setRefresh() { refresh = true; };
            void resetRefresh() { refresh = false; };
            boolean isRefreshed() { return refresh; };

            void setEncoder(RotaryEncoder::RotaryEncoder *enc) { encoder = enc; };

            void drawTextBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t width, const char* text, boolean inverted);

            void drawTitle(const char* title);

            int drawMessage(const char*title, const char* line1, const char* line2, RotaryEncoder::encoderState state);

            void update();

    };
};

#endif