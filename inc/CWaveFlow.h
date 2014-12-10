// includes
#include "LPD8806.h"

typedef enum {
    eWaveFlowDirFwd = 0;
    eWaveFlowDirBwd = 1;
} EWaveFlowDirection;

class CWaveFlow
{
  public:
    CWaveFlow(unsigned int* auShift, LPD8806* alLedStrip, unsigned int auNumLeds, unsigned int auWindowSize, unsigned int auSigmaGauss, unsigned int auAmplGauss);
    ~CWaveFlow();
    void calcIntensity();
    void constrainLedStrip();
    void moveLedIntensity();
    void show();
    void applyShift();
  private:
    unsigned int* m_uIntensity[3];
    unsigned int* m_uLedStripIntensity[3];
    unsigned int m_uPosition[3];
    unsigned int m_uNumLeds;
    unsigned int m_uWindowSize;
    unsigned int m_uSigmaGauss;
    unsigned int m_uAmplGauss;
    EWaveFlowDirection m_eWFDir[3];
    LPD8806* m_lLedStrip;
}
