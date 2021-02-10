#include "display.h"
#include "constants.h"

namespace Display {

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ I2C_SCL, /* data=*/ I2C_SDA);
    //U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ I2C_SCL, /* data=*/ I2C_SDA, /* reset=*/ U8X8_PIN_NONE);

    Display::Display() {
        refresh = false;
        u8g2.setFont(u8g2_font_7x13B_mf);
        displayHeight = u8g2.getDisplayHeight();
        displayWidth = u8g2.getDisplayWidth();
        fontHeight = u8g2.getMaxCharHeight();
        fontWidth = u8g2.getMaxCharWidth();
    }

    void Display::drawTextBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t width, const char* text, boolean inverted) {
        u8g2_uint_t textHeight = fontHeight + 2;
        u8g2.setDrawColor(1);
        if (inverted) {
            u8g2.drawBox( x, y, width, textHeight);
            u8g2.setDrawColor(0);
        } else {
            u8g2.drawFrame( x, y, width, textHeight);
        }
        u8g2.drawStr(x + centerPos(text, width), y + fontHeight - 1, text);
    }

    void Display::drawTitle(const char* title) {
        drawTextBox(0, 0, displayWidth, title, true);
    }

    int Display::userMessage(const char*title, const char* line1, const char* line2, RotaryEncoder::encoderState state) {
        switch (state) {
            case RotaryEncoder::DOWN:
            case RotaryEncoder::UP:
                if (selected == 1) {
                    selected = 2;
                } else {
                    selected = 1;
                }
                setRefresh();
                break;
            case RotaryEncoder::PRESS:
                return selected;
                break;
            default:
                break;
        }
        if (isRefreshed() or (selected == 0)) {
            if (selected == 0) { selected = 1; refresh = true;}
            u8g2.clearBuffer();
            drawTitle(title);
            u8g2.setFont(u8g2_font_7x13B_mf);
            u8g2.setDrawColor(1);
            uint8_t fontHeight = u8g2.getMaxCharHeight() + 2;
            u8g2.drawStr(centerPos(line1, displayWidth), 2 * fontHeight - 2, line1);
            u8g2.drawStr(centerPos(line2, displayWidth), 3 * fontHeight - 2, line2);
            drawTextBox(1, 3 * fontHeight + 2, ((displayWidth >> 1) - 2), "Ok", (selected == 1));
            drawTextBox((displayWidth >> 1), 3 * fontHeight + 2, ((displayWidth >> 1) - 2), "Cancel", (selected == 2));
        }
        return 0;
    }

    void Display::update() {
        if (refresh) {
            u8g2.sendBuffer();
        }
    }

}