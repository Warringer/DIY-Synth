#ifndef __ROTARYENCODER_H
#define __ROTARYENCODER_H

#include <Encoder.h>
#include <Bounce2.h>

// Encoder
#define ENCODER_COUNT 3

namespace RotaryEncoder {

    /**
     * @brief enum for States used by RotaryEncoder Class
     *
     */
    enum encoderState {
        NIL,        /*!< No last action */
        UP,         /*!< Encoder incremented up */
        DOWN,       /*!< Encoder incremented down */
        PRESS };    /*!< Encoder Butten was pressed */

    /**
     * @brief Wrapper Class for Teensy Encoder and Bounce objects to operate a Rotary Encoder with Push Button
     *
     */
    class RotaryEncoder {
        private:
            int8_t position;
            int16_t oldPos;
            boolean changed;
            boolean pressed;
            encoderState status;

            Encoder *encoder;
            Bounce *button;

        public:
            /**
             * @brief Construct a new Rotary Encoder object
             *
             */
            RotaryEncoder();

            /**
             * @brief Construct a new Rotary Encoder object by taking existing objects
             *
             * @param encoder   Teensy Encoder object for Rotary Encoder
             * @param button    Teensy Bounce object to debounce Encoder Button
             */
            RotaryEncoder(Encoder *encoder, Bounce *button);
            /**
             * @brief Construct a new Rotary Encoder object, creating new objects for Endocere and Bounce
             *        by taking the Pins for either Object
             *
             * @param encA      Pin A for Encoder direction
             * @param encB      Pin B for Encoder direction
             * @param but       Pin for Bounce to debounce Encoder Button
             */
            RotaryEncoder(uint8_t encA, uint8_t encB, uint8_t but);

            /**
             * @brief Get the Status of the object
             *
             * @return encoderState   Returns enum for the last Status
             */
            encoderState getStatus() { return status; };
            /**
             * @brief Resets the Status message from the Object
             *
             */
            void resetStatus() { status = NIL; };

            /**
             * @brief Resets all private variables of the object
             *
             */
            void resetAll();

            /**
             * @brief Runs an update of the object, dealing with any changes of the Encoder
             *        and the Bound objects, saving it to the Object state.
             *
             */
            void update();
    };
};

#endif