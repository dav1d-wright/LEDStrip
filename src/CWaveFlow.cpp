// includes
#include "LPD8806.h"



// function implementations
CWaveFlow::CWaveFlow(unsigned int* auDelay, LPD8806* alLedStrip, unsigned int auNumLeds,
                     unsigned int auWindowSize):
    m_uPosition(auStartingPoint), m_lLedStrip(alLedStrip), m_uNumLeds(auNumLeds), m_uWindowSize(auWindowSize)
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
    // TODO
}

void CWaveFlow::constrainLedStrip()
{
    for(unsigned int i = 0; i < 3; i++)
    {
        for(unsigned int j = 0; j < 2 * auWindowSize + m_uNumLeds; j++)
        {
            if((j > auWindowSize) && (j < m_uNumLeds))
            {
                m_uLedStripIntensity[i][j - auWindowSize - 1] = m_uLedIntensity[i][j];
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
                m_untensity[i][jFwd] = m_uLedIntensity[i][jFwd - 1];
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
    m_lLedStrip->show();
}


void CWaveFlow::show()
{
    // TODO (wrapper function for LPD8806::show())
}