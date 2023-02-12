#include <ctype.h>
#include <string.h>
#include "main.h"
#include "morse-codes.h"



int morse_code()
{
    char *p, *r, *input;
    int i, j, result, rounds, length, strlength;
    i = 0;
    rounds = 2;
    result = 0;
    p = malloc(INIT_SIZE);
    r = malloc(INIT_SIZE);
    input = malloc(INIT_SIZE);
    if(p == NULL || r == NULL || input == NULL)
    {
        error_handling(NULLPOINTER); 
        return -1;
    }

    if(inputtype == KONSOLE)
    {
        if(runs == 0)cmd_check();
        input = insert_cmd();
    } else 
    {
        filecheck();
        input = insert_file();
    }
    strlength = strlen(input);

    while(i < strlength)
    {   
        p = get_morse_code(input[i++]);
        if(*p == 0)
        {
            return -1;
        }
        length = strlen(p);
        if(strcmp(p, "X") == 0 && i > 0)
        {
            r[result -1] = 'X';
        } else 
        {
            for(j = 0; j < length; j++)
            {   
                r[result++] = p[j];
                if(result % INIT_SIZE == 0)
                {   
                    r = realloc(r,INIT_SIZE * ++rounds );
                    if(r == NULL)
                    {
                        error_handling(NULLPOINTER); 
                        return -1;
                    }
                }
            }
            if(r[result] != 'X')
            {
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
            }
        }
    }
    r[result] = 0;
    output_check(r);
    free(input);
    free(r);
    return 0;
}

char* insert_file() /*Die Funktion erfasst Eingaben ueber eine Datei*/
{   
    FILE * fp; 
    char *p, *t;
    int i, x, rounds;
    rounds = 2;
    x = 0;
    i = 0;
    p = malloc(INIT_SIZE);
    t = malloc(INIT_SIZE);
    
    if(direction == CODE)fp = fopen("files/code.txt", "r");
    else { fp = fopen("files/decode.txt", "r");}
    
    while(fread(p, 1, 1, fp) == 1)
    {       
        t[i++] = *p;
        if(++x % INIT_SIZE == 0)
        {   
            t = realloc(t, INIT_SIZE * ++rounds);
            if(t == NULL)
            {   
                error_handling(NULLPOINTER);
                return '\0';
            }
        }
    }
    t[i] = 0;
    fclose(fp); 
    free(p);
    return t;
}

char* insert_cmd() /*Diese Funktion erfasst die Eingaben ueber die Kommandozeile*/
{   
    
    char* p;
    int counter, round;
    char c;
    round = 2;
    counter = 0;
    p = malloc(INIT_SIZE);
    if(p == NULL) 
    {
        error_handling(NULLPOINTER); 
        return '\0';
    }
    c = getchar();
    while(c != '\n') /*Eingabe wird p zugewiesen*/
    {   
        
        p[counter++] = c;
        if(counter % INIT_SIZE == 0)
        {
            p = realloc(p, (++round) * INIT_SIZE);
            if(p == NULL)
            { 
                error_handling(NULLPOINTER);
                return '\0';
            }
        }
        c = getchar();
    }
    p[counter] = '\0';

    return p;
}


char* get_morse_code(char c) /*Diese Funktion prueft, ob das eingegebene Zeichen gueltig ist*/
{
    int i;

    if(isspace(c) ||c == 10)
    {   
        return "X";

    }
    c = toupper(c);
    if(c >= 65)
    {
        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            if(c == *alphabet[i][0])
            {   
                return alphabet[i][1];
            }
        }
    } else 
    {

        for(i = 0; i < NUMBERS_SIZE; i++)
        {
            if(c == *numbers[i][0])
            {
                return numbers[i][1];
            }
        }
        for(i = 0; i < PUNCT_SIZE; i++)
        {   
            if(c == *punct[i][0])
            {
                return punct[i][1];
            }
        }
    }
    /*Ab hier startet die Fehler-behandlung*/
    error_handling(INVALID_INPUT);
    printf("Erstes ungueltiges Zeichen: %c", c);
    
    printf("\n\nBitte gib nur gueltige Zeichen ein.\nZ.B. alle lateinischen Klein- und Grossbuchstaben.\nAlle gueltigen Zeichen findest du im 'files' Ordner unter 'Morse-Codes'.\n\nNeue Eingabe:\n");
    runs++;
    morse_code();
    
    
    return "\0";
    
}


/*
int code_file() Diese Funktion dient zur Codierung einer Eingabe ueber eine Datei
{

    Deklariert einen Zeiger vom Datentyp FILE
    char *p, *t, *r;
    int i, j, result, rounds, length, strlength, x;
    x = 1;
    i = 0;
    rounds = 1;

    filecheck();
    
    
    if(fp == NULL) Liefert NULL zurueck, wenn die Datei nicht gefunden wurde
    { 
        error_handling(FILEERR); 
        return -1; 
    } 
    p = malloc(INIT_SIZE);
    t = malloc(INIT_SIZE);
    r = malloc(INIT_SIZE);
    if(p == NULL || t == NULL || r == NULL)
    {
        error_handling(NULLPOINTER); 
        return -1;
    }
    
    while(fread(p, 1, 1, fp) == 1)
    {       
            
        t[i++] = *p;
        if(++x % INIT_SIZE == 0)
        {   
            t = realloc(t, INIT_SIZE * ++rounds);
            if(t == NULL)
            {   
                error_handling(NULLPOINTER);
                return -1;
            }
        }
    }
    t[i] = 0;
    fclose(fp); 
    free(p);
    
    rounds = 1;
    i = 0;
    result = 0;
    
    strlength = strlen(t);
    while(i < strlength)
    {   
        p = get_morse_code(t[i++]);
        if(*p == 0)
        {
            return -1;
        }
        length = strlen(p);
        if(strcmp(p, "X") == 0 && i > 0)
        {
            r[result -1] = 'X';
        } else 
        {
            for(j = 0; j < length; j++)
            {   
                r[result++] = p[j];
                if(result % INIT_SIZE == 0)
                {   
                    r = realloc(r,INIT_SIZE * ++rounds );
                    if(r == NULL)
                    {
                        error_handling(NULLPOINTER); 
                        return -1;
                    }
                }
            }
            if(r[result] != 'X')
            {
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
            }
        }
    }

    r[result-1] = 0;
    output_check(r);
    free(r);
    free(t);
    return 0;
}
*/

/*
int code_cmd() Diese Funktion sorgt fuer die Codierung einer Eingabe ueber die Konsole
{   
    char *p, *r, *tmp;
    int counter, i, j, length, result, round;
    result = 0;
    round = 1;

    
    
    r = malloc(INIT_SIZE);
    p = malloc(INIT_SIZE);
    if(p == NULL || r == NULL)
    {
        error_handling(NULLPOINTER);
        return -1;
    }

    Die insert()-funktion liefert einen Pointer auf den eingegebenen String
    counter = strlen(p);
    i = 0;
    while(i < counter)
    {       
            if(isspace(p[i]))
            {   
                r[result++] = 'X';
                if(result % INIT_SIZE == 0)
                {   
                    r = realloc(r, INIT_SIZE * (++round));
                    if(r == NULL) 
                    {
                        error_handling(NULLPOINTER); error-handling ist in error-handler.c
                        return -1;
                    }
                }
                while(isspace(p[i]))
                {
                    i++;
                }
            }

            tmp = get_morse_code(p[i++]);
            if(tmp == NULL) 
            {
                error_handling(NULLPOINTER);
                return -1;
            }
            if(*tmp == 0)
            {
                return -1;
            }

            length = strlen(tmp);
            for(j = 0; j < length; j++) 
            {
                r[result++] = tmp[j]; 
                if(result % INIT_SIZE == 0)
                {
                    r = realloc(r, INIT_SIZE * (++round));
                    if(r == NULL) 
                    {
                        error_handling(NULLPOINTER);
                        return -1;
                    }
                }
            }
            if(isspace(p[i])) 
            {
                r[result++] = 'X';
                if(result % INIT_SIZE == 0)
                {   
                    r = realloc(r, INIT_SIZE * (++round));
                    if(r == NULL) 
                    {
                        error_handling(NULLPOINTER);
                        return -1;
                    }
                }
                while(isspace(p[i]))
                {
                    i++;
                }
            }
            else 
            {
                r[result++] = 32;
                if(result % INIT_SIZE == 0)
                {
                    r = realloc(r, INIT_SIZE * (++round));
                    if(r == NULL) 
                    {
                        error_handling(NULLPOINTER);
                        return -1;
                    }
                }
            }
    }

    r[result] = 0;
    output_check(r);
    free(p);
    free(r);
    return 0;
}
*/