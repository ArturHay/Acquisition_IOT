#ifndef CUSB_6XXX_H
#define CUSB_6XXX_H

#include <QString>
#include "NIDAQmx.h"
#include <stdio.h>
#include "NIDAQmx.h"
#include <Windows.h>
#include <unistd.h>
#define NBRE_VAL 10
#define FREQ_SAMPLE 100.0
#define NS 10
#include <QElapsedTimer>
class CUsb_6xxx
{
    private:
        //Identifiant de la tâche d'acquisition
        TaskHandle  m_taskHandle;
        //Nom de la tâche
        QString m_nomTache;
        //Nom de la carte
        QString m_nomCarte;
        //Numéro de la voie
        QString m_numVoie;
        //Mode de connexion du capteur : différentielle ou mode commun
        int m_connexionCapteur;
        //plage de tension du CAN
        double m_tensionMin;
        double m_tensionMax;
        //Fréquence d'échantillonnage du CAN
        double m_freqEchant;
        //Tableau des données acquises
        double m_dataAcq[NBRE_VAL];
        //Tableau des temps
        double m_dataTemps[NBRE_VAL];
        //timeout
        double timeout = 10.0;
        //Nombre de valeur lues
        //deltat
        double deltaT ;
        //read
        int32 m_read;
        //Erreur fonctions bas niveau
        int32 m_error;
        //Itérateur tableau
        int m_i;
        //timer
        QElapsedTimer timer;
    public:
        CUsb_6xxx();
        ~CUsb_6xxx();
        void configuration(QString p_nomTache,QString p_nomCarte,
                           QString p_numVoie,double p_freqEchant);
        //Démarrage acquisition
        void startAcquisition();
        //Acquisition de N points
        void acquerir();
        //Arrêt acquisition
        void stopAcquisition();
        //Suppression de la tâche d'acquisition
        void clearAcquisition();
        //Affichage tableau de mesures
        void printConsole();
        //Retour du pointeur sur tableau dynamique des valeurs
        double *getDataAcq();
        double *getDataTemps();
};

#endif // CUSB_6XXX_H
