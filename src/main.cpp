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

uint16_t help = 1;
int help2 = 1;
int i = 0;
const char *testList[] = { "Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta", "Eta", "Theta", "Iota", "Kappa"};

void updateControl(){
  encoder.update();
  RotaryEncoder::encoderState state = encoder.getStatus();;
  int t = display.userSelectionList("Test", &help, testList, 10, state);
  if (t > 0) {
    help2 += 100;
  }//*/
  //int t = display.userInputValue("Display", "Display Intensity", &help2, 0, 15, 1, "", state);
  /**if (t > 0) {
    analogWrite(TFT_LED, help);
  }//*/
  //int t = display.userMessage("Test", "Line 1\nLine 2\nLine 3", state);
  display.drawStatus();
  encoder.resetStatus();
  display.update();
  // put changing controls in here
}


int updateAudio(){
  return aSin.next(); // return an int signal centred around 0
}


void loop(){
  audioHook(); // required here
}