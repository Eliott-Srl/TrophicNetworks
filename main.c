#include "Simulation/Simulation.h"
#include <time.h>
#include <stdlib.h>

Graphe *retrieveNetwork() {
    char filename[50];

    //printf("Vous voulez quelle réseau ?\n>>>");
    //gets(filename);

    return lire_graphe("info_ferme.txt");
}

void afficher(Graphe *graphe, bool timeRunning) {
    //system(CLEAR);

    int largeur = printf("+--[Networks]-[ J: ↘ | K: %s | L: ↗ ]-[S: Export image]--+\n", timeRunning ? "⏸" : "▶") - 1;
    int la = 0;

    for (int i = 0; i < graphe->ordre; i++) {
        la = printf("| %s (%d): ", graphe->names[i], (int) graphe->pSommet[i]->quantity);
        for (int j = 0; j < largeur - la - 1; j++) {
            printf(" ");
        }
        printf("|\n");

        pArc arc = graphe->pSommet[i]->arc;

        while(arc != NULL) {
            la = printf("|  - %c (%f)", graphe->names[arc->sommet], arc->poids);

            for (int j = 0; j < largeur - la - 1; j++) {
                printf(" ");
            }
            printf("|\n");

            arc = arc->arc_suivant;
        }

        la = printf("|");
        for (int j = 0; j < la - 2; j++) {
            printf(" ");
        }
        printf("|\n");
    }
}

int main() {
    Graphe *graphe = retrieveNetwork();

    char action = '0';
    bool running = 1;
    float playSpeed = 0.0f;
    float lastSpeed = 1.0f;
    bool timeRunning = 0;

    clock_t begin = clock();
    clock_t end = clock();
    
    while(running) {
        if (kbhit()) {
            action = getch();
            switch (action) {
                case 'q':
                    running = 0;
                    break;
                case ' ':
                case 'k':
                    if (playSpeed == 0) {
                        playSpeed = lastSpeed;
                        lastSpeed = 0.0f;
                        timeRunning = 1;
                        begin = clock();
                    } else {
                        lastSpeed = playSpeed;
                        playSpeed = 0.0f;
                        timeRunning = 0;
                    }
                    break;
                case 'j':
                    if (playSpeed != 0) {
                        playSpeed -= 0.25f;
                    }
                    break;
                case 'l':
                    if (playSpeed != 0) {
                        playSpeed += 0.25f;
                    }
                    break;
            }
            end = clock();

            if (end - begin > (long) 1 / (long) 60 / (long) playSpeed) {
                simulation(graphe);
                afficher(graphe, timeRunning);
                begin = clock();
            }

            printf("%c\n", action);

            action = '0';
        }
    }

    return 0;
}
