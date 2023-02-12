#include "main.h"

void error_handling(int error) 
{
    switch(error)
    {
        case INVALID_INPUT:
            printf("\n!!Eine oder mehrere Eingaben waren ungueltig!\nBitte ueberpruefe deine Eingegebenen Zeichen!!\n");
            break;
        case NULLPOINTER:
            printf("\n!!Ein oder mehrere Pointer sind fehlerhaft. Starte das Programm neu!!\n");
            break;
        case SYSEX:
            printf("\nProgrammfehler!!\nDas Programm wurde automatisch beendet\n");
            exit(0);
            break;
        case FILEERR:
            printf("\nEine oder mehrere Dateien sind fehlerhaft. Bitte ueberpruefe die Dateien\nund/oder starte das Programm neu!!\n");
            break;
        case OUTPUTERR:
            printf("\nEs gab einen Fehler bei der Ausgabe!! Versuch es nochmal oder starte das Programm neu!!\n");
            break;
        case OPSYSERR:
            printf("\n!!Achtung wahrscheinlich gab es ein Problem mit deinem Betriebssystem\nstelle sicher, dass das Programm auf einem Windows-Betriebssystem laeuft\num alle features nutzen zu koennen\n");
            break;
        case PROGRAMERR:
            printf("\n!!Es gab einen Fehler im Programmablauf!\nStarte das Programm neu!!\n");
            break;
    }

}

int try(int val, int error) /*Diese funktion ist vor allem fuer betriebssystemspezifische funktionen.*/
{   
    if(val == 0)
    {
        return 0;
    }
    else
    {
        if(error != 0)error_handling(error);
    }
    return 1;
}

