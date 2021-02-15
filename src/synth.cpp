#include "synth.h"

namespace Synth {

    // use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
    Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

    ADSR <CONTROL_RATE, AUDIO_RATE> envelope;

    // Smooth analog Inputs
    RollingAverage <int, 16> kAverageFreq;
    RollingAverage <int, 16> kAverageAttack;
    RollingAverage <int, 16> kAverageRelease;

    IntMap kMapFreq(0, 1024, OSCI_MIN, OSCI_MAX);
    IntMap kMapAttack(0, 1024, ATTACK_MIN, ATTACK_MAX);
    IntMap kMapRelease(0, 1024, RELEASE_MIN, RELEASE_MAX);

    int kFreq = 880;
    int kAttack = 10;
    int kRelease = 10;

    boolean gate_button = false;
    boolean gate_button_pressed = false;

    void setupSynth() {
        //gate_button = new Bounce();
        //gate_button->attach(GATE_BUTTON, INPUT_PULLUP);
        //gate_button->interval(5);
        pinMode(GATE_BUTTON, INPUT_PULLUP);
        envelope.setADLevels(255,64);
        envelope.setTimes(200,0,0,500); // 10000 is so the note will sustain 10 seconds unless a noteOff comes
        startMozzi(CONTROL_RATE); // :)
    }

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

    void handleADSR() {
        int attack = analogRead(ATTACK_POT);
        attack = kAverageAttack.next(attack);
        attack = kMapAttack(attack);
        int release = analogRead(DECAY_POT);
        release = kAverageRelease.next(release);
        release = kMapAttack(release);
        envelope.setAttackTime(attack);
        envelope.setReleaseTime(release);
    }

    void updateControl() {
        handleOsciWaveform();
        handleOsciFrequency();
        handleADSR();
        if (digitalRead(GATE_BUTTON)) {
            gate_button = false;
        } else {
            gate_button = true;
        }
        if (gate_button && !gate_button_pressed) {
            gate_button_pressed = true;
            envelope.noteOn();
            digitalWrite(LED_BUILTIN, HIGH);
        }
        if (!gate_button && gate_button_pressed) {
            gate_button_pressed = false;
            envelope.noteOff();
            digitalWrite(LED_BUILTIN, LOW);
        }
        envelope.update();
    }

    int updateAudio() {
        return (int) (envelope.next() * aSin.next())>>8;
    }

}