#include "Simulation/Simulation.h"
#include <time.h>
#include <stdlib.h>

#define DEBUG 0

Graphe *retrieveNetwork() {
    if (DEBUG) {
        return lire_graphe("info_ferme");
    } else {
        char filename[50];

        printf("Vous voulez quelle réseau ?\n>>>");
        gets(filename);

        return lire_graphe(filename);
    }
}

void screenshot(Graphe *graphe, int *screen) {
    // Génération du fichier DOT
    char png_cmd[256];
    (*screen)++;
    printf("Conversion du graphe en cours...\n");
    generate_dynamic_dot_file(graphe, "graph_temp.dot");
    sprintf(png_cmd, "\"Graphviz\\bin\\dot.exe\" -Tpng graph_temp.dot > graph_%d.png", *screen);
    system(png_cmd);
    remove("graph_temp.dot");
    printf("Screenshot enregistre sous le nom: graph_%d.png\n", *screen);
}

void base() {
    Graphe *graphe = retrieveNetwork();

    if (!graphe) {
        printf("Erreur : le graphe n'a pas pu être chargé.\n");
        exit(-1);
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
                    exit(0);
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
                    afficher(graphe, timeRunning);
                    break;
            }

            action = '0';
        }
        end = clock();

        if (timeRunning == 1 && (float) (end - begin) > CLOCKS_PER_SEC / playSpeed) {
            simulation(graphe);
            afficher(graphe, timeRunning);
            begin = clock();
        }
    }
}

int main() {
    base();
    return 0;
}
