#include <stdio.h>
#include "Simulation/Simulation.h"
#include <time.h>

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
    float playSpeed = 0.0f;
    float lastSpeed = 1.0f;
    bool timeRunning = 0;

    clock_t begin = clock();
    clock_t end = clock();
    
    while(running) {
        afficher();

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
                        end = clock();
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

            if (end - begin > (((long) 1 / (long) 60)) / (long) playSpeed) {
                simulation(graphe, playSpeed);
                begin = clock();
            }

            printf("%c\n", action);

            action = '0';
        }
    }

    return 0;
}
