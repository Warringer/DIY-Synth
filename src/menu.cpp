#include "menu.h"

namespace Menu  {

    // Menus
    const char *main_menu[] = { "LFO", "Oscillator"};
    const char main_menu_title[] = "Main Menu";
    uint16_t main_menu_selection = 0;

    const char *lfo_menu[] = { "LFO Waveform" };
    const char lfo_menu_title[] = "LFO";
    uint16_t lfo_menu_selection = 0;

    const char *osci_menu[] = { "Oscillator Waveform" };
    const char osci_menu_title[] = "Oscillator";
    uint16_t osci_menu_selection = 0;

    const char *waveform_menu[] = {"Sine", "Triangle", "Square", "Ramp"};

    const char lfo_waveform_title[] = "LFO Waveform";
    uint16_t lfo_waveform_selection = 0;
    uint8_t lfo_waveform = Waveform::SINE;
    boolean lfo_waveform_changed = false;
    uint16_t lfo_freq;

    const char osci_waveform_title[] = "Oscillator Waveform";
    uint16_t osci_waveform_selection = 0;
    uint8_t osci_waveform = Waveform::SINE;
    boolean osci_waveform_changed = false;
    uint16_t osci_freq;

    uint8_t status_tick = 0;
    boolean status_redraw = true;;

    MenuState menuState = MenuState::MAIN_MENU;

    void handleMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state) {
        switch (menuState) {
            case MenuState::MAIN_MENU:
                showMainMenu(display, state);
                break;
            case MenuState::LFO_MENU:
                showLfoMenu(display, state);
                break;
            case MenuState::OSCI_MENU:
                showOsciMenu(display, state);
                break;
            case MenuState::LFO_WAVEFORM:
                showLfoWaveformMenu(display, state);
                break;
            case MenuState::OSCI_WAVEFORM:
                showOsciWaveformMenu(display, state);
            default:
                break;
        }
    };

    void handleStatus(DisplayTFT::Display *display){
        if (status_tick < 32) {
            status_tick++;
        } else {
            status_tick = 0;
            status_redraw = true;
        }
        if (status_redraw) {
            display->drawStatus();
            showStatus(display);
            status_redraw = false;
        }
    }

    void showMainMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state) {
        int t = display->userSelectionList(main_menu_title, &main_menu_selection, main_menu, MAIN_MENU_SIZE, state);
        if (t > 0) {
            switch (main_menu_selection) {
            case 1:
                menuState = MenuState::LFO_MENU;
                break;
            case 2:
                menuState = MenuState::OSCI_MENU;
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

    void showOsciMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state) {
        int t = display->userSelectionList(osci_menu_title, &osci_menu_selection, osci_menu, LFO_MENU_SIZE, state);
        if (t > 0) {
            switch (osci_menu_selection) {
            case 0:
                menuState = MenuState::MAIN_MENU;
                break;
            case 1:
                menuState = MenuState::OSCI_WAVEFORM;
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
                    lfo_waveform = Waveform::RAMP;
                    break;
                default:
                    break;
            }
            if (lfo_menu_selection > 0){
                lfo_waveform_changed = true;
            }
            menuState = MenuState::LFO_MENU;
        }
    }

    void showOsciWaveformMenu(DisplayTFT::Display *display, RotaryEncoder::encoderState state) {
        int t = display->userSelectionList(lfo_menu_title, &osci_menu_selection, waveform_menu, WAVEFORM_MENU_SIZE, state);
        if (t > 0) {
            switch (osci_menu_selection) {
                case 1:
                    osci_waveform = Waveform::SINE;
                    break;
                case 2:
                    osci_waveform = Waveform::TRI;
                    break;
                case 3:
                    osci_waveform = Waveform::SQUARE;
                    break;
                case 4:
                    osci_waveform = Waveform::RAMP;
                    break;
                default:
                    break;
            }
            if (osci_menu_selection > 0){
                osci_waveform_changed = true;
            }
            menuState = MenuState::OSCI_MENU;
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
            case Waveform::RAMP:
                display->drawRampIcon(lfoXPos, statusYPos, color);
                break;
            default:
                break;
        }
        uint8_t osciXPos = lfoXPos + 20;
        display->drawStatusValue(osciXPos, statusYPos + 8, osci_freq, "Hz");
        display->drawStatusText(osciXPos, statusYPos, "Osci:");
        osciXPos += 31;
        switch (osci_waveform) {
            case Waveform::SINE:
                display->drawSinIcon(osciXPos, statusYPos, color);
                break;
            case Waveform::TRI:
                display->drawTriIcon(osciXPos, statusYPos, color);
                break;
            case Waveform::SQUARE:
                display->drawSquareIcon(osciXPos, statusYPos, color);
                break;
            case Waveform::RAMP:
                display->drawRampIcon(osciXPos, statusYPos, color);
                break;
            default:
                break;
        }
    }
}