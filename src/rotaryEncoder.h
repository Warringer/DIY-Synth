#ifndef __ROTARYENCODER_H
#define __ROTARYENCODER_H

#include <Encoder.h>
#include <Bounce2.h>

// Encoder
#define ENCODER_COUNT 3

namespace RotaryEncoder {

    enum encoderState { NIL, UP, DOWN, PRESS };

    class RotaryEncoder {
        private:
            int8_t position;
            int16_t oldPos;
            boolean changed;
            boolean pressed;
            encoderState move;

            Encoder *encoder;
            Bounce *button;

        public:
            RotaryEncoder();
            RotaryEncoder(Encoder *encoder, Bounce *button);
            RotaryEncoder(uint8_t encA, uint8_t encB, uint8_t but);

            void setPosition(uint8_t pos) { position = pos; };
            uint8_t getPosition() { return position; };

            void setEncoder(Encoder *enc) { encoder = enc; };
            void setButton(Bounce *but) { button = but; };

            boolean isChanged() { return changed; };
            void setChanged() { changed = true;};
            void resetChanged() { changed = false; };

            boolean isPressed() { return pressed; };
            void setPressed() { pressed = true; };
            void resetPressed() { pressed = false; };

            encoderState getMovement() { return move; };
            void resetMovement() { move = NIL; };

            void resetAll();

            void update();
    };
};

#endif