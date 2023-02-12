#include <string.h>
#include <ctype.h>
#include "main.h"
#include "morse-codes.h"


char get_morse_decode(char*);

int morse_decode()
{   
    
    char *p, *input, *r;
    int i, j, length, result, rounds;

    p = malloc(INIT_SIZE *2);
    r = malloc(INIT_SIZE);
    if(p == NULL || r == NULL)
    {
        error_handling(NULLPOINTER);
        return -1;
    }

    (inputtype == KONSOLE) ? (cmd_check()) : (filecheck()); /*Diese funktionen sind in der content.c*/
    (inputtype == KONSOLE) ? (input = insert_cmd()) : (input = insert_file()); /*Diese Funktionen sind in der code.c*/
    

    length = strlen(input);
    i = 0;
    j = 0;
    result = 0;
    rounds = 2; /*rounds wird genutzt fuer die speicherplatzverwaltung von den genutzten pointern*/

    while(i <= length)
    {   
        p[j++] = input[i++];
    
        if(input[i] == 32 || input[i] == 10 || i == length) /*Wenn der Benutzer ein leerzeichen oder \n eingibt, dann werden die bis dahin gespeicherten zeichen als morsecode uebergeben*/
        {
            p[j] = 0;
            if(get_morse_decode(p) == 0) 
            {   
                free(p);
                free(r);
                free(input);
                return 0;
            }
            r[result++] = get_morse_decode(p);/*Gibt den passenden Buchstaben zum morsecode zurueck*/
            if(result % INIT_SIZE == 0)
            {
                r = realloc(r, ++rounds * INIT_SIZE);
                if(r == NULL)
                {
                    error_handling(NULLPOINTER);
                    return -1;
                }
            }
            j = 0;
            i++;
            while(input[i] == 32 || input[i] == 10 || input[i] == 'X')
            {
                i++;
            }
        } 
        if(input[i] == 'X') /*X wird als worttrenner genutzt*/
        {
            p[j] = 0;
            if(get_morse_decode(p) == 0)
            {   
                free(p);
                free(r);
                free(input);
                return 0;
            }
            r[result++] = get_morse_decode(p);
            if(result % INIT_SIZE == 0)
            {
                r = realloc(r, ++rounds * INIT_SIZE);
                if(r == NULL)
                {
                    error_handling(NULLPOINTER);
                    return -1;
                }
            }
            r[result++] = 32;
            if(result % INIT_SIZE == 0)
            {
                r = realloc(r, ++rounds * INIT_SIZE);
                if(r == NULL)
                {
                    error_handling(NULLPOINTER);
                    return -1;
                }
            }
            j = 0;
            i++;
            while(input[i] == 'X' || input[i] == 32 || input[i] == 10)
            {
                i++;
            }
        }
       
    }
    r[result] = 0;
    output_check(r); /*output_check ist in der content.c*/
    free(r);
    free(p);
    free(input);
    return 0;

}





char get_morse_decode(char* str) /*Hier wird geprüft, ob das übergebene Zeichen ein gültiges Zeichen für die Decodierung ist.*/
{   
    int i;
    
    for(i = 0; i < ALPHABET_SIZE; i++)
    {   
        if(strcmp(str, alphabet[i][1]) == 0)
        {   
            
            return *alphabet[i][0];
        }
    }
    for(i = 0; i < NUMBERS_SIZE; i++)
    {
        if(strcmp(str, numbers[i][1]) == 0)
        {
            
            return *numbers[i][0];
        }
    }
         
    for(i = 0; i < PUNCT_SIZE; i++)
    {
        if(strcmp(str, punct[i][1]) == 0)
        {
            
            return *punct[i][0];
        }
    }

    /*Hier startet die Fehlerbehandlung, falls ein unguelter String eingegeben wurde*/
    error_handling(INVALID_INPUT);
    printf("Erstes ungueltiges Wort: %s", str);
    runs++;
    printf("\n\nBitte gib nur gueltige Zeichen ein.\nZ.B. alle lateinischen Klein- und Grossbuchstaben.\nAlle gueltigen Zeichen findest du im 'files' Ordner unter 'Morse-Codes'.\n\nNeue Eingabe:\n");
    morse_decode();
    return '\0';
}


/*Das sind alte Funktionen -> Nicht wichtig fuer die funktionalitaet*/

/*
int decode_file() Diese Funktion dient zur decodierung von Eingaben ueber eine Datei
{   
    char *p, *t, *r;
    int i, j, result, rounds, length, x;
    x = 1;
    rounds = 2;
    i = 0;
    j = 0;
    filecheck();
    
    p = malloc(INIT_SIZE);
    t = malloc(INIT_SIZE);
    if(p == NULL|| t == NULL)
    {
        error_handling(NULLPOINTER); 
        return -1;
    }
    t = insert_file();
    r = malloc(INIT_SIZE);
    
    i = 0;
    rounds = 2;
    result = 0;

    length = strlen(t);
  
    while(i <= length)
    {   
       
        if(t[i] == 32 || i == length)
        {
            p[j] = 0;
            if(get_morse_decode(p) == 0)
                return -1;
            r[result++] = get_morse_decode(p);
            printf("%c", r[result-1]);
            if(result % INIT_SIZE == 0)
            {
                r = realloc(r, INIT_SIZE * ++rounds);
                if(r == NULL)
                { 
                    error_handling(NULLPOINTER); 
                    return -1;
                }
            }
            j = 0;
            i++;
            
            if(t[i] == 32)
            {
                while(t[i] == 32)
                {
                    i++;
                }
            }
        } else if(t[i] == 'X') 
        {
            p[j] = 0;
            if(get_morse_decode(p) == 0)
                return -1;
            r[result++] = get_morse_decode(p);
            printf("%c", r[result-1]);
            r[result] = 32;
            if(result++ % INIT_SIZE == 0)
            {
                r = realloc(r, INIT_SIZE * ++rounds);
                if(r == NULL)
                { 
                    error_handling(NULLPOINTER); 
                    return -1;
                }
            }
            j = 0;
            i++;

            if(t[i] == 32 || t[i] == 'X')
            {
                while(1)
                {   
                    if(t[i] == 32 || t[i] == 'X')
                    {
                        i++;
                    } else
                    {
                        break;
                    }
                }
            }
        }
        p[j++] =t[i++];
    }
    printf("length %i, i %i, result %i", length, i, result);
    r[result] = 0;
    printf("string: %s", r);
    free(t);
    output_check(r);
    free(r);
    return 0;
}


int decode_cmd() Diese funktion dient der decodierung fuer die Eingabe in der Konsole
{
    char *p, *r, *t;
    int i, j, rounds, result, length;
    rounds = 2;
    i = 0;
    result = 0;
    j = 0;

    if(runs == 0)
        cmd_check();
    

    t = malloc(INIT_SIZE);
    r = malloc(INIT_SIZE);
    p = malloc(INIT_SIZE);
    if(t == NULL || p == NULL || r == NULL)
    {
        error_handling(NULLPOINTER); 
        return -1;
    }

    t = insert_cmd();
    
    length = strlen(t);
    while(i <= length) Hier findet die decodierung der Zeichen statt
    {
        if(t[i] == 32 || i == length) 32 = Ascii-code fuer leerzeichen
        {   
            if(i > 0)
            {
                p[j] = 0;
                if(get_morse_decode(p) == 0)
                    return -1;
                r[result++] = get_morse_decode(p);
                if(result % INIT_SIZE == 0) Diese Bedinung wird nach jeder neuzuweisung eines pointers stehen. -> Ueberprueft den Speicher eines Pointers
                {
                    r = realloc(r, INIT_SIZE * ++ rounds);
                    if(r == NULL)
                    {
                        error_handling(NULLPOINTER); 
                        return -1;
                    }
                }
            }
            while(t[i] == 32) Diese Schleifen sind notwendig, falls der Benutzer mehrere Leerzeichen oder 'Worttrenner hintereinander einbaut. Diese werden dann als insg. eines interpretiert.'
            {   
                i++;
            }
            while(t[i] == 'X')
            {
                i++;
            }
            j = 0;
        }
        if(t[i] == 'X')
        {   
            if(i > 0)
            {
                p[j] = 0;
                if(get_morse_decode(p) == 0)
                    return -1;
                r[result++] = get_morse_decode(p);
                r[result] = 32;
                if(result++ % INIT_SIZE == 0)
                {
                    r = realloc(r, INIT_SIZE * ++ rounds);
                    if(r == NULL)
                    {
                        error_handling(NULLPOINTER); 
                        return -1;
                    }
                }
            }
            while(t[i] == 'X') 
            {
                i++;
            }
            while(t[i] == 32) 
            {   
                i++;
            }
            j = 0;
        }
        p[j++] = t[i++];
    }
    r[result] = 0;
    output_check(r); output_check() befindet sich in der content.c Datei
    free(p);
    free(t);
    free(r);
    return 0;
}
*/