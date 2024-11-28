#include "Processing.h"

bool primaryProductor(Graphe *graphe, int id) {

    // Code here

    return 0;
}

void trophicLevels(Graphe* graphe, int id) {

    // No return just prints

}

void isolateSpecies(Graphe *graphe, int id) {
    char action = ' ';

    while(action != 'q') {
        action = ' ';

        printf("+--[Isolation: %s]-[Q: Quit]--+");

        // Actions here

        printf("+-------------------+");

        if (kbhit()) {
            action = getch();
        }
    }
}
