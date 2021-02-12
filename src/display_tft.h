#ifndef __DISPLAY_TFT_H
#define __DISPLAY_TFT_H

#include <ST7735_t3.h>
#include <SPI.h>
#include "constants.h"
#include "rotaryEncoder.h"

namespace DisplayTFT {

    extern ST7735_t3 tft;

    class Display {
        private:
            boolean refresh;
            uint16_t displayWidth;
            uint16_t displayHeight;
            uint8_t titleHeight;
            uint16_t selected;
            boolean userDone;
            uint8_t selectionListSize;
            uint8_t lowerPartBegin;
            boolean refreshStatus;
            boolean newStatus;

        public:
            /**
             * @brief   Construct a new Display object
             *          Sets global U8g2 font
             *          Sets object variable for display and font size
             *
             */
            Display() {
                refresh = false;
                displayHeight = tft.width();
                displayWidth  = tft.height();
                selected = 0;
                userDone = true;
                selectionListSize = 10;
                tft.initR(INITR_BLACKTAB);
                tft.setRotation(tft.getRotation()+1);
                tft.fillScreen(ST7735_BLACK);
                lowerPartBegin = 105;
                refreshStatus = false;
                newStatus = true;
            };

            /**
             * @brief   Set the Refresh variable
             *
             */
            void setRefresh() { refresh = true; };
            /**
             * @brief   Resets the Refresh variable
             *
             */
            void resetRefresh() { refresh = false; };
            /**
             * @brief   returns the status of the refresh variable
             *
             * @return boolean  true, if the display gets refreshed
             *                  false, when display refresh does not happen
             */
            boolean isRefreshed() { return refresh; };

            /**
             * @brief   Set the Refresh variable
             *
             */
            void setRefreshStatus() { refreshStatus = true; };
            /**
             * @brief   Resets the Refresh variable
             *
             */
            void resetRefreshStatus() { refreshStatus = false; };
            /**
             * @brief   returns the status of the refresh variable
             *
             * @return boolean  true, if the display gets refreshed
             *                  false, when display refresh does not happen
             */
            boolean isRefreshedStatus() { return refreshStatus; };

            /**
             * @brief   
             * 
             */
            void setNewStatus() { newStatus = true; };

            /**
             * @brief   User Interface method to create a TextBox in any part of the display
             *          Height of the TextBox is dependent on the font size
             *          Text is centered in the TextBox
             *
             * @param x         upper left x position of the TextBox
             * @param y         upper left y position of the TextBox
             * @param width     width of the TextBox
             * @param text      Text to be displayed in the Textbox
             * @param inverted  if true, Textbox will be light with black text
             *                  if false, TextBox will be dark with light text
             */
            void drawTextBox(uint16_t x, uint16_t y, uint16_t width, const char* text, boolean inverted);

            /**
             * @brief   Wrapper for Textbox to create a Title in top part of the display
             *          Position is (0, 0) with the entire display width and inverted colors
             *
             * @param title     Text of the Title
             */
            void drawTitle(const char* title);

            /**
             * @brief   UserDialog method creating a Message Box with a title and two lines
             *          Two buttons, 'Ok' and 'Cancel' are available
             *          Selection of the Buttons is per RotaryEncoder and is non-blocking
             *          Selection is done by pressing the RotaryEncoder Button
             *
             * @param title     Title of the UserDialog
             * @param text      Text of the Message Box May use multiple lines terminated with '\n'
             * @param state     Status of the Rotary Encoder
             * @return uint8_t  returns 0, when no selection has been made
             *                  returns 1, when 'Ok' has been selected
             *                  returns 2, when 'Cancel' has been selected
             */
            uint8_t userMessage(const char*title, const char* text, RotaryEncoder::encoderState state);

            /**
             * @brief   UserDialog to Input a uint16_t value, increasing by a given step size
             *          The Value is changed per RotaryEncoder and is non-blocking
             *          The Value can be accepted by pressing the RotaryEncoder Button
             *
             * @param title     Title of the UserDialog
             * @param pre       Explanation of the Value
             * @param value     pointer to the value to be changed
             *                  returns the accepted value
             * @param low       lower bounds of the value
             * @param high      upper bounds of the value
             * @param step      step used to increase/decrease the value
             * @param unit      Possible unit of the Value, e.g. 'V' or 'Hz'
             * @param state     Status of the RotaryEncoder
             * @return uint8_t  return 0, when the value is not accepted
             *                  return 1, when the value is accepted and returned over the pointer to value
             */
            uint8_t userInputValue(const char* title, const char* pre, int *value, uint16_t low, uint16_t high, uint8_t step, const char* unit, RotaryEncoder::encoderState state);

            /**
             * @brief   UserDialog to display a List, where any element can be selected, including the Title
             *          The item on the list can be selected per RotaryEncoder and is non-blocking
             *          The item can be selected by pressing the RotaryEncoder Button
             *          Note:   selectPos return 0, when the Title has been chosen, for e.g. escaping the UserDialog
             *
             * @param title     Title of the UserDialog
             * @param selectPos pointer to the initial selected item on the dialog
             *                  returns the finally selected value
             *                  returns 0, when title was selected, for e.g. escaping the dialog
             * @param list      List of Items for the Selection
             *                  Maximum size of List is 10
             * @param listSize  Size of the List of Items, max 10
             * @param state     Status of the RotaryEncoder
             * @return uint8_t  returns 0, is no selection has been made
             *                  returns 1, if a selection has been made and returned over the pointer to selectPos
             */
            uint8_t userSelectionList(const char* title, uint16_t *selectPos, const char *list[], uint8_t listSize, RotaryEncoder::encoderState state);

            /**
             * @brief   Creates a Status Display in the Lower part of the Display
             *          Can be called repeatedly to display changed valued.
             *          If different Values, e.g. temperatures instead of voltages
             *          the method 'Display::setNewStatus()' needs to be executes to change the value Text
             * 
             * @param title         Title of the Status Display
             * @param value1        First Value to be displayed
             * @param value1Text    Text for the first Value
             * @param value2        Second Value to be displayed
             * @param value2Text    Text for the second Value
             * @param value3        Third Value of the Status
             * @param value3Text    Text for the third Value
             * @param value4        Fourth Value to be displayed
             * @param value4Text    Text for the fourth Value
             */
            void drawStatus();

             /**
             * @brief   Method to update the display if the Refresh Variable is set
             *          Method just present for compatibility reasons with OLED version of this class
             *
             */
            void update() {};

            /**
             * @brief   Method to start the  Display
             *          Method just present for compatibility reasons with OLED version of this class
             *
             */
            void begin() { tft.fillScreen(ST7735_BLACK); };
    };

}

#endif