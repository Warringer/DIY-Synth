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

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

// use #define for CONTROL_RATE, not a constant
#ifdef CONTROL_RATE
  #undef CONTROL_RATE
  #define CONTROL_RATE 128 // Hz, powers of 2 are most reliable
#endif

int freq = 880;

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
  pinMode(TFT_LED, OUTPUT);
  analogWrite(TFT_LED, 14);
  startMozzi(CONTROL_RATE); // :)
  aSin.setFreq(freq); // set the frequency
}

void handleAudio() {
  
}

void updateControl() {
  encoder.update();
  RotaryEncoder::encoderState state = encoder.getStatus();;
  handleMenu(&display, state);
  handleStatus(&display);
  encoder.resetStatus();
}


int updateAudio() {
  return aSin.next(); // return an int signal centred around 0
}


void loop() {
  audioHook(); // required here
}