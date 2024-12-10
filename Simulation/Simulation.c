#include "Simulation.h"

void simulation(Graphe *graphe) {
    for (int i = 0; i < graphe->ordre; i++) {
        pSommet espece = graphe->pSommet[i];

        double portageEnvironnement = 0;

        for (int j = 0; j < graphe->ordre; j++) {
            pSommet influence = graphe->pSommet[j];

            pArc arc = influence->arc;
            while(arc != NULL) {
                if (arc->sommet == espece->id) {
                    portageEnvironnement += arc->poids * influence->quantity;
                    espece->quantity -= arc->poids * influence->quantity;
                }
                arc = arc->arc_suivant;
            }
        }

        espece->quantity += espece->croissance * espece->quantity * (1 - espece->quantity / portageEnvironnement);
    }
}
