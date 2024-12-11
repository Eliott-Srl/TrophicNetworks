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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
int u_fscanf(FILE *__stream, const char *__format, ...);
#define MAX_CATEGORIES 25
#define MAX_FIELD_LENGTH 500

void emptyScanf();
#endif //TROPHICNETWORKS_UTILS_H
