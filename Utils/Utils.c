#include "Utils.h"

int u_fscanf(FILE *__stream, const char *__format, ...) {
    if (fgetc(__stream) == '#') {
        fseek(__stream, -1L, SEEK_CUR);
        fgets(NULL, 80, __stream);
    }

    char current_char = (char) fgetc(__stream);
    while (current_char == ' ' || current_char == '\n') {
        current_char = (char) fgetc(__stream);
    }

    fseek(__stream, -1L, SEEK_CUR);

    va_list vaList;

    va_start(vaList, __format);

    return vfscanf(__stream, __format, vaList);
}

// Function to empty the scanf buffer
void emptyScanf() {
    int c;
    while((c = getchar()) != EOF && c != '\n');
}