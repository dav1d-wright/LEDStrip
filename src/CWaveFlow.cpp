// includes
#include "LPD8806.h"



// function implementations
CWaveFlow::CWaveFlow(unsigned int* auShift, LPD8806* alLedStrip, unsigned int auNumLeds,
                     unsigned int auWindowSize, unsigned int auSigmaGauss, unsigned int auAmplGauss):
    m_uPosition(auShift), m_lLedStrip(alLedStrip), m_uNumLeds(auNumLeds), m_uWindowSize(auWindowSize),
    m_uSigmaGauss(auSigmaGauss), m_uAmplGauss(auAmplGauss)
{
    for(unsigned int i = 0; i < 3; i++)
    {
        m_eWFDir[i] = eWaveFlowDirFwd;
        m_uIntensity[i] = new(unsigned int [2 * auWindowSize + m_uNumLeds]);
        m_uLedStripIntensity[i] = new(unsigned int [m_uNumLeds]);
        for(unsigned int j = 0; j < m_uNumLeds + 2 * auWindowSize; j++)
        {
            m_uIntensity[i][j] = 0;
        }
    }
}

CWaveFlow::~CWaveFlow()
{
    delete[] m_uIntensity;
    delete[] m_uLedStripIntensity
}

void CWaveFlow::calcIntensity()
{
    int n;
    for(unsigned int j = 0; i < m_uWindowSize; i++)
    {
        n = i - ((m_uWindowSize +1) / 2);
        m_uIntensity[0][j] = m_uAmplGauss * exp(n/(2*m_uSigmaGauss*m_uSigmaGauss));
        m_uIntensity[1][j] = m_uAmplGauss * exp(n/(2*m_uSigmaGauss*m_uSigmaGauss));
        m_uIntensity[2][j] = m_uAmplGauss * exp(n/(2*m_uSigmaGauss*m_uSigmaGauss));
    }
}

void CWaveFlow::applyShift()
{
    for(unsigned int i = 0; i < 3, i++)
    {
        for (unsigned int j = 2 * auWindowSize + m_uNumLeds - 1; j >= 0 ; j--)
        {
            m_uIntensity[i][j] = m_uIntensity[i][j-m_uPosition[i]];
        }
    }
}

void CWaveFlow::constrainLedStrip()
{
    for(unsigned int i = 0; i < 3; i++)
    {
        for(unsigned int j = 0; j < 2 * auWindowSize + m_uNumLeds; j++)
        {
            if((j > auWindowSize) && (j < m_uNumLeds))
            {
                m_uLedStripIntensity[i][j - auWindowSize - 1] = m_uIntensity[i][j];
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
            for(unsigned int jFwd = 2 * auWindowSize + m_uNumLeds -1; j >= 0; j--)
            {
                m_untensity[i][jFwd] = m_uIntensity[i][jFwd - 1];
            }
            m_uPosition++;
        }
        else
        {
            for(unsigned int jFwd = 0; j <  2 * auWindowSize + m_uNumLeds -1; j++)
            {
                m_uLedIntensity[i][jFwd - 1] = m_uLedIntensity[i][jFwd];
            }
            m_uPosition--;
        }
    }
    this->constrainLedStrip();
    m_lLedStrip->show();
}


void CWaveFlow::show()
{
    // TODO (wrapper function for LPD8806::show())
}