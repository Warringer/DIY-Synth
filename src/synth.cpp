#include "synth.h"

namespace Synth {

    // use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
    Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

    // Smooth analog Inputs
    RollingAverage <int, 16> kAverageFreq;

    IntMap kMapFreq(0, 1024, OSCI_MIN, OSCI_MAX);

    int kFreq = 880;

    void handleOsciWaveform() {
        if (Menu::osci_waveform_changed) {
            Menu::osci_waveform_changed = false;
            switch (Menu::osci_waveform) {
            case Menu::Waveform::SINE:
                Synth::aSin.setTable(SIN2048_DATA);
                break;
            case Menu::Waveform::RAMP:
                Synth::aSin.setTable(SAW2048_DATA);
                break;
            case Menu::Waveform::SQUARE:
                Synth::aSin.setTable(SQUARE_NO_ALIAS_2048_DATA);
                break;
              case Menu::Waveform::TRI:
                Synth::aSin.setTable(TRIANGLE2048_DATA);
                break;
              default:
                break;
            }
        }
    }

    void handleOsciFrequency() {
        int freq = analogRead(F_POT);
        freq = kAverageFreq.next(freq);
        freq = kMapFreq(freq);
        aSin.setFreq(freq);
        Menu::osci_freq = freq;
    }

}