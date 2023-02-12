#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_INPUT -1
#define NULLPOINTER -2
#define SYSEX -3
#define FILEERR -4
#define OUTPUTERR -5
#define OPSYSERR -6
#define PROGRAMERR -7

void error_handling(int);
int try(int, int);
#endif