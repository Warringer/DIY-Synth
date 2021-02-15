#ifndef __SYNTH_H
#define __SYNTH_H

#include <ADC.h>
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <tables/saw2048_int8.h> // saw table generator
#include <tables/square_no_alias_2048_int8.h>
#include <tables/triangle2048_int8.h>
#include <RollingAverage.h>
//#include <AutoMap.h>
#include <IntMap.h>
#include <ADSR.h>

#include <Bounce2.h>

#include "constants.h"
#include "menu.h"

namespace Synth {

    // use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
    extern Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin;

    extern ADSR <CONTROL_RATE, AUDIO_RATE> envelope;

    // Smooth analog Inputs
    extern RollingAverage <int, 16> kAverageFreq;
    extern RollingAverage <int, 16> kAverageAttack;
    extern RollingAverage <int, 16> kAverageRelease;

    extern IntMap kMapFreq;
    extern IntMap kMapAttack;
    extern IntMap kMapRelease;

    extern int kFreq;
    extern int kAttack;
    extern int kRelease;

    extern boolean gate_button;
    extern boolean gate_button_pressed;

    void setupSynth();

    void handleOsciWaveform();
    void handleOsciFrequency();
    void handleADSR();

    void updateControl();
    int updateAudio();

}

#endif