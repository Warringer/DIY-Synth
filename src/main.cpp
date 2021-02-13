#include <Arduino.h>

/*  Example playing a sinewave at a set frequency,
    using Mozzi sonification library.

    Demonstrates the use of Oscil to play a wavetable.

    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or
    check the README or http://sensorium.github.com/Mozzi/

    Mozzi documentation/API
		https://sensorium.github.io/Mozzi/doc/html/index.html

		Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

    Tim Barrass 2012, CC by-nc-sa.
*/

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

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

// use #define for CONTROL_RATE, not a constant
#ifdef CONTROL_RATE
  #undef CONTROL_RATE
  #define CONTROL_RATE 128 // Hz, powers of 2 are most reliable
#endif

#include "rotaryEncoder.h"
#include "constants.h"
#include "display_tft.h"
#include "menu.h"

// Smooth analog Inputs
//RollingAverage <int, 16> kAverageFreq;

IntMap kMapFreq(0, 1024, OSCI_MIN, OSCI_MIN);

int kFreq = 880;

RotaryEncoder::RotaryEncoder encoder(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_BUTTON);
DisplayTFT::Display display;

void setup() {
  analogWriteResolution(4);
  display.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TFT_LED, OUTPUT);
  analogWrite(TFT_LED, 14);
  startMozzi(CONTROL_RATE); // :)
  aSin.setFreq(kFreq);
}

void handleInputs() {
  //int freq = mozziAnalogRead(FREQ_KNOB);
  //freq = kMapFreq(freq);
  //aSin.setFreq(freq);
}

void handleAudio() {
  if (Menu::osci_waveform_changed) {
    Menu::osci_waveform_changed = false;
    switch (Menu::osci_waveform) {
      case Menu::Waveform::SINE:
        aSin.setTable(SIN2048_DATA);
        break;
      case Menu::Waveform::RAMP:
        aSin.setTable(SAW2048_DATA);
        break;
      case Menu::Waveform::SQUARE:
        aSin.setTable(SQUARE_NO_ALIAS_2048_DATA);
        break;
      case Menu::Waveform::TRI:
        aSin.setTable(TRIANGLE2048_DATA);
        break;
      default:
        break;
    }
  }
}

void updateControl() {
  encoder.update();
  RotaryEncoder::encoderState state = encoder.getStatus();;
  Menu::handleMenu(&display, state);
  Menu::handleStatus(&display);
  encoder.resetStatus();
  handleAudio();
  handleInputs();
}


int updateAudio() {
  return aSin.next(); // return an int signal centred around 0
}


void loop() {
  audioHook(); // required here
}