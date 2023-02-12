#ifndef CONTENT_H
#define CONTENT_H


#define DATEI 10
#define KONSOLE 20
#define CODE 30
#define DECODE 40
#define CHECK() printf("check\n");
#define YES 1
#define NO 0


int direction;
int inputtype;

void flush_buff();
void filecheck();
void cmd_check();
int input(int, int);
int content();
int more_runs();
int yes_no();
int code_output(char*);
int file_output(char*);
void clear_file(FILE*);
int output_check(char*);
int decode_output(char*);
#endif