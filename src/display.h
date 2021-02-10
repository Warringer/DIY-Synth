#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <U8g2lib.h>
#include <i2c_t3.h>
#include "rotaryEncoder.h"

namespace Display {

    extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    //extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;

    //! Display Wrapper class for dealing with a 128x64 SSD1306 display
    /*!
        This class wraps up the U8G2 library for an easier use
        also includes a few user methods for Message Box, changing Integer Values
    */
    class Display {
        private:
            boolean refresh;            //! should the display be refreshed?
            uint8_t titleHeight;        //! height of the title bar
            u8g2_uint_t displayWidth;   //! width of the display in pixel
            u8g2_uint_t displayHeight;  //! height of the display in pixel
            u8g2_uint_t fontWidth;      //! height of the used font in pixel
            u8g2_uint_t fontHeight;     //! width of the used font in pixel
            uint16_t selected;          //! helper variable for selection of options in user methods
            boolean userDone;           //! helper variable for selection of options in user methods
            uint8_t selectionListSize;  //! helper for selection lists

            //! helper method to center text within a given area of the display
            /*!
                this method can be used to center the position of a given text based on its length and the width of the area where the text should be displayed
                \param text     Text to be displayed
                \param width    width of the area where the text is to be displayed
                \return         x position for the text to center it
            */
            uint8_t centerPos(const char* text, u8g2_uint_t width) { return (width - (strlen(text) * u8g2.getMaxCharWidth())) >> 1; };

            //! helper methos to make a title, clear the display buffer and set the draw color to '1'
            /*!
                \param title   text of the title
            */
            void makeTitle(const char* text);

        public:
            //! Constructor
            /*!
                Constructor calls u8g2.begin(), sets the font and gets the height and width of display and font
            */
            Display();

            //! Sets refresh to true
            void setRefresh() { refresh = true; };
            //! Resets refresh to false
            void resetRefresh() { refresh = false; };
            //! is the display be refreshed on next update()
            boolean isRefreshed() { return refresh; };

            //! Draws a Text Box
            /*!
                Convenience function to dra a textbox the height is based on the used font
                \param x            x position of the TextBox
                \param y            y position of the TextBox
                \param width        width of the TextBox
                \param text         text to be displayed in the TextBox
                \param inverted     should the Textbox be inverted in colors?
            */
            void drawTextBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t width, const char* text, boolean inverted);

            //! Draws a Title Textbox
            /*!
                Convenience function to draw a Title on top of the display, wrapper for Display::TextBox
                \param text         text to be displayed in the title
            */
            void drawTitle(const char* title);

            //! displays a user message
            /*!
                Draws a user message with two lines of text and to buttons, 'Ok' and 'Cancel'
                Uses the input from a Rotary Encoder, through the RotaryEncoder::encoderState enum to switch between buttons.
                Click on the Encoder Button returns the result
                Used in a 'non blocking' design, so that other things can be done by the controller
                \param title        Title of the message
                \param line1        first line of the message
                \param line2        second line of the message
                \param state        state of the rotary encoder
                \return             return 0 is nothing happens in the function, 1 when 'Ok' is selected, 2 when 'Cancel' is selected
            */
            uint8_t userMessage(const char*title, const char* line1, const char* line2, RotaryEncoder::encoderState state);

            //! displays a dialog to change an integer value
            /*!
                Draws a user dialog to change an integer
                Uses the input from a Rotary Encoder, through the RotaryEncoder::encoderState enum to increase and decrease the value.
                Click on the Encoder returns the result
                Used in a 'non blocking' design, so that other things can be done by the controller
                \param title        Title of the Dialog
                \param pre          Description of the Value
                \param value        A pointer to the value to be chanced
                \param low          Lowest possible value
                \param high         Highest possible value
                \param post         Text to be printed after the value, e.g. a SI unit
                \param state        state of the rotary encoder
                \return             returns 1 when the button was clicked and the value accepted, 0 when the value was not accepted yet
            */
            uint8_t userInputValue(const char* title, const char* pre, uint16_t *value, uint16_t low, uint16_t high, const char* post, RotaryEncoder::encoderState state);

            //! displays a dialog to change an integer value, increase and decrease in steps
            /*!
                Draws a user dialog to change an integer by steps
                Uses the input from a Rotary Encoder, through the RotaryEncoder::encoderState enum to increase and decrease the value.
                Click on the Encoder returns the result
                Used in a 'non blocking' design, so that other things can be done by the controller
                \param title        Title of the Dialog
                \param pre          Description of the Value
                \param value        A pointer to the value to be chanced
                \param low          Lowest possible value
                \param high         Highest possible value
                \param step         value of the steps the value is to be changed, e.g. 10 steps
                \param post         Text to be printed after the value, e.g. a SI unit
                \param state        state of the rotary encoder
                \return             returns 1 when the button was clicked and the value accepted, 0 when the value was not accepted yet
            */
            uint8_t userInputValue(const char* title, const char* pre, uint16_t *value, uint16_t low, uint16_t high, uint8_t step, const char* post, RotaryEncoder::encoderState state);

            //! displays a list of scrollable and selectable items.
            /*!
                Draws a scrollsable List of items, where any item can be selected
                Uses the input from a Rotary Encoder, through the RotaryEncoder::encoderState enum to increase and decrease the value.
                Click on the Encoder returns the result
                Used in a 'non blocking' design, so that other things can be done by the controller
                \param title        Title of the Dialog
                \param selectPos    A pointer to the Value to be selected, value updated when button is pressed
                \param list         A list of strings displayed on the List
                \param listSize     Size of the list
                \param state        state of the rotary encoder
                \return             return 1 when the button is clicked and the list item accepted, 0 when no item has been selected
            */
            uint8_t userSelectionList(const char* title, uint16_t *selectPos, const char *list[], uint8_t listSize, RotaryEncoder::encoderState state);

            //! Updates the display when there is something to be refreshed
            void update();

    };
};

#endif