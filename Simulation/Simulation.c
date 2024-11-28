#include "Simulation.h"

void simulation(Graphe *graphe, const float playSpeed) {
    for (int i = 0; i < graphe->ordre; i++) {
        pSommet espece = graphe->pSommet[i];

        float portageEnvironnement = 0;
        espece->quantity = espece->quantity;

        for (int j = 0; j < graphe->ordre; j++) {
            pSommet influence = graphe->pSommet[j];

            pArc arc = influence->arc;
            while(arc != NULL) {
                if (arc->sommet == espece->id) {
                    portageEnvironnement += arc->poids * (float) influence->quantity;
                    espece->quantity -= arc->poids * (float) influence->quantity;
                }
                arc = arc->arc_suivant;
            }
        }

        espece->quantity += espece->croissance * espece->quantity * (1 - espece->quantity / portageEnvironnement);
    }
}
