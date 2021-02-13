#ifndef __MENU_H
#define __MENU_H

#include "display_tft.h"
#include "constants.h"
#include "rotaryEncoder.h"

namespace Menu {

    extern const char *main_menu[];
    extern const char main_menu_title[];
    #define MAIN_MENU_SIZE 2
    extern uint16_t main_menu_selection;

    extern const char *lfo_menu[];
    extern const char lfo_menu_title[];
    #define LFO_MENU_SIZE 1
    extern uint16_t lfo_menu_selection;

    extern const char *osci_menu[];
    extern const char osci_menu_title[];
    #define OScI_MENU_SIZE 1
    extern uint16_t osci_menu_selection;

    extern const char *waveform_menu[];
    #define WAVEFORM_MENU_SIZE 4

    extern const char lfo_waveform_title[];
    extern uint16_t lfo_waveform_selection;
    extern uint8_t lfo_waveform;
    extern boolean lfo_waveform_changed;

    extern const char osci_waveform_title[];
    extern uint16_t osci_waveform_selection;
    extern uint8_t osci_waveform;
    extern boolean osci_waveform_changed;

    enum Waveform {
        SINE,
        TRI,
        SQUARE,
        PULSE,
        RAMP,
        INV_RAMP
    };

    enum MenuState {
        MAIN_MENU,
        LFO_MENU,
        OSCI_MENU,
        LFO_WAVEFORM,
        OSCI_WAVEFORM
    };

    void handleMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);
    void handleStatus(DisplayTFT::Display *display);

    void showMainMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);
    void showLfoMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);
    void showOsciMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);

    void showLfoWaveformMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);
    void showOsciWaveformMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);

    void showStatus(DisplayTFT::Display *display);

}

#endif