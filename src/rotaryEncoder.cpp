#include "rotaryEncoder.h"

namespace RotaryEncoder {

    RotaryEncoder::RotaryEncoder() {
        resetAll();
        button = NULL;
        encoder = NULL;
    }

    RotaryEncoder::RotaryEncoder(Encoder *encoder, Bounce *button) {
        resetAll();
        button = button;
        encoder = encoder;
    }


    RotaryEncoder::RotaryEncoder(uint8_t encA, uint8_t encB, uint8_t but) {
        resetAll();
        button = new Bounce();
        button->attach(but, INPUT_PULLUP);
        button->interval(5);
        encoder = new Encoder(encA, encB);
    }

    void RotaryEncoder::resetAll() {
        position = 0;
        pressed = false;
        changed = false;
    }

    void RotaryEncoder::update() {
        button->update();
        int8_t pos = encoder->read();
        status = NIL;
        if (button->changed()) {
            pressed = button->read();
            if (pressed) { status = PRESS; }
        }
        if (oldPos - pos > ENCODER_COUNT) {
            status = UP;
            oldPos = pos;
            position++;
        } else if (pos - oldPos > ENCODER_COUNT) {
            status = DOWN;
            oldPos = pos;
            position--;
        } else {
        }
    }
}