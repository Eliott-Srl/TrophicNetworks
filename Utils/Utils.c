#include "Utils.h"

int u_fscanf(FILE *__stream, const char *__format, ...) {
    if (fgetc(__stream) == '#') {
        fseek(__stream, -1L, SEEK_CUR);
        fgets(NULL, 80, __stream);
    }

    va_list vaList;

    va_start(vaList, __format);

    return vfscanf(__stream, __format, vaList);
}
