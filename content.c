#include <ctype.h>
#include <string.h>
#include "main.h"

char* seq = "Herzlich Willkommen bei Morse-Decoder";

void welcome() /*Anfangssequenz*/
{	
	int i, counter;
	counter = 0;
	if(try(system("cls"), 0) != 0)
	{
		try(system("clear"), OPSYSERR); /*Falls Benutzer Linux benutzt*/
	}

	printf("\n\n");
	
	while(1)
	{
		printf("-");
		Beep(0, 50);
		
		if(counter == 5)
		{
			for(i = 0; i <= 36; i++)
			{	
				printf("%c",seq[i]);
				
				Beep(0, 40);
			}
		} else if(counter == 11)
		{
			break;
		}

		counter++;
	}
	printf("\n\n");
	
}

/*Content Management: Die ganze Datei 'content.c' sorgt fuer die Regelung von fast allen Eingaben und Ausgaben auf der Konsole und in der Datei*/
int content(int status)
{	
	char c;
	if(status == 0)		/*Status = 0, nur beim Programmstart*/
		welcome();		
	
	printf("Moechtest du die Eingabe ueber:\n(1) Die Konsole\n(2) Eine Datei\n\n");

	while(1) 
	{
		c = getchar();
		if(c == '1' || c == '2')
		{
			break;
		}
		while(c != '\n')
		{
			c = getchar();
		}

		printf("- Gebe eine '1' ein wenn du den zu uebersetzenden Text ueber die Konsole eingeben moechtest\n");
		printf("- Gebe eine '2' ein wenn du den zu uebersetzenden Text ueber eine Datei eingeben moechtest\n");
		
	}
	
	switch(c)
	{
		case '2': 
			inputtype = DATEI;
			break;
		
		case '1':
			inputtype = KONSOLE;
			break;
	}

	flush_buff(); /*flush_buff befindet sich am Ende von 'content.c'*/
	input(inputtype, 0);
	return 0;
}

int input(int in, int status)
{
	char c;
	char *p;
	int counter, round;
	round = 1; /*round ist wichtig fuer die Speicherplatzverwaltung*/
	counter = 0;

	p = malloc(INIT_SIZE); 
	if(p == NULL)
	{
		error_handling(NULLPOINTER);   /*error_handling befindet sich in der Datei 'error_handler.c'*/
		return -1;			
	} 					
	
	if(status == 1) /*Status = 1, ist dann wahr, wenn eine falsche Eingabe gemacht wurde. (Rekursiver Aufruf)*/
	{	
		printf("\n!!!!!!!!!!");
		printf("\nGebe die Zeichenfolge: 'decodieren' ein, \nwenn du Morse-Code decodieren moechtest.\n");
		printf("Gebe die Zeichenfolge: 'codieren' ein, \nwenn du einen beliebigen Text zu Morse-Code uebersetzen\nmoechtest");
		printf("\n!!!!!!!!!!\n\n");
	}
	
	printf("\nMoechtest du 'decodieren'(Morse -> Deutsch)\noder 'codieren'(Deutsch -> Morse)?\n");
	c = getchar();
	while(c != '\n')
	{		
		p[counter++] = c;
		if(counter % INIT_SIZE == 0) 
		{
			p = realloc(p, INIT_SIZE * ++round);
			if(p == NULL)
			{
				error_handling(NULLPOINTER); 
				return -1;
			}
		}
		c = getchar();
	}
	p[counter] = 0;

	if(strcmp(p, "decodieren") == 0)
	{
			direction = DECODE;
			free(p);
			return 0;
	}
	if(strcmp(p, "codieren") == 0)
	{
			direction = CODE;
			free(p);
			return 0;
	}

	free(p);
	input(in, 1);
	return 0;
}
	
int more_runs() /*Wird aufgerufen, wenn er Benutzer weitere Eingaben machen moechte*/
{	
	char c;
	if(try(system("cls"), 0) != 0)
	{
		try(system("clear"), OPSYSERR);
	}
	printf("\nMoechtest du:\n(1) Die jetzigen Einstellungen beibehalten\n(2) Die Einstellungen aendern?\n");

	while(1)
	{
		c = getchar();
		flush_buff();

		if(c == '1')
		{	
			printf("Eingabe:\n");
			return 0;

		} else if(c == '2')
		{	
			runs = 0;
			content(1);
			return 0;
		}
		switch(direction)
		{
			case CODE: 
				switch(inputtype){
					case DATEI:
						printf("\n-Gebe '1' ein, falls du die \njetzigen Einstellungen (Eingabe: Datei, Codieren) behalten moechten.");
						printf("-\n-Gebe '2' ein, falls du die \nEinstellungen aendern moechten.");
						break;
					case KONSOLE:
						printf("\n-Gebe '1' ein, falls du die \njetzigen Einstellungen (Eingabe: Konsole, Codieren) behalten moechten.");
						printf("-\n-Gebe '2' ein, falls du die \nEinstellungen aendern moechten.");
						break;
				}
				break;
			case DECODE: 
				switch(inputtype){
					case DATEI:
						printf("\n-Gebe '1' ein, falls du die \njetzigen Einstellungen (Eingabe: Datei, Decodieren) behalten moechten.");
						printf("-\n-Gebe '2' ein, falls du die \nEinstellungen aendern moechten.");
						break;		
					case KONSOLE:
						printf("\n-Gebe '1' ein, falls du die \njetzigen Einstellungen (Eingabe: Konsole, Decodieren) behalten moechten.");
						printf("-\n-Gebe '2' ein, falls du die \nEinstellungen aendern moechten.");
						break;
				}
				break;
		}
	}
	return 0;
}

int output_check(char *string) /*Diese Funktion regelt das gewuenschte Ausgabemedium*/
{
	char c;
	printf("\nMoechtest du die Ausgabe ueber:\n(1) Die Konsole\n(2) Eine Datei\n\n");
	c = getchar();
	flush_buff();
	if(c == '1')
	{	
		(direction == CODE) ? code_output(string) : decode_output(string);
	} else if(c == '2')
	{
		file_output(string);
	} else 
	{
		output_check(string);
		return -1;
	}
	return 0;
}

void filecheck() /*Steuert das oeffnen der Eingabe-Dateien*/
{		
		printf("\ndruecke hier in der Konsole die Enter-Taste,\nwenn du fertig bist.\n");
		switch(direction)
		{
			case DECODE:
					if(runs == 0){
						if(try(system("notepad files/readme_d.txt"), 0) != 0){
							try(system("gedit files/readme_d.txt"), OPSYSERR);
						}
					}
					if(try(system("notepad files/decode.txt"), 0) != 0){
							try(system("gedit files/decode.txt"), OPSYSERR);
						}
					break;
			case CODE:
					if(runs == 0){
						if(try(system("notepad files/readme_c.txt"), 0) != 0){
							try(system("gedit files/readme_c.txt"), OPSYSERR);
						}
					}
					if(try(system("notepad files/code.txt"), 0) != 0){
							try(system("gedit files/code.txt"), OPSYSERR);
						}
					break;
		}
		while(getchar() != '\n')
		{
			flush_buff();
		}

}
	
void cmd_check() /*Diese funktion dient als kleines Tutorial, wie man seine Eingaben auf der Konsole macht*/
{	
	if(runs == 0)
	{
		char c;
	
		if(direction == CODE)
		{	
			printf("--------------------");
			printf("\n\nUm nun einen Text in Morse-Code zu codieren\ngebe deinen Wunschtext ueber die Konsole\nganz normal ein.\n");
			printf("Bei der Ausgabe sind die einzelnen Morse-Codes,\npro Zeichen, mit einem Leerzeichen getrennt.\nWoerter sind mit einem 'X' getrennt.\n");
			printf("\nMoechtest du einen Beispieltext + Ausgabe sehen?\nja(y)/Nein(n)");
			c = getchar();
			if(toupper(c) == 'Y' || toupper(c) == 'J')
			{
				printf("\nDie Eingabe: 'Hallo Welt'\nhat folgende Ausgabe:\n .... .- .-.. .-.. ---X.-- . .-.. -\n");
			}
			flush_buff();
			printf("\n-------------------\n");
			printf("\nViel Spass beim Codieren!\n\n");
		} else 
		{	printf("--------------------");
			printf("\n\nUm nun einen Morse-Code zu decodieren, gebe\ndie Zeichen wie folgt ein:\n");
			printf("- Einzelne Buchstaben werden mit einem Leerzeichen\ngetrennt\n");
			printf("- woerter werden mit einem 'X' getrennt ohne Leerzeichen\nsowohl vor als auch hinter dem 'X'. \n");
			printf("\nMoechtest du eine Beispiel-Eingabe + Ausgabe sehen?\nja(y)/nein(n)");
			c = getchar();
			if(toupper(c) == 'Y' || toupper(c) == 'J')
			{
				printf("\n\nDie Eingabe: .... .- .-.. .-.. ---X.-- . .-.. -\n");
				printf("Hat folgende Ausgabe: 'HALLO WELT'");
			}
			flush_buff();
			printf("\n-------------------\n");
			printf("\nViel Spass beim Decodieren!\n\n");
		}
	
		flush_buff();
	}
}

int code_output(char* output) /*Regelt die Ausgabe in der Konsole fuer codierte Zeichen*/
{	
	int i, length;
	length = strlen(output);
	printf("\nSoll die Ausgabe mit Ton erfolgen?\nja(y)/Nein(n)");
		
	if(yes_no() == YES)
	{	
		if(length >= 150)
		{
			printf("\nBist du sicher?\nDie Ausgabe koennte sehr lang ausfallen.\nJa(y)/Nein(n)");
			if(yes_no() == YES)
			{

				printf("Ausgabe:\n");
				for(i = 0; i < length; i++)
				{
				printf("%c", output[i]);
				if(output[i] == '.')
				{	
					Beep(500,80);	/*Beep ist eine funktion aus windows.h die eine Ausgabe mit Ton ermoeglicht*/
					Beep(0, 200);
						
				} 
				if(output[i] == '-')
				{	
					Beep(300, 80);
					Beep(0, 200);
				}
				if(output[i] == 32 || output[i] == 'X')
				{	
					Beep(0, 80);
					Beep(0, 200);
				}
				}
				return 0;
			}
		} 
		if(length < 150)
		{
			printf("Ausgabe:\n");
			for(i = 0; i < length; i++)
			{
			printf("%c", output[i]);
			if(output[i] == '.')
			{	
				Beep(500,80);	/*Beep ist eine funktion aus windows.h die eine Ausgabe mit Ton ermoeglicht*/
				Beep(0, 200);		
			} 
			if(output[i] == '-')
			{	
				Beep(300, 80);
				Beep(0, 200);
			}
			if(output[i] == 32 || output[i] == 'X')
			{	
				Beep(0, 80);
				Beep(0, 200);
			}
			}
			return 0;
		}
	}
	printf("\nAusgabe:\n%s\n", output);
	return 0;
}


int decode_output(char* output)/*Regelt die Ausgabe in der Konsole fuer decodierte Zeichen*/
{

	printf("Ausgabe:\n%s\n", output);

	return 0;
}


int file_output(char *output) /*Regelt die generelle Ausgabe in einer Datei von codierten/decodierten Zeichen*/
{
	FILE *out;
	out = fopen("files/output.txt", "r+");
	if(out == NULL)
	{
		error_handling(NULLPOINTER); 
		return -1;
	}
	fwrite(output, 1, strlen(output), out);
	fclose(out);
	if(try(system("notepad files/output.txt"), 0) != 0)
	{
		try(system("gedit files/output.txt"), OPSYSERR);
	}
	clear_file(out);
	return 0;
}

int yes_no() /*eigentlich unnoetige Hilfsfunktion*/
{	
	char c;
	c = getchar();
	flush_buff();
	if(toupper(c) == 'Y' || toupper(c) == 'J')
	{
		return YES;
	}else if(toupper(c) == 'N') 
	{
		return NO;
	} 
	return -1;
}

void flush_buff() /*Bekannt aus Vorlesung*/
{	
	
	char c;
	while(c != '\n' && c != EOF)
	{
		c = getchar();
	}
	
}

void clear_file(FILE *fp) /*Aehnlich wie flush_buff(), leert den Inhalt der Output-Datei*/
{	
	fp = fopen("files/output.txt", "w");
	
	fclose(fp);
}
