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

#include "constants.h"
#include "menu.h"

namespace Synth {

    // use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
    extern Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin;

    // Smooth analog Inputs
    extern RollingAverage <int, 16> kAverageFreq;

    extern IntMap kMapFreq;

    extern int kFreq;

    void handleOsciWaveform();
    void handleOsciFrequency();

}

#endif