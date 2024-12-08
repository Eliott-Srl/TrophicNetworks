#ifndef TROPHICNETWORKS_UTILS_H
#define TROPHICNETWORKS_UTILS_H

#include <stdio.h>
#include <stdarg.h>

#ifdef __WIN32__
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int u_fscanf(FILE *__stream, const char *__format, ...);

#endif //TROPHICNETWORKS_UTILS_H
