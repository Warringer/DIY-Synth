#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <U8g2lib.h>
#include <i2c_t3.h>
#include "rotaryEncoder.h"

namespace Display {

    extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    //extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;

    /**
     * @brief   Wrapper class for U8g2lib graphics on a SSD1306 OLED display
     *          allows to redraw the display only when needed
     *          contains various userDialog/interface functions
     *          Note:   userDialog functions are dependent on the RotaryEncoder Class
     *                  userDialog functions are non-blocking and need to be called
     *                  repeatedly to be useful
     *
     */
    class Display {
        private:
            boolean refresh;
            uint8_t titleHeight;
            u8g2_uint_t displayWidth;
            u8g2_uint_t displayHeight;
            u8g2_uint_t fontWidth;
            u8g2_uint_t fontHeight;
            uint16_t selected;
            boolean userDone;
            uint8_t selectionListSize;

            /**
             * @brief   Convenience method to return the x position for a given test, so that it can be displayed centered based on a given midpoint
             *          e.g. a given text box, or the entire display
             *
             * @param text      Text to be centered
             * @param width     Width of the Container where the text should be centered
             * @return uint8_t  x position relative to the container width
             */
            uint8_t centerPos(const char* text, u8g2_uint_t width) { return (width - (strlen(text) * u8g2.getMaxCharWidth())) >> 1; };

            /**
             * @brief Convenience method to clear the display buffer, create a userDialog Title, and change the draw display color
             *
             * @param text      Text to be written in the title
             */
            void makeTitle(const char* text);

        public:
            /**
             * @brief   Construct a new Display object
             *          Sets global U8g2 font
             *          Sets object variable for display and font size
             *
             */
            Display();

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
            void drawTextBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t width, const char* text, boolean inverted);

            /**
             * @brief   Wrapper for Textbox to create a Title in top part of the display
             *          Position is (0, 0) with the entire display width and inverted colors
             *
             * @param title     Text of the Title
             */
            void drawTitle(const char* title);

            /**
             * @brief   UserDialog method creating a Message Box with a title and two lines
             *          Two buttons, 'Ok' and 'Cancel' are avaiable
             *          Selection of the Buttons is per RotaryEncoder and is non-blocking
             *          Selection is done by pressing the RotaryEncoder Button
             *
             * @param title     Title of the UserDialog
             * @param line1     Line 1 of the Message Box
             * @param line2     Line 2 of the Message Box
             * @param state     Status of the Rotary Encoder
             * @return uint8_t  returns 0, when no selection has been made
             *                  returns 1, when 'Ok' has been selected
             *                  returns 2, when 'Cancel' has been selected
             */
            uint8_t userMessage(const char*title, const char* line1, const char* line2, RotaryEncoder::encoderState state);

            /**
             * @brief   UserDialog to Input a uint16_t value
             *          The Value is changed per RotaryEncoder and is non-blocking
             *          The Value can be accepted by pressing the RotaryEncoder Button
             *
             * @param title     Title of the UserDialog
             * @param pre       Explanation of the Value
             * @param value     pointer to the value to be changed
             *                  returns the accepted value
             * @param low       lower bounds of the value
             * @param high      upper bounds of the value
             * @param post      Possible unit of the Value, e.g. 'V' or 'Hz'
             * @param state     Status of the RotaryEncoder
             * @return uint8_t  return 0, when the value is not accepted
             *                  return 1, when the value is accepted and returned over the pointer to value
             */
            uint8_t userInputValue(const char* title, const char* pre, uint16_t *value, uint16_t low, uint16_t high, const char* post, RotaryEncoder::encoderState state);

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
             * @param post      Possible unit of the Value, e.g. 'V' or 'Hz'
             * @param state     Status of the RotaryEncoder
             * @return uint8_t  return 0, when the value is not accepted
             *                  return 1, when the value is accepted and returned over the pointer to value
             */
            uint8_t userInputValue(const char* title, const char* pre, uint16_t *value, uint16_t low, uint16_t high, uint8_t step, const char* post, RotaryEncoder::encoderState state);

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
             * @param listSize  Size of the List of Items
             * @param state     Status of the RotaryEncoder
             * @return uint8_t  returns 0, is no selection has been made
             *                  returns 1, if a selection has been made and returned over the pointer to selectPos
             */
            uint8_t userSelectionList(const char* title, uint16_t *selectPos, const char *list[], uint8_t listSize, RotaryEncoder::encoderState state);

            /**
             * @brief   Method to update the display if the Refresh Variable is set
             *
             */
            void update();

    };
};

#endif