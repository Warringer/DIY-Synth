#include "menu.h"

// Menus
const char *main_menu[] = { "LFO", "Oscillator"};
const char main_menu_title[] = "Main Menu";
uint16_t main_menu_selection = 0;

const char *lfo_menu[] = { "LFO Waveform" };
const char lfo_menu_title[] = "LFO";
uint16_t lfo_menu_selection = 0;

const char *oszi_menu[] = { "Oszillator Waveform" };
const char oszi_menu_title[] = "Oszillator";
uint16_t oszi_menu_selection = 0;

const char *waveform_menu[] = {"Sine", "Triangle", "Square", "Pulse", "Ramp", "Inv Ramp"};

const char lfo_waveform_title[] = "LFO Waveform";
uint16_t lfo_waveform_selection = 0;
uint8_t lfo_waveform = Waveform::SINE;

const char oszi_waveform_title[] = "Oscillator Waveform";
uint16_t oszi_waveform_selection = 0;
uint8_t oszi_waveform = Waveform::SINE;


MenuState menuState = MenuState::MAIN_MENU;

void handleMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state) {
    switch (menuState) {
        case MenuState::MAIN_MENU:
            showMainMenu(display, state);
            break;
        case MenuState::LFO_MENU:
            showLfoMenu(display, state);
            break;
        case MenuState::OSZI_MENU:
            showOsziMenu(display, state);
            break;
        case MenuState::LFO_WAVEFORM:
            showLfoWaveformMenu(display, state);
            break;
        case MenuState::OSZI_WAVEFORM:
            showOsziWaveformMenu(display, state);
        default:
            break;
    }
};

void handleStatus(DisplayTFT::Display *display){
    display->drawStatus();
    showStatus(display);
}

void showMainMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state) {
    int t = display->userSelectionList(main_menu_title, &main_menu_selection, main_menu, MAIN_MENU_SIZE, state);
    if (t > 0) {
        switch (main_menu_selection) {
        case 1:
            menuState = MenuState::LFO_MENU;
            break;
        case 2:
            menuState = MenuState::OSZI_MENU;
            break;
        default:
            break;
        }
    }
}

void showLfoMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state) {
    int t = display->userSelectionList(lfo_menu_title, &lfo_menu_selection, lfo_menu, LFO_MENU_SIZE, state);
    if (t > 0) {
        switch (lfo_menu_selection) {
        case 0:
            menuState = MenuState::MAIN_MENU;
            break;
        case 1:
            menuState = MenuState::LFO_WAVEFORM;
            break;
        default:
            break;
        }
    }
}

void showOsziMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state) {
    int t = display->userSelectionList(oszi_menu_title, &oszi_menu_selection, oszi_menu, LFO_MENU_SIZE, state);
    if (t > 0) {
        switch (oszi_menu_selection) {
        case 0:
            menuState = MenuState::MAIN_MENU;
            break;
        case 1:
            menuState = MenuState::OSZI_WAVEFORM;
            break;
        default:
            break;
        }
    }
}

void showLfoWaveformMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state) {
    int t = display->userSelectionList(lfo_menu_title, &lfo_menu_selection, waveform_menu, WAVEFORM_MENU_SIZE, state);
    if (t > 0) {
        switch (lfo_menu_selection) {
            case 1:
                lfo_waveform = Waveform::SINE;
                break;
            case 2:
                lfo_waveform = Waveform::TRI;
                break;
            case 3:
                lfo_waveform = Waveform::SQUARE;
                break;
            case 4:
                lfo_waveform = Waveform::PULSE;
                break;
            case 5:
                lfo_waveform = Waveform::RAMP;
                break;
            case 6:
                lfo_waveform = Waveform::INV_RAMP;
                break;
            default:
                break;
        }
        menuState = MenuState::LFO_MENU;
    }
}

void showOsziWaveformMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state) {
    int t = display->userSelectionList(lfo_menu_title, &oszi_menu_selection, waveform_menu, WAVEFORM_MENU_SIZE, state);
    if (t > 0) {
        switch (oszi_menu_selection) {
            case 1:
                oszi_waveform = Waveform::SINE;
                break;
            case 2:
                oszi_waveform = Waveform::TRI;
                break;
            case 3:
                oszi_waveform = Waveform::SQUARE;
                break;
            case 4:
                oszi_waveform = Waveform::PULSE;
                break;
            case 5:
                oszi_waveform = Waveform::RAMP;
                break;
            case 6:
                oszi_waveform = Waveform::INV_RAMP;
                break;
            default:
                break;
        }
        menuState = MenuState::OSZI_MENU;
    }
}

void showStatus(DisplayTFT::Display *display) {
    uint8_t statusYPos = display->getStatusYPos() + 2;
    uint8_t lfoXPos = 5;
    uint16_t color = display->getStatusColor();
    display->drawStatusText(lfoXPos, statusYPos, "LFO:");
    lfoXPos += 25;
    switch (lfo_waveform) {
        case Waveform::SINE:
            display->drawSinIcon(lfoXPos, statusYPos, color);
            break;
        case Waveform::TRI:
            display->drawTriIcon(lfoXPos, statusYPos, color);
            break;
        case Waveform::SQUARE:
            display->drawSquareIcon(lfoXPos, statusYPos, color);
            break;
        case Waveform::PULSE:
            display->drawPulseIcon(lfoXPos, statusYPos, color);
            break;
        case Waveform::RAMP:
            display->drawRampIcon(lfoXPos, statusYPos, color);
            break;
        case Waveform::INV_RAMP:
            display->drawReverseRampIcon(lfoXPos, statusYPos, color);
            break;
        default:
            break;
    }
    uint8_t osziXPos = lfoXPos + 20;
    display->drawStatusText(osziXPos, statusYPos, "Oszi:");
    osziXPos += 31;
    switch (oszi_waveform) {
        case Waveform::SINE:
            display->drawSinIcon(osziXPos, statusYPos, color);
            break;
        case Waveform::TRI:
            display->drawTriIcon(osziXPos, statusYPos, color);
            break;
        case Waveform::SQUARE:
            display->drawSquareIcon(osziXPos, statusYPos, color);
            break;
        case Waveform::PULSE:
            display->drawPulseIcon(osziXPos, statusYPos, color);
            break;
        case Waveform::RAMP:
            display->drawRampIcon(osziXPos, statusYPos, color);
            break;
        case Waveform::INV_RAMP:
            display->drawReverseRampIcon(osziXPos, statusYPos, color);
            break;
        default:
            break;
    }

}