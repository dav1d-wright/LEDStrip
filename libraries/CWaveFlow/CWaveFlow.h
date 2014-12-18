// includes

typedef enum {
    eWaveFlowDirFwd = 0,
    eWaveFlowDirBwd = 1
} EWaveFlowDirection;

class CWaveFlow
{
  public:
    CWaveFlow(unsigned int auShift[3], LPD8806* alLedStrip, unsigned int auNumLeds, unsigned int auWindowSize, unsigned int auSigmaGauss, unsigned int auAmplGauss);
    ~CWaveFlow();
    //calculate gaussian window
    void calcIntensity();
    void constrainLedStrip();
    void moveIntensity();
    void show();
    //initial shift between r, g, b
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
};
