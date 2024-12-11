#include "Simulation/Simulation.h"
#include <time.h>
#include <stdlib.h>

Graphe *retrieveNetwork() {
    char filename[50];

    //printf("Vous voulez quelle réseau ?\n>>>");
    //gets(filename);

    return lire_graphe("info_ferme");
}

void screenshot(Graphe *graphe, int *screen) {
    // Génération du fichier DOT
    char dot_file[256];
    (*screen)++;
    sprintf(dot_file, "graph_step_%d.dot", *screen);
    generate_dynamic_dot_file(graphe, dot_file);
}

int main() {
    Graphe *graphe = retrieveNetwork();

    if (!graphe) {
        printf("Erreur : le graphe n'a pas pu être chargé.\n");
        return 1;
    }

    char action = '0';
    bool running = 1;
    float playSpeed = 0.0f;
    float lastSpeed = 1.0f;
    bool timeRunning = 0;
    int screen = 0;

    clock_t begin = clock();
    clock_t end = clock();

    afficher(graphe, timeRunning);

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
                case 's':
                    screenshot(graphe, &screen);
                    break;
                case 'g':
                    timeRunning = 0;
                    isolateSpecie(graphe);
            }

            action = '0';
            emptyScanf();
        }
        end = clock();

        if (timeRunning == 1 && end - begin > CLOCKS_PER_SEC) {
            simulation(graphe);
            afficher(graphe, timeRunning);
            begin = clock();
        }
    }


    return 0;
}
