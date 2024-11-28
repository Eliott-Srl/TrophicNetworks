#include <stdio.h>
#include <conio.h>
#include "Processing/Processing.h"

Graphe *retrieveNetwork() {
    char filename[50];

    printf("Vous voulez quelle réseau ?\n>>>");
    gets_s(filename, 50);

    return lire_graphe(filename);
}

void afficher() {
    printf("+--[Networks]-[||]--+");
}


int main() {
    Graphe *graphe = retrieveNetwork();

    char action = ' ';
    
    while(1) {
        afficher();

        if (kbhit()) {
            action = getch();
            printf("%c\n", action);
            action = ' ';
        }
    }

    return 0;
}
