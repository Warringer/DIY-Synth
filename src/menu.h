#ifndef __MENU_H
#define __MENU_H

#include "display_tft.h"
#include "constants.h"
#include "rotaryEncoder.h"

extern const char *main_menu[];
extern const char main_menu_title[];
#define MAIN_MENU_SIZE 2
extern uint16_t main_menu_selection;

extern const char *lfo_menu[];
extern const char lfo_menu_title[];
#define LFO_MENU_SIZE 1
extern uint16_t lfo_menu_selection;

extern const char *oszi_menu[];
extern const char oszi_menu_title[];
#define OSZI_MENU_SIZE 1
extern uint16_t oszi_menu_selection;

extern const char *waveform_menu[];
#define WAVEFORM_MENU_SIZE 6

extern const char lfo_waveform_title[];
extern uint16_t lfo_waveform_selection;
extern uint8_t lfo_waveform;

extern const char oszi_waveform_title[];
extern uint16_t oszi_waveform_selection;
extern uint8_t oszi_waveform;

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
    OSZI_MENU,
    LFO_WAVEFORM,
    OSZI_WAVEFORM
};

void handleMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);
void handleStatus(DisplayTFT::Display *display);

void showMainMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);
void showLfoMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);
void showOsziMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);

void showLfoWaveformMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);
void showOsziWaveformMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state);

void showStatus(DisplayTFT::Display *display);

#endif