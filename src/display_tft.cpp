#include "display_tft.h"

namespace DisplayTFT {

    ST7735_t3 tft = ST7735_t3(SPI_CS1, SPI_DC, SPI_DOUT, SPI_SCK, SPI_RST);

    void Display::drawTextBox(uint16_t x, uint16_t y, uint16_t width, const char* text, boolean inverted) {
        uint16_t boxColor = tft.Color565(0, 76, 186); // 50% Gra
        uint8_t textHeight = tft.getTextSizeX() * 8;
        if (inverted) {
            tft.fillRect(x, y, width, textHeight + 4, boxColor);
        } else {
            tft.drawRect(x, y, width, textHeight + 4, boxColor);
        }
        tft.setCursor(x + (width >> 1), y + (textHeight >> 1) + 2, true);
        tft.print(text);
    }

    void Display::drawTitle(const char* title) {
        titleHeight = tft.getTextSizeX() * 8 + 2;
        drawTextBox(0, 0, displayWidth, title, true);
    }

    uint8_t Display::userMessage(const char*title, const char* text, RotaryEncoder::encoderState state) {
        setRefresh();
        if (userDone) {
            drawTitle(title);
            tft.setCursor(0, titleHeight + 4);
            tft.setTextWrap(true);
            tft.print(text);
            selected = 1;
            userDone = false;
        } else {
            switch (state) {
                case RotaryEncoder::DOWN:
                case RotaryEncoder::UP:
                    if (selected == 1) {
                        selected = 2;
                    } else {
                        selected = 1;
                    }
                    break;
                case RotaryEncoder::PRESS:
                    userDone = true;
                    return selected;
                    break;
                case RotaryEncoder::NIL:
                    if (!userDone) {
                        resetRefresh();
                    }
                default:
                    break;
            }
        }
        if (isRefreshed()){
            tft.fillRect(0, displayHeight - (titleHeight + 4), displayWidth, titleHeight + 4, ST7735_BLACK);
            drawTextBox(1, displayHeight - (titleHeight + 4), (displayWidth >> 1) - 2, "Ok", (selected == 1));
            drawTextBox(1 + (displayWidth >> 1), displayHeight - (titleHeight + 4), (displayWidth >> 1) - 2, "Cancel", (selected == 2));
        }
        return 0;
    }

    uint8_t Display::userInputValue(const char* title, const char* pre, int *value, uint16_t low, uint16_t high, uint8_t step, const char* unit, RotaryEncoder::encoderState state) {
        setRefresh();
        if (userDone) {
            drawTitle(title);
            tft.setCursor(displayWidth >> 1, 2 * titleHeight + 4, true);
            tft.print(pre);
            selected = *value;
            if (selected > high) {
                selected = high;
            }
            if (selected < low) {
                selected = low;
            }
            userDone = false;
        } else {
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
                break;
            case RotaryEncoder::UP:
                if ((selected + step) > high) {
                    selected = high;
                } else {
                    selected += step;
                }
                break;
            case RotaryEncoder::PRESS:
                *value = selected;
                selected = 0;
                userDone = true;
                return 1;
                break;
            case RotaryEncoder::NIL:
                if (!userDone) {
                    resetRefresh();
                }
            default:
                break;
            }
        }
        if (isRefreshed()) {
            tft.fillRect(0, 3 * titleHeight, displayWidth, titleHeight << 1, ST7735_BLACK);
            tft.setCursor(displayWidth >> 1, 3 * titleHeight +4, true);
            tft.print(selected);
            tft.print(" ");
            tft.print(unit);
        }
        return 0;
    };

    uint8_t Display::userSelectionList(const char* title, uint16_t *selectPos, const char *list[], uint8_t listSize, RotaryEncoder::encoderState state) {
        setRefresh();
        uint8_t listOffset = 0;
        uint8_t displayedListSize = listSize;
        if (listSize > selectionListSize) {
            if (selected > selectionListSize) {
                listOffset = selected - selectionListSize;
            }
            displayedListSize = selectionListSize;
        }
        int line = 0;
        if (userDone) {
            drawTitle(title);
            for (uint8_t i = 1; i <= displayedListSize; i++) {
                line = titleHeight + tft.getTextSizeY() * 9 * i;
                tft.setCursor(displayWidth >> 1, line, true);
                tft.print(list[i + listOffset - 1]);
            }
            selected = *selectPos;
            if (selected > listSize) {
                selected = listSize;
            }
            userDone = false;
        } else {
            switch (state)
            {
            case RotaryEncoder::DOWN:
                if (selected == 0) {
                    selected = listSize;
                } else {
                    selected--;
                }
                break;
            case RotaryEncoder::UP:
                if (selected >= listSize) {
                    selected = 0;
                } else {
                    selected++;
                }
                break;
            case RotaryEncoder::PRESS:
                *selectPos = selected;
                selected = 0;
                userDone = true;
                return 1;
                break;
            case RotaryEncoder::NIL:
                if (!userDone) {
                    resetRefresh();
                }
            default:
                break;
            }
        }
        if (isRefreshed()) {
            tft.fillRect(0, 0, 10, titleHeight, tft.Color565(0, 76, 186));
            tft.fillRect(0, titleHeight + 2, 10, displayHeight - (titleHeight +1) - (displayHeight - lowerPartBegin), ST7735_BLACK);
            if (selected == 0) {
                tft.setCursor(1, 2);
                tft.print(">");
            }
            for (uint8_t i = 1; i <= displayedListSize; i++) {
                line = titleHeight + tft.getTextSizeY() * 9 * i;
                if ((i + listOffset) == selected) {
                    tft.setCursor(4, line, true);
                    tft.print(">");
                }
            }
        }
        return 0;
    }

    void Display::drawStatus(const char* title, int *value1, char* value1Text, int *value2, char* value2Text, int *value3, char* value3Text, int *value4, char* value4Text) {
        if (newStatus) {
            drawTextBox(0, lowerPartBegin + 1, displayWidth, title, true);
            newStatus = false;
            tft.setCursor(20, lowerPartBegin + titleHeight + 10, true);
            tft.print(value1Text);
            if (value2Text) {
                tft.setCursor((displayWidth >> 1) + 20, lowerPartBegin + titleHeight + 10, true);
                tft.print(value2Text);
            }
            if (value3Text) {
                tft.setCursor(20, lowerPartBegin + titleHeight + 25, true);
                tft.print(value3Text);
            }
            if (value4Text) {
                tft.setCursor((displayWidth >> 1) + 20, lowerPartBegin + titleHeight + 25, true);
                tft.print(value4Text);
            }
            setRefreshStatus();
        }
        if (isRefreshedStatus()) {
            tft.fillRect(32, lowerPartBegin + titleHeight + 3, 30, 64, ST7735_BLACK);
            tft.fillRect((displayWidth >> 1) + 32, lowerPartBegin + titleHeight + 3, 30, 64, ST7735_BLACK);
            tft.setCursor(50, lowerPartBegin + titleHeight + 10, true);
            tft.print(*value1);
            if (value2Text) {
                tft.setCursor((displayWidth >> 1) + 50, lowerPartBegin + titleHeight + 10, true);
                tft.print(*value2);
            }
            if (value3Text) {
                tft.setCursor(50, lowerPartBegin + titleHeight + 25, true);
                tft.print(*value3);
            }
            if (value4Text) {
                tft.setCursor((displayWidth >> 1) + 50, lowerPartBegin + titleHeight + 25, true);
                tft.print(*value4);
            }
            resetRefreshStatus();
        }
    }

}