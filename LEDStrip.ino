

// includes
#include "LPD8806.h"
#include "CWaveFlow.h"
#include <SPI.h>
#include <math.h>

// defines
#define DF_NUM_LEDS 32U
#define DF_DATA_PIN 2U
#define DF_CLK_PIN 3U
#define DF_WAIT 100U
#define DF_WINDOW_SIZE 9 // ODD NUMBER!
#define DF_GAUSS_SIGMA 6 * DF_WINDOW_SIZE
#define DF_GAUSS_AMPLITUDE 0xEFU


// objects and variables
LPD8806 ledStrip = LPD8806(DF_NUM_LEDS, DF_DATA_PIN, DF_CLK_PIN);
unsigned int uShift[3] = {0, 10, 20};
//CWaveFlow cWaveFlow(uShift, &ledStrip, DF_NUM_LEDS, DF_WINDOW_SIZE, DF_GAUSS_SIGMA, DF_GAUSS_AMPLITUDE);
CWaveFlow cWaveFlow;

void setup() {
  ledStrip.begin();
  Serial.begin(9600);
  ledStrip.show();
  cWaveFlow.setShift(uShift);
  cWaveFlow.setLedStrip(&ledStrip);
  cWaveFlow.setNumLeds(DF_NUM_LEDS);
  cWaveFlow.setWindowSize(DF_WINDOW_SIZE);
  cWaveFlow.setSigmaGauss(DF_GAUSS_SIGMA);
  cWaveFlow.setAmplGauss(DF_GAUSS_AMPLITUDE);
  cWaveFlow.calcIntensity();
  cWaveFlow.applyShift();
}

void loop() {
//  for(unsigned int i = 0; i < DF_NUM_LEDS + 20; i++)
//  {
//    if(i < DF_NUM_LEDS)
//     {
//       ledStrip.setPixelColor(i, 0x0E, 0x00, 0x00);
//       ledStrip.show();
//     }
//     
//     if((i > 5) && (i < DF_NUM_LEDS + 6))
//     {
//       ledStrip.setPixelColor(i-6, 0x00, 0x0E, 0x00);
//       ledStrip.show();
//     }
//     
//     if((i > 10) && (i < DF_NUM_LEDS + 11))
//     {
//       ledStrip.setPixelColor(i-11, 0x00, 0x00, 0x0E);
//       ledStrip.show();
//     }
//     
//     if((i > 15) && (i < DF_NUM_LEDS + 16))
//     {
//       ledStrip.setPixelColor(i-16, 0x00, 0x00, 0x00);
//       ledStrip.show();
//     }
//     
//    delay(DF_WAIT);
//  }
//  cWaveFlow.moveIntensity();
  cWaveFlow.show();
  delay(DF_WAIT);
  
}
