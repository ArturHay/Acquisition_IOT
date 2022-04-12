#include "cusb_6xxx.h"

CUsb_6xxx::CUsb_6xxx()
{
    m_taskHandle = nullptr;
    m_nomTache = QString::fromUtf8("non renseigné");
    m_nomCarte = QString::fromUtf8("non renseigné");
    m_numVoie = QString::fromUtf8("non renseigné");
    m_tensionMin = 0;
    m_tensionMax = 0;
    m_freqEchant = 0;
    m_taskHandle = 0;
    m_error = 0;
    m_read = 0;
    m_i = 0;
    m_dataAcq [NBRE_VAL-1] = {0.0};
    m_dataTemps [NBRE_VAL-1] = {0.0};
    deltaT = 1.0/FREQ_SAMPLE;

    //A compléter
}
CUsb_6xxx::~CUsb_6xxx()
{}
void CUsb_6xxx::configuration(QString p_nomTache,QString p_nomCarte,QString p_numVoie,double p_freqEchant)
{
    m_nomTache =p_nomTache;
    m_nomCarte = p_nomCarte;
    m_numVoie = p_numVoie;
    m_nomCarte = m_nomCarte + "/" + m_numVoie;
    m_connexionCapteur = DAQmx_Val_Cfg_Default;
    m_tensionMin = 0;
    m_tensionMax = 6;
    m_freqEchant = p_freqEchant;
    m_taskHandle = nullptr;
    m_error = DAQmxCreateTask(m_nomTache.toStdString().c_str(),&m_taskHandle);
    m_error = DAQmxCreateAIVoltageChan(m_taskHandle,m_nomCarte.toStdString().c_str(),m_nomTache.toStdString().c_str(),DAQmx_Val_RSE,m_tensionMin,m_tensionMax,DAQmx_Val_Volts,nullptr);
    printf("DAQmxCreateAIVoltageChan=%ld\n",DAQmxCreateAIVoltageChan);
    m_error = DAQmxCfgSampClkTiming(m_taskHandle,"",m_freqEchant,DAQmx_Val_Rising,DAQmx_Val_ContSamps,NS);
    for (int i=0; i<NS; i++)
    {
        m_dataTemps[i]= deltaT * i;
        printf("dataTemps[%i]=%lf\n",i,m_dataTemps[i]);
    }


}
void CUsb_6xxx::startAcquisition()
{
    printf("demarrage asquisition\n");
    timer.start();
    m_error = DAQmxStartTask(m_taskHandle);
}
void CUsb_6xxx::acquerir()
{
    DAQmxReadAnalogF64(m_taskHandle,NS,timeout,DAQmx_Val_GroupByScanNumber,m_dataAcq,NS,&m_read,nullptr);
    for(int i=0; i< NS; i++)
    {
        printf("data[%i]=%lf\n",i,m_dataAcq[i]);

    }
}
void CUsb_6xxx::stopAcquisition()
{
    DAQmxStopTask(m_taskHandle);
    printf("fin acquisition\n");}
void CUsb_6xxx::clearAcquisition()
{
    DAQmxClearTask(m_taskHandle);
    printf("clear.\n");
}
void CUsb_6xxx::printConsole()
{
}
double *CUsb_6xxx::getDataAcq()
{
    return(m_dataAcq);
}
double *CUsb_6xxx::getDataTemps()
{   
    return (m_dataAcq);
}


