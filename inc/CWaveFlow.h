// includes
#include "LPD8806.h"

typedef enum {
    eWaveFlowDirFwd = 0;
    eWaveFlowDirBwd = 1;
} EWaveFlowDirection;

class CWaveFlow
{
  public:
    CWaveFlow(unsigned int* auStartingPoint, LPD8806* alLedStrip, unsigned int auNumLeds,
              unsigned int auWindowSize);
    ~CWaveFlow();
    void calcLedIntensity();
    void constrainLedStrip();
    void moveLedIntensity();
    void show();
  private:
    unsigned int* m_uIntensity[3];
    unsigned int* m_uLedStripIntensity[3];
    unsigned int m_uPosition[3];
    unsigned int m_uNumLeds;
    unsigned Int m_uWindowSize;
    EWaveFlowDirection m_eWFDir[3];
    LPD8806* m_lLedStrip;
}
