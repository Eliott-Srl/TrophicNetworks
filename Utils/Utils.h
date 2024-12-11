#ifndef TROPHICNETWORKS_UTILS_H
#define TROPHICNETWORKS_UTILS_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#ifdef __WIN32__
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define LARGEURPRINT 64

int u_fscanf(FILE *__stream, const char *__format, ...);

void emptyScanf();

void fillIn(int toPrint, char in, char ex);

void printSquaredReturn(char ex, char in);

#endif //TROPHICNETWORKS_UTILS_H
