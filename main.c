/*
    @Author: Daniel Feustel
    @Version: 23.01.2023
*/

#include "main.h"



int main()
{    
    runs = 0; /*Eine globale Variable, die Angibt wie viele Durchlaeufe das Programm gemacht hat*/
    content(0); /*Parameter 0, wichtig fuer die Anfangssequenz*/
    do
    {
        switch(direction) /*Grosser switch-case block. Sorgt fuer die Verwaltung von Eingabe-medium und Codierung/decodierung*/
        {
            case CODE:
                switch(inputtype){
                    case DATEI:
                        morse_code();
                        break;
                    case KONSOLE:
                        morse_code();
                        break;
                    default: 
                        error_handling(PROGRAMERR);
                        break;
                }
                break;
            case DECODE:
                switch(inputtype){
                    case DATEI:
                        morse_decode();
                        break;
                    case KONSOLE:
                        morse_decode();
                        break;
                    default: 
                        error_handling(PROGRAMERR);
                        break;
                }
                break;
            default: 
                error_handling(PROGRAMERR);
                 break;
        }
    } while(quit() == 0);

    return 0;
}

int quit() /*Wurde ins Leben gerufen, damit der Benutzer nicht nach jeder Eingabe das Programm schließen und neustarten muss*/
{   
    char c;
    printf("\n\nMoechten Sie das Programm verlassen?\nja(y)/Nein(n)");
    
    while(1)
    {
        c = getchar();
        flush_buff();

        if(toupper(c)== 'Y' || toupper(c) == 'J')
        {   
            return 1;
        } 
        else if(toupper(c) == 'N')
        {   
            runs++;
            more_runs();
            return 0;
        }
        error_handling(INVALID_INPUT);
    }
}
