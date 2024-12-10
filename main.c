#include "Simulation/Simulation.h"
#include <time.h>
#include <stdlib.h>

Graphe *retrieveNetwork() {
    char filename[50];

    //printf("Vous voulez quelle réseau ?\n>>>");
    //gets(filename);

    return lire_graphe("info_ferme.txt");
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

            action = '0';
        }
        end = clock();

        if (end - begin > CLOCKS_PER_SEC) {
            afficher(graphe, timeRunning);
            simulation(graphe);
            begin = clock();
        }
    }

    return 0;
}
