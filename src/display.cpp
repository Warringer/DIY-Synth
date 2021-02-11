#include "display.h"
#include "constants.h"
#include <string.h>

namespace Display {

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ I2C_SCL, /* data=*/ I2C_SDA);
    //U8G2_SSD1306_128X64_NONAME_F_SW_I2C oled(U8G2_R0, /* clock=*/ I2C_SCL, /* data=*/ I2C_SDA, /* reset=*/ U8X8_PIN_NONE);

    Display::Display() {
        refresh = false;
        oled.setFont(u8g2_font_t0_12b_te);
        displayHeight = oled.getDisplayHeight();
        displayWidth = oled.getDisplayWidth();
        fontHeight = oled.getMaxCharHeight();
        fontWidth = oled.getMaxCharWidth();
        selected = 0;
        userDone = true;
    }

    void Display::drawTextBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t width, const char* text, boolean inverted) {
        u8g2_uint_t textHeight = fontHeight + 2;
        oled.setDrawColor(1);
        if (inverted) {
            oled.drawBox( x, y, width, textHeight);
            oled.setDrawColor(0);
        } else {
            oled.drawFrame( x, y, width, textHeight);
        }
        oled.drawStr(x + centerPos(text, width), y + fontHeight - 1, text);
    }

    void Display::drawTitle(const char* title) {
        titleHeight = fontHeight + 2;
        drawTextBox(0, 0, displayWidth, title, true);
    }

    void Display::makeTitle(const char* title) {
        oled.clearBuffer();
        drawTitle(title);
        oled.setDrawColor(1);
    }

    uint8_t Display::userMessage(const char*title, const char* line1, const char* line2, RotaryEncoder::encoderState state) {
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
                userDone = true;
                return selected;
                break;
            default:
                break;
        }
        if (isRefreshed() or userDone) {
            if (userDone) {
                selected = 1;
                refresh = true;
                userDone = false;
            }
            makeTitle(title);
            uint8_t fontHeight = oled.getMaxCharHeight() + 2;
            oled.drawStr(centerPos(line1, displayWidth), 2 * fontHeight - 2, line1);
            oled.drawStr(centerPos(line2, displayWidth), 3 * fontHeight - 2, line2);
            drawTextBox(1, 3 * fontHeight + 2, ((displayWidth >> 1) - 2), "Ok", (selected == 1));
            drawTextBox((displayWidth >> 1), 3 * fontHeight + 2, ((displayWidth >> 1) - 2), "Cancel", (selected == 2));
        }
        return 0;
    }

    uint8_t Display::userInputValue(const char* title, const char* pre, uint16_t *value, uint16_t low, uint16_t high,  const char* post, RotaryEncoder::encoderState state) {
        switch (state)
        {
        case RotaryEncoder::DOWN:
            if (selected != low) {
                selected--;
            };
            setRefresh();
            break;
        case RotaryEncoder::UP:
            if (selected != high) {
                selected++;
            }
            setRefresh();
            break;
        case RotaryEncoder::PRESS:
            *value = (uint8_t) selected;
            selected = 0;
            userDone = true;
            return 1;
            break;
        default:
            break;
        }
        if (isRefreshed() or userDone) {
            if (userDone) {
                selected = *value;
                refresh = true;
                userDone = false;
            }
            makeTitle(title);
            uint8_t fontHeight = oled.getMaxCharHeight() + 2;
            oled.drawStr(centerPos(pre, displayWidth), 2 * fontHeight - 2, pre);
            String val = String(selected) + " ";
            char str[val.length()];
            val.toCharArray(str, val.length());
            oled.drawStr(centerPos(str, displayWidth), 3 * fontHeight, str);
            uint8_t posPost = centerPos(str, displayWidth) + fontWidth * val.length() - (fontWidth >> 1);
            oled.drawStr(posPost, 3 * fontHeight, post);
        }
        return 0;
    }

    uint8_t Display::userInputValue(const char* title, const char* pre, uint16_t *value, uint16_t low, uint16_t high, uint8_t step, const char* post, RotaryEncoder::encoderState state) {
        switch (state)
        {
        case RotaryEncoder::DOWN:
            if (selected > step) {
                selected -= step;
                if (selected < low) {
                    selected = low;
                }
            } else {
                selected = 0;
            }
            setRefresh();
            break;
        case RotaryEncoder::UP:
            if ((selected + step) > high) {
                selected = high;
            } else {
                selected += step;
            }
            setRefresh();
            break;
        case RotaryEncoder::PRESS:
            *value = selected;
            selected = 0;
            userDone = true;
            return 1;
            break;
        default:
            break;
        }
        if (isRefreshed() or userDone) {
            if (userDone) {
                selected = *value;
                if (selected > high) {
                    selected = high;
                }
                if (selected < low) {
                    selected = low;
                }
                refresh = true;
                userDone = false;
            }
            makeTitle(title);
            uint8_t fontHeight = oled.getMaxCharHeight() + 2;
            oled.drawStr(centerPos(pre, displayWidth), 2 * fontHeight - 2, pre);
            String val = String(selected) + " ";
            char str[val.length()];
            val.toCharArray(str, val.length());
            oled.drawStr(centerPos(str, displayWidth), 3 * fontHeight, str);
            uint8_t posPost = centerPos(str, displayWidth) + fontWidth * val.length() - (fontWidth >> 1);
            oled.drawStr(posPost, 3 * fontHeight, post);
        }
        return 0;
    }

    uint8_t Display::userSelectionList(const char* title, uint16_t *selectPos, const char *list[], uint8_t listSize, RotaryEncoder::encoderState state) {
        switch (state)
        {
        case RotaryEncoder::DOWN:
            if (selected == 0) {
                selected = listSize;
            } else {
                selected--;
            }
            setRefresh();
            break;
        case RotaryEncoder::UP:
            if (selected >= listSize) {
                selected = 0;
            } else {
                selected++;
            }
            setRefresh();
            break;
        case RotaryEncoder::PRESS:
            *selectPos = selected;
            selected = 0;
            userDone = true;
            return 1;
            break;
        default:
            break;
        }
        if (isRefreshed() or userDone) {
            if (userDone) {
                selected = *selectPos;
                if (selected > listSize) {
                    selected = listSize;
                }
                refresh = true;
                userDone = false;
                selectionListSize = 4; //(displayHeight - titleHeight) / fontHeight;
            }
            makeTitle(title);
        }
        uint8_t listOffset = 0;
        if (listSize > selectionListSize) {
            if (selected > selectionListSize) {
                listOffset = selected - selectionListSize;
            }
        }
        if (selected == 0) {
            oled.setDrawColor(0);
            oled.drawStr(1, fontHeight - 1, ">");
            oled.setDrawColor(1);
        }
        for (uint8_t i = 1; i <= selectionListSize; i++) {
            int yOffset = titleHeight + fontHeight * i;
            if ((i + listOffset) == selected) {
                oled.drawStr(1, yOffset, ">");
            }
            oled.drawStr(1 + fontWidth, yOffset, list[i + listOffset - 1]);
        }
        oled.setCursor(100, 25);
        oled.print(listSize);
        oled.setCursor(100, 35);
        oled.print(selectionListSize);
        return 0;
    }

    void Display::update() {
        if (refresh) {
            oled.sendBuffer();
            resetRefresh();
        }
    }

}