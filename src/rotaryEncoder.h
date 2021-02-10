#ifndef __ROTARYENCODER_H
#define __ROTARYENCODER_H

#include <Encoder.h>
#include <Bounce2.h>

// Encoder
#define ENCODER_COUNT 3

namespace RotaryEncoder {

    //! endocerState
    /*! Enabled the user of Encoder States for the last action of the Encoder */
    enum encoderState {
        NIL,        /*!< No last action */
        UP,         /*!< Encoder incremented up */
        DOWN,       /*!< Encoder incemented down */
        PRESS };    /*!< Encoder Butten was pressed */

    class RotaryEncoder {
        private:
            int8_t position;        //! Position of the Encoder
            int16_t oldPos;         //! old Position of the Encoder
            boolean changed;        //! did anything change in the Encoder?
            boolean pressed;        //! has the Encoder Button be pressed?
            encoderState status;    //! Status of the Encoder since last use

            Encoder *encoder;       //! Encoder Object to use
            Bounce *button;         //! Bounce Object to debounce the Encoder Button

        public:
            //! Empty Constructor
            /*!
                Just the basic Constructor
             */
            RotaryEncoder();

            //! Constructor with prepared Encoder object and Bounce debouncer object for button
            /*!
              \param encoder Teensy Encoder object
              \param button  Teensy Bounce object
             */
            RotaryEncoder(Encoder *encoder, Bounce *button);

            //! Constructor that autogenerates Encoder and Bounce Objects
            /*!
              \param encA   Encoder Pin A
              \param encB   Encoder Pin B
              \param but    Encoder Button Pin
            */
            RotaryEncoder(uint8_t encA, uint8_t encB, uint8_t but);

            //! Setter for Encoder Position
            /*!
              \param pos    Encoder Position
            */
            void setPosition(uint8_t pos) { position = pos; };

            //! Getter for Encoder Position
            /*!
              \return       Encoder Position
            */
            uint8_t getPosition() { return position; };

            //! Setter for Encoder object
            /*!
              \param enc    Teensy Encoder object
            */
            void setEncoder(Encoder *enc) { encoder = enc; };
            //! Setter for Bounce object
            /*!
              \param but    Teensy Bounce Object
            */
            void setButton(Bounce *but) { button = but; };

            //! Getter for Status of the Encoder
            /*!
                has the encoder changed since last time?
              \return       boolean status of the encoder
            */
            boolean isChanged() { return changed; };
            //! Sets Changed Status to true
            void setChanged() { changed = true;};
            //! resets changed Status to false
            void resetChanged() { changed = false; };

            //! Getter for Status of the Button
            /*! has the Encoder Button be pressed?
              \return       boolean status of the button
            */
            boolean isPressed() { return pressed; };
            //! Sets the button to true
            void setPressed() { pressed = true; };
            //! Resets the button to false
            void resetPressed() { pressed = false; };

            //! Getter for status of the Encoder as a whole
            /*!
              \return       returns the Status of the Encoder as encoderStatus enum
            */
            encoderState getStatus() { return status; };
            //! Resets the status of the Encoder
            void resetStatus() { status = NIL; };

            //! Resets the entire Encoder object
            /*!
                Mainly used in the Constructors
            */
            void resetAll();

            //! Runs an update of the Encoder to see if anything has changed
            void update();
    };
};

#endif