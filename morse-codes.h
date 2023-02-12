#ifndef MORSE_CODES_H
#define MORSE_CODES_H

#define ALPHABET_SIZE 26
#define NUMBERS_SIZE 10
#define PUNCT_SIZE 15

static char *alphabet[26][2] = /*Leider mussten die Arrays in einer seperaten Header-Datei inizialisiert werden, sonst gibt die uebersetzung mit den Zusatzschaltern einen Fehler bzw. ein  Warnung: Wunused-variable*/
{
        {"A", ".-"}, {"B", "-..."}, {"C", "-.-."}, {"D", "-.."}, {"E", "."}, {"F", "..-."}, {"G", "--."},
        {"H", "...."}, {"I", ".."}, {"J", ".---"}, {"K", "-.-"}, {"L", ".-.."}, {"M", "--"}, {"N", "-."},
        {"O", "---"}, {"P", ".--."}, {"Q", "--.-"}, {"R", ".-."}, {"S", "..."}, {"T", "-"}, {"U", "..-"},
        {"V", "...-"}, {"W", ".--"}, {"X", "-..-"}, {"Y", "-.--"}, {"Z", "--.."}
};

static char *numbers[10][2] = 
{  
        {"0", "-----"}, {"1", ".----"}, {"2", "..---"}, {"3", "...--"}, {"4", "....-"}, 
        {"5", "....."}, {"6", "-...."}, {"7", "--..."}, {"8", "---.."}, {"9", "----."}
};
static char *punct[16][2] = 
{
        {".", ".-.-.-"}, {",", "--..--"}, {":", "---..."}, {";", "-.-.-."}, {"?", "..--.."}, {"!", "-.-.--"},
        {"-", "-....-"}, {"_", "..--.-"}, {"(", "-.--."}, {")", "-.--.-"}, {"'", ".----."}, {"=", "-...-"},
        {"+", ".-.-."}, {"/", "-..-."}, {"@", ".--.-."}
};

#endif