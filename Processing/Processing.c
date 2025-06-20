#include "Processing.h"

#include "Processing.h"

bool primaryProductor(Graphe* graphe, int id) {
    if (id < 0 || id >= graphe->ordre) {
        printf("Erreur : id invalide.\n");
        return 0;
    }

    // Parcourir les arcs sortants du sommet `id`
    pArc arc = graphe->pSommet[id]->arc;
    while (arc != NULL) {
        // Si un arc sortant existe c'est un looser
        return 0;
    }

    // Si aucun arc sortant trouvé c'est un predateur
    return 1;
}

bool predateur(Graphe* graphe, int id) {
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

// Ajouter un niveau trophique à la liste s'il n'existe pas déjà
void ajouterNiveau(int* niveaux, int* taille, int niveau) {
    for (int i = 0; i < *taille; i++) {
        if (niveaux[i] == niveau) {
            return; // Niveau déjà présent, on ne l'ajoute pas
        }
    }
    niveaux[*taille] = niveau;
    (*taille)++;
}

// Fonction récursive pour calculer tous les niveaux trophiques possibles
void calculerNiveauTrophique(Graphe* graphe, int id, int** niveaux, int* tailles) {
    // Vérification si déjà calculé
    if (tailles[id] != -1) {
        return;
    }

    // Si c'est un producteur primaire, son niveau est 0
    if (primaryProductor(graphe, id)) {
        niveaux[id][0] = 0;
        tailles[id] = 1; // Taille est 1 car il n'y a qu'un seul niveau
        return;
    }

    // Initialiser la taille à 0 avant de commencer
    tailles[id] = 0;

    // Parcourir tous les sommets pour trouver les prédécesseurs
    for (int i = 0; i < graphe->ordre; i++) {
        pArc arc = graphe->pSommet[i]->arc;

        while (arc != NULL) {
            if (arc->sommet == id) {
                // Calculer récursivement les niveaux trophiques pour le prédécesseur
                calculerNiveauTrophique(graphe, i, niveaux, tailles);

                // Ajouter tous les niveaux trophiques du prédécesseur + 1
                for (int j = 0; j < tailles[i]; j++) {
                    ajouterNiveau(niveaux[id], &tailles[id], niveaux[i][j] + 1);
                }
            }
            arc = arc->arc_suivant;
        }
    }
}

int trophicLevels(Graphe* graphe, int** niveaux, int* tailles, int id) {
    int la = 0;
    if (graphe == NULL || graphe->pSommet == NULL) {
        printf("Erreur : graphe invalide.\n");
        exit(-1);
    }

    if (id < 0 || id >= graphe->ordre) {
        printf("Erreur : id invalide.\n");
        exit(-1);
    }

    // Calculer les niveaux trophiques
    for (int i = 0; i < graphe->ordre; i++) {
        calculerNiveauTrophique(graphe, i, niveaux, tailles);
    }

    // Afficher les niveaux pour l'espèce demandée
    for (int i = 0; i < tailles[id]; i++) {
        la += printf("%d ", niveaux[id][i]);
    }
    la += printf("\n");

    return la;
}

// Supprime une espèce et ses arcs associés
void supprimerEspece(Graphe* graphe, int id) {
    // Vérification de l'id
    if (id < 0 || id >= graphe->ordre) {
        printf("Erreur : id invalide.\n");
        return;
    }

    printf("Suppression de l'espece %d...\n", id);

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
    graphe->pSommet[id]->quantity = -1;

    printf("Espece %d supprime.\n", id);
}

void repercuterSuppression(Graphe* graphe, int id) {
    // Vérification de l'id
    if (id < 0 || id >= graphe->ordre || graphe->pSommet[id]->quantity == -1) {
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

void isolateSpecie(Graphe *graphe) {
    int choix = -1, la = 0;

    printf("Selectionne l'espece a isoler\n");
    for (int i = 0; i < graphe->ordre; i++) {
        printf(" (%d) %s\n", i + 1, graphe->names[i]);
    }

    do {
        scanf("%d", &choix);
    } while(choix <= 0 && choix > graphe->ordre && choix == -1);

    la = printf("+--[%s]-[Quantity: %.02f]", graphe->names[choix - 1], graphe->pSommet[choix - 1]->quantity);

    fillIn(LARGEURPRINT - la, '-', '+');

    if (primaryProductor(graphe, choix - 1)) {
        la = printf("| L'espece est un producteur primaire");

        fillIn(LARGEURPRINT - la, ' ', '|');
    }

    if (predateur(graphe, choix - 1)) {
        la = printf("| L'espece est un predateur principal");

        fillIn(LARGEURPRINT - la, ' ', '|');
    }

    la = printf("| Niveaux trophique: ");

    int* tailles = calloc(graphe->ordre, sizeof(int));
    int** niveaux = malloc(graphe->ordre * sizeof(int*));

    for (int i = 0; i < graphe->ordre; i++) {
        niveaux[i] = calloc(graphe->ordre, sizeof(int)); // Chaque espèce peut avoir jusqu'à "ordre" niveaux
        tailles[i] = -1; // Initialiser la taille à -1 (non calculé)
    }

    la += printf("%d", trophicLevels(graphe, niveaux, tailles, choix - 1));

    fillIn(LARGEURPRINT - la, ' ', '|');

    printSquaredReturn('+', '-');

    printf("Appuie sur n'importe quelle touche pour revenir au menu\n");
    scanf(" ");
}
