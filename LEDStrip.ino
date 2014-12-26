

// includes
#include "LPD8806.h"
#include "CWaveFlow.h"
#include <SPI.h>
#include <math.h>

// defines
#define DF_NUM_LEDS 160U // 1m -> 32, 5m -> 160
#define DF_DATA_PIN 2U
#define DF_CLK_PIN 3U
#define DF_MOD_PIN 22U
#define DF_MOD_AMBIENT_RUNS 500U
#define DF_WAIT_AMBIENT 50U
#define DF_WAIT_FLOW 50U
#define DF_WINDOW_SIZE 100L // ODD NUMBER!
#define DF_AMPLITUDE 0xEFU


// objects and variables
LPD8806 ledStrip = LPD8806(DF_NUM_LEDS, DF_DATA_PIN, DF_CLK_PIN);
unsigned int uShift[3] = {DF_WINDOW_SIZE, DF_WINDOW_SIZE+75, DF_WINDOW_SIZE+120};
unsigned int uSkip[3] = {1, 0, 0};
CWaveFlow cWaveFlow;
uint8_t uModeInp;
EMode eMod;

void setup() {
  ledStrip.begin();
  Serial.begin(9600);
  ledStrip.show();
  
  pinMode(DF_MOD_PIN, INPUT);
  pinMode(DF_MOD_PIN, INPUT_PULLUP);
  uModeInp = digitalRead(DF_MOD_PIN);
  eMod = (uModeInp == 1) ? eModAmbient : eModFlow;
  Serial.println(eMod);
  
  cWaveFlow.setLedStrip(&ledStrip);
  cWaveFlow.setNumLeds(DF_NUM_LEDS);
  cWaveFlow.setAmplitude(DF_AMPLITUDE);
  cWaveFlow.setMode(eMod);

  if(eMod == eModFlow)
  {
    cWaveFlow.setShift(uShift);
    cWaveFlow.setSkip(uSkip);
    cWaveFlow.setWindowSize(DF_WINDOW_SIZE);
    cWaveFlow.calcIntensity();
  }
  
  if(eMod == eModAmbient){
    cWaveFlow.setAmbientRuns(DF_MOD_AMBIENT_RUNS);
  }

}

void loop() {
  cWaveFlow.moveIntensity();
  
  if(eMod == eModAmbient)
  {
    delay(DF_WAIT_AMBIENT);
  }
  
  if(eMod == eModFlow)
  {
    delay(DF_WAIT_FLOW);
  }
}
