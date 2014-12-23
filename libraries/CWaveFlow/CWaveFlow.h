// includes

typedef enum {
    eWaveFlowDirFwd = 0,
    eWaveFlowDirBwd = 1
} EWaveFlowDirection;

class CWaveFlow
{
  public:
    // constructor/destructo
    CWaveFlow();
    //CWaveFlow(unsigned int auShift[3], LPD8806* alLedStrip, unsigned int auNumLeds, unsigned int auWindowSize, unsigned int auSigmaGauss, unsigned int auAmplGauss);
    ~CWaveFlow();
    // set methods
    void setShift(unsigned int* auShift);
    void setLedStrip(LPD8806* alLedStrip);
    void setNumLeds(unsigned int auNumLeds);
    void setWindowSize(unsigned int auWindowSize);
    void setSigmaGauss(int aiSigmaGauss);
    void setAmplGauss(int aiAmplGauss);
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
    int m_iSigmaGauss;
    int m_iAmplGauss;
    EWaveFlowDirection m_eWFDir[3];
    LPD8806* m_lLedStrip;
};
