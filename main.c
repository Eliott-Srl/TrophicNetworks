#include <stdio.h>
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

    char action = '0';
    bool running = 1;
    
    while(running) {
        afficher();

        if (kbhit()) {
            action = getch();
            switch (action) {
                case 'Q':
                    running = 0;
                    break;
                case ' ':
                    break;
            }
            printf("%c\n", action);
            action = '0';
        }
    }

    return 0;
}
