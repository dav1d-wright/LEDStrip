// includes

typedef enum {
    eWaveFlowDirFwd = 0,
    eWaveFlowDirBwd = 1
} EWaveFlowDirection;

typedef enum {
    eModFlow = 0,
    eModAmbient = 1
} EMode;

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
    void setAmplitude(uint8_t auAmplGauss);
    void setMode(EMode aeMod);
    void setAmbientRuns(uint8_t auRuns);
    void setSkip(unsigned int* auSkip);
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
    unsigned int m_uSkip[3];
    unsigned int m_uSkipReset[3];
    unsigned int m_uOverlap;
    unsigned int m_uNumLeds;
    unsigned int m_uAmbientRuns;
    unsigned int m_uAmbientRunsReset;
    unsigned int m_uAmbientCol;
    uint8_t m_uWindowSize;
    unsigned int m_uAmplitude;
    unsigned int m_uLengthIntensity;
    EWaveFlowDirection m_eWFDir[3];
    EMode m_eMod;
    LPD8806* m_lLedStrip;
};
