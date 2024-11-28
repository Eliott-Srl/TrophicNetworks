#include "Processing.h"

#include "Processing.h"

bool primaryProductor(Graphe* graphe, int id) {

    if (id < 0 || id >= graphe->ordre) {
        printf("Erreur : id invalide.\n");
        return 0;
    }

    // Parcourir tous les sommets pour vérifier s'il existe des arcs entrants
    for (int i = 0; i < graphe->ordre; i++) {
        pArc arc = graphe->pSommet[i]->arc;
        while (arc != NULL) {
            if (arc->sommet == id) {
                return 0;
            }
            arc = arc->arc_suivant;
        }
    }

    // Si aucun arc entrant trouvé, c'est un producteur primaire
    return 1;
}


int calculerNiveauTrophique(Graphe* graphe, int id, int* niveaux) {
    // Si le niveau a déjà été calculé, on le retourne
    if (niveaux[id] != -1) {
        return niveaux[id];
    }

    // Si l'espèce est un producteur primaire, son niveau est 0 (on vérifie avec al fonction d'avant)
    if (primaryProductor(graphe, id)) {
        niveaux[id] = 0;
        return 0;
    }

    // Sinon, calculer le niveau trophique basé sur le prédécesseur
    int maxNiveau = 0;
    for (int i = 0; i < graphe->ordre; i++) {

        pArc arc = graphe->pSommet[i]->arc;
        while (arc != NULL) {
            if (arc->sommet == id) {
                int niveauPrecedent = calculerNiveauTrophique(graphe, i, niveaux);
                if (niveauPrecedent + 1 > maxNiveau) {
                    maxNiveau = niveauPrecedent + 1;
                }
            }
            arc = arc->arc_suivant;
        }
    }

    // Stocker et retourner le niveau trophique
    niveaux[id] = maxNiveau;
    return maxNiveau;
}

void trophicLevels(Graphe* graphe, int id) {
    // Vérification que le graphe est valide
    if (graphe == NULL || graphe->pSommet == NULL) {
        printf("marche pas.\n");
        return;
    }

    // Tableau pour mémoriser les niveaux trophiques
    int* niveaux = malloc(graphe->ordre * sizeof(int));
    if (niveaux == NULL) {
        printf("pas assez de mémoire.\n");
        return;
    }

    // Initialiser les niveaux non calculés à -1
    for (int i = 0; i < graphe->ordre; i++) {
        niveaux[i] = -1;
    }

    // Si un id spé est donné
    if (id >= 0 && id < graphe->ordre) {
        printf("Calcul des niveaux trophiques pour l'espèce %d :\n", id);
        int niveau = calculerNiveauTrophique(graphe, id, niveaux);
        printf("Espèce %d : Niveau trophique %d\n", id, niveau);
    } else {
        // Si aucun id spécifique n'est donné, on affiche tout
        printf("Niveaux trophiques pour toutes les espèces :\n");
        for (int i = 0; i < graphe->ordre; i++) {
            int niveau = calculerNiveauTrophique(graphe, i, niveaux);
            printf("Espèce %d : Niveau trophique %d\n", i, niveau);
        }
    }

    // Libérer la mémoire
    free(niveaux);
}



// Supprime une espèce et ses arcs associés
void supprimerEspece(Graphe* graphe, int id) {
    // Vérification de l'id
    if (id < 0 || id >= graphe->ordre) {
        printf("Erreur : id invalide.\n");
        return;
    }

    printf("Suppression de l'espèce %d...\n", id);

    // Supprimer tous les arcs sortants de l'espèce
    pArc arc = graphe->pSommet[id]->arc;
    while (arc != NULL) {
        pArc temp = arc;
        arc = arc->arc_suivant;
        free(temp);
    }
    graphe->pSommet[id]->arc = NULL;

    // Supprimer tous les arcs entrants dans l'espèce
    for (int i = 0; i < graphe->ordre; i++) {
        if (i == id) continue; // Pas besoin de vérifier l'espèce supprimée elle-même
        pArc prev = NULL;
        pArc current = graphe->pSommet[i]->arc;
        while (current != NULL) {
            if (current->sommet == id) {
                if (prev == NULL) {
                    graphe->pSommet[i]->arc = current->arc_suivant;
                } else {
                    prev->arc_suivant = current->arc_suivant;
                }
                free(current);
                break;
            }
            prev = current;
            current = current->arc_suivant;
        }
    }

    // Marquer l'espèce comme supprimée (par exemple, en mettant sa quantité à -1)
    graphe->pSommet[id]->quantité = -1;

    printf("Espèce %d supprimée.\n", id);
}




void repercuterSuppression(Graphe* graphe, int id) {
    // Vérification de l'id
    if (id < 0 || id >= graphe->ordre || graphe->pSommet[id]->quantité == -1) {
        printf("Erreur : espèce invalide ou déjà supprimée.\n");
        return;
    }

    printf("Répercussion de la suppression de l'espèce %d...\n", id);

    // Parcourir tous les sommets pour voir qui dépend de l'espèce supprimée
    for (int i = 0; i < graphe->ordre; i++) {
        if (i == id) continue; // Ignorer l'espèce supprimée

        // Vérifier si l'espèce actuelle dépend de l'espèce supprimée
        pArc prev = NULL;
        pArc current = graphe->pSommet[i]->arc;
        while (current != NULL) {
            if (current->sommet == id) {
                // Réduire la quantité ou appliquer une règle d'impact (faut rajouter le systeme d'eliott)
               // graphe->pSommet[i]->quantité *= 0.5; // Exemple : réduire la quantité de moitié
               // graphe->pSommet[i]->croissance *= 0.8; // Exemple : réduire la croissance de 20%

                // Supprimer l'arc (relation de dépendance)
                if (prev == NULL) {
                    graphe->pSommet[i]->arc = current->arc_suivant;
                } else {
                    prev->arc_suivant = current->arc_suivant;
                }
                free(current);
                break;
            }
            prev = current;
            current = current->arc_suivant;
        }
    }
}




// Afficher le graphe maj
void afficherGraphe(Graphe* graphe) {
    printf("Graphe actuel :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        if (graphe->pSommet[i]->quantité == -1) {
            printf("Espèce %d : SUPPRIMÉE\n", i);
            continue;
        }

        printf("Espèce %d (Quantité : %.2f, Croissance : %.2f) : ",
               graphe->pSommet[i]->id,
               graphe->pSommet[i]->quantité,
               graphe->pSommet[i]->croissance);

        pArc arc = graphe->pSommet[i]->arc;
        while (arc != NULL) {
            printf(" -> %d (Poids : %.2f)", arc->sommet, arc->poids);
            arc = arc->arc_suivant;
        }
        printf("\n");
    }
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
