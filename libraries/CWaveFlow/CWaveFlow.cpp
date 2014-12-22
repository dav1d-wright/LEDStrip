// includes
#include "LPD8806.h"
#include "CWaveFlow.h"


// function implementations
//CWaveFlow::CWaveFlow(unsigned int auShift[3], LPD8806* alLedStrip, unsigned int auNumLeds,
//                     unsigned int auWindowSize, unsigned int auSigmaGauss, unsigned int auAmplGauss):
//    m_uPosition(auShift), m_lLedStrip(alLedStrip), m_uNumLeds(auNumLeds), m_uWindowSize(auWindowSize),
//    m_uSigmaGauss(auSigmaGauss), m_uAmplGauss(auAmplGauss)
//{
//    for(unsigned int i = 0; i < 3; i++)
//    {
//        m_eWFDir[i] = eWaveFlowDirFwd;
//        m_uIntensity[i] = new(unsigned int [2 * auWindowSize + m_uNumLeds]);
//        m_uLedStripIntensity[i] = new(unsigned int [m_uNumLeds]);
//        for(unsigned int j = 0; j < m_uNumLeds + 2 * auWindowSize; j++)
//        {
//            m_uIntensity[i][j] = 0;
//        }
//    }
//}

CWaveFlow::CWaveFlow()
{
    m_uWindowSize = 1;
    m_uSigmaGauss = 1;
    m_uAmplGauss = 0x0F;
    m_lLedStrip = 0;
    
    for(unsigned int i = 0; i < 3; i++)
    {
        m_uPosition[i] = 0;
        m_eWFDir[i] = eWaveFlowDirFwd;
        m_uIntensity[i] = 0;;
        m_uLedStripIntensity[i] = 0;;
    }
    this->constrainLedStrip();
//    this->show();
}

CWaveFlow::~CWaveFlow()
{
    //delete[] m_uIntensity;
    //delete[] m_uLedStripIntensity
}

void CWaveFlow::setShift(unsigned int* auShift)
{
    m_uPosition[0] = auShift[0];
    m_uPosition[1] = auShift[1];
    m_uPosition[2] = auShift[2];
}

void CWaveFlow::setLedStrip(LPD8806* alLedStrip)
{
    m_lLedStrip = alLedStrip;
}

void CWaveFlow::setNumLeds(unsigned int auNumLeds)
{
    m_uNumLeds = auNumLeds;
}

void CWaveFlow::setWindowSize(unsigned int auWindowSize)
{
    m_uWindowSize = auWindowSize;
}

void CWaveFlow::setSigmaGauss(unsigned int auSigmaGauss)
{
    m_uSigmaGauss = auSigmaGauss;
}

void CWaveFlow::setAmplGauss(unsigned int auAmplGauss)
{
    m_uAmplGauss = auAmplGauss;
}

//calculate gaussian window
void CWaveFlow::calcIntensity()
{
    for(unsigned int i = 0; i < 3; i++)
    {
        m_uIntensity[i] = new(unsigned int [2 * m_uWindowSize + m_uNumLeds]);
        m_uLedStripIntensity[i] = new(unsigned int [m_uNumLeds]);
        for(unsigned int j = 0; j < m_uNumLeds + 2 * m_uWindowSize; j++)
        {
            m_uIntensity[i][j] = 0;
//            m_uIntensity[i][j] = 0xefU;
        }
    }
    this->constrainLedStrip();
    int n;
    for(unsigned int i = 0; i < m_uWindowSize; i++)
    {
        n = i - ((m_uWindowSize +1) / 2);
        m_uIntensity[0][i] = m_uAmplGauss * exp(n/(2*m_uSigmaGauss*m_uSigmaGauss));
        m_uIntensity[1][i] = m_uAmplGauss * exp(n/(2*m_uSigmaGauss*m_uSigmaGauss));
        m_uIntensity[2][i] = m_uAmplGauss * exp(n/(2*m_uSigmaGauss*m_uSigmaGauss));
    }

    this->show();
}

//initial shift between r, g, b
void CWaveFlow::applyShift()
{
    for(unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 2 * m_uWindowSize + m_uNumLeds - 1; j >= 0 ; j--)
        {
            m_uIntensity[i][j] = m_uIntensity[i][j-m_uPosition[i]];
            if(j == 1)
            {
                m_uIntensity[i][0] = 0;
            }
        }
    }
    this->constrainLedStrip();
    this->show();

}

void CWaveFlow::constrainLedStrip()
{
    for(unsigned int i = 0; i < 3; i++)
    {
        for(unsigned int j = 0; j < 2 * m_uWindowSize + m_uNumLeds; j++)
        {
            if((j > m_uWindowSize) && (j < m_uNumLeds))
            {
                m_uLedStripIntensity[i][j] = m_uIntensity[i][j];
            }
        }
    }
}

void CWaveFlow::moveIntensity()
{
    for(unsigned int i = 0; i < 3; i++)
    {
        if(m_eWFDir[i] == eWaveFlowDirFwd)
        {
            for(unsigned int jFwd = 2 * m_uWindowSize + m_uNumLeds - 1; jFwd >= 0; jFwd--)
            {
                if(jFwd == 0)
                {
                    m_uIntensity[i][jFwd] = 0;
                }
                else
                {
                    m_uIntensity[i][jFwd] = m_uIntensity[i][jFwd - 1];
                }
            }
            m_uPosition[i]++;
            if(m_uPosition[i] == 2 * m_uWindowSize + m_uNumLeds)
            {
                m_eWFDir[i] = eWaveFlowDirBwd;
            }
        }
        else
        {
            for(unsigned int jBwd = 0; jBwd <  2 * m_uWindowSize + m_uNumLeds - 1; jBwd++)
            {
                if(jBwd == 2 * m_uWindowSize + m_uNumLeds - 1)
                {
                    m_uIntensity[i][jBwd] = 0;
                    
                }
                else
                {
                    m_uIntensity[i][jBwd] = m_uIntensity[i][jBwd + 1];
                }
                
            }
            m_uPosition[i]--;
            if(m_uPosition[i] == 0)
            {
                m_eWFDir[i] = eWaveFlowDirFwd;
            }
        }
    }
    this->constrainLedStrip();
    this->show();
}


void CWaveFlow::show()
{
    for (unsigned int i = 0; i < m_uNumLeds; i++) {
        m_lLedStrip->setPixelColor(i, m_uLedStripIntensity[0][i], 0, 0);
//        m_lLedStrip->setPixelColor(i, m_uLedStripIntensity[0][i], m_uLedStripIntensity[1][i], m_uLedStripIntensity[2][i]);
    }
    m_lLedStrip->show();
}