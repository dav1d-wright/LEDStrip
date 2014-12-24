

// includes
#include "LPD8806.h"
#include "CWaveFlow.h"
#include <SPI.h>
#include <math.h>

// defines
#define DF_NUM_LEDS 32U
#define DF_DATA_PIN 2U
#define DF_CLK_PIN 3U
#define DF_WAIT 50U
#define DF_WINDOW_SIZE 10L // ODD NUMBER!
#define DF_GAUSS_SIGMA 6 * DF_WINDOW_SIZE
#define DF_GAUSS_AMPLITUDE 0xEFU


// objects and variables
LPD8806 ledStrip = LPD8806(DF_NUM_LEDS, DF_DATA_PIN, DF_CLK_PIN);
unsigned int uShift[3] = {DF_WINDOW_SIZE, DF_WINDOW_SIZE+15, DF_WINDOW_SIZE+20};
unsigned int uSkip[3] = {0, 1, 2};
CWaveFlow cWaveFlow;

void setup() {
  ledStrip.begin();
  Serial.begin(9600);
  ledStrip.show();
  cWaveFlow.setShift(uShift);
  cWaveFlow.setSkip(uSkip);
  cWaveFlow.setLedStrip(&ledStrip);
  cWaveFlow.setNumLeds(DF_NUM_LEDS);
  cWaveFlow.setWindowSize(DF_WINDOW_SIZE);
  cWaveFlow.setAmplitude(DF_GAUSS_AMPLITUDE);
  cWaveFlow.calcIntensity();
  cWaveFlow.applyShift();
  cWaveFlow.moveIntensity();
}

void loop() {
  cWaveFlow.moveIntensity();
  delay(DF_WAIT);
}
