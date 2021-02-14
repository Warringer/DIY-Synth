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

// use #define for CONTROL_RATE, not a constant
#ifdef CONTROL_RATE
  #undef CONTROL_RATE
  #define CONTROL_RATE 128 // Hz, powers of 2 are most reliable
#endif

#include "synth.h"
#include "rotaryEncoder.h"
#include "constants.h"
#include "display_tft.h"
#include "menu.h"

RotaryEncoder::RotaryEncoder encoder(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_BUTTON);
DisplayTFT::Display display;

void setup() {
  analogWriteResolution(4);
  display.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  Synth::setupSynth();
}

void handleInputs() {
  Synth::handleOsciFrequency();
}

void handleAudio() {
  Synth::handleOsciWaveform();
}

void updateControl() {
  encoder.update();
  RotaryEncoder::encoderState state = encoder.getStatus();;
  Menu::handleMenu(&display, state);
  Menu::handleStatus(&display);
  encoder.resetStatus();
  handleAudio();
  handleInputs();
  Synth::updateControl();
}


int updateAudio() {
  return Synth::updateAudio(); // return an int signal centred around 0
}


void loop() {
  audioHook(); // required here
}