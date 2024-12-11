#include "Utils.h"

// Function that retrieves a character only if the line is not empty
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

void fillIn(int toPrint, char in, char ex) {
    for (int i = 0; i < toPrint - 1; i++) {
        printf("%c", in);
    }

    printf("%c\n", ex);
}

void printSquaredReturn(char ex, char in) {
    int la = printf("%c", ex);

    fillIn(LARGEURPRINT - la, in, ex);
}
