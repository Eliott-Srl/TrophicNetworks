#include "Simulation.h"

void simulation(Graphe *graphe) {
    for (int i = 0; i < graphe->ordre; i++) {
        pSommet espece = graphe->pSommet[i];

        double portageEnvironnement = 1;

        for (int j = 0; j < graphe->ordre; j++) {
            pSommet influence = graphe->pSommet[j];

            pArc arc = influence->arc;
            while(arc != NULL) {
                if (arc->sommet == espece->id) {
                    portageEnvironnement += arc->poids * influence->quantity;
                }
                arc = arc->arc_suivant;
            }
        }

        double esspece = espece->croissance * espece->quantity * (1 - espece->quantity / portageEnvironnement);
        espece->quantity += esspece;

        for (int j = 0; j < graphe->ordre; j++) {
            pSommet influence = graphe->pSommet[j];

            pArc arc = influence->arc;
            while(arc != NULL) {
                if (arc->sommet == espece->id) {
                    espece->quantity -= arc->poids * influence->quantity;
                }
                arc = arc->arc_suivant;
            }
        }
    }
}
