#include "Graphe.h"

pSommet* CreerArete(pSommet* sommet, int s1, int s2, float pond) {
    if (sommet[s1]->arc == NULL) {
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->poids = pond;
        Newarc->arc_suivant = NULL;
        sommet[s1]->arc = Newarc;
        return sommet;
    } else {
        pArc temp = sommet[s1]->arc;
        while (temp->arc_suivant != NULL) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->poids = pond;
        Newarc->arc_suivant = NULL;

        if (temp->sommet > s2) {
            Newarc->arc_suivant = temp->arc_suivant;
            Newarc->sommet = temp->sommet;
            Newarc->poids = temp->poids;
            temp->sommet = s2;
            temp->poids = pond;
            temp->arc_suivant = Newarc;
            return sommet;
        }

        temp->arc_suivant = Newarc;
        return sommet;
    }
}

// créer le graphe
Graphe* CreerGraphe(int ordre) {
    Graphe * Newgraphe = (Graphe*) malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*) malloc(ordre * sizeof(pSommet));
    Newgraphe->ordre = ordre;
    return Newgraphe;
}

/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille, orientation (0 ou 1) et liste des arcs */
Graphe *lire_graphe(char *nomFichier) {
    Graphe *graphe;
    FILE *ifs = fopen(nomFichier, "r");
    int taille, ordre, s1, s2;
    float pond;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    char ligne[1024]; // Pour stocker une ligne du fichier

    // Lire l'ordre du graphe
    do {
        fgets(ligne, sizeof(ligne), ifs);
        nbLigne++;
    } while (ligne[0] == '#' || ligne[0] == '\n');  // Ignorer les lignes de commentaires et vides

    if (ligne[0] == ' ') {
        printf("Erreur dans le fichier à la ligne %d: Espace suivi de rien\n", nbLigne);
        exit(-1);
    }

    if (ligne[0] > '9' || ligne[0] < '0') {
        printf("Erreur dans le fichier à la ligne %d: Pas un ordre correcte\n", nbLigne);
        exit(-1);
    }

    sscanf(ligne, "%d", &ordre);  // Lecture de l'ordre du graphe

    graphe = CreerGraphe(ordre); // Créer le graphe d'ordre "ordre"

    // Lire la taille du graphe
    do {
        fgets(ligne, sizeof(ligne), ifs);
        nbLigne++;
    } while (ligne[0] == '#' || ligne[0] == '\n');  // Ignorer les lignes de commentaires et vides

    if (ligne[0] == ' ') {
        printf("Erreur dans le fichier à la ligne %d: Espace suivi de rien\n", nbLigne);
        exit(-1);
    }

    if (ligne[0] > '9' || ligne[0] < '0') {
        printf("Erreur dans le fichier à la ligne %d: Pas une taille correcte\n", nbLigne);
        exit(-1);
    }

    sscanf(ligne, "%d", &taille);  // Lecture de la taille du graphe

    graphe->taille = taille;

    // Lecture des sommets avec leurs informations
    for (int i = 0; i < ordre; i++) {
        graphe->pSommet[i] = (pSommet) malloc(sizeof(struct Sommet));
        graphe->pSommet[i]->arc = NULL;

        // Lire une ligne complète du fichier pour chaque sommet
        do {
            fgets(ligne, sizeof(ligne), ifs);
            nbLigne++;
        } while (ligne[0] == '#' || ligne[0] == '\n');  // Ignorer les lignes de commentaires et vides

        if (ligne[0] == ' ') {
            printf("Erreur dans le fichier à la ligne %d: Espace suivi de rien\n", nbLigne);
            exit(-1);
        }

        // Découper la ligne en champs séparés par des points-virgules
        char *token = strtok(ligne, ";");

        graphe->names[i] = strdup(token);

        token = strtok(NULL, ";");

        int conv = strtol(token, NULL, 10);

        if (conv == 0) {
            printf("Erreur dans le fichier à la ligne %d: Pas une espece correcte\n", nbLigne);
            exit(-1);
        }

        graphe->pSommet[i]->croissance = 1.0f / (float) conv;

        graphe->pSommet[i]->id = i;
        graphe->pSommet[i]->quantity = 100;
    }

    // Lecture des arcs
    for (int i = 0; i < taille; ++i) {
        do {
            fgets(ligne, sizeof(ligne), ifs);
            nbLigne++;
        } while (ligne[0] == '#' || ligne[0] == '\n');  // Ignorer les lignes de commentaires et vides

        if (ligne[0] == ' ') {
            printf("Erreur dans le fichier à la ligne %d: Espace suivi de rien\n", nbLigne);
            exit(-1);
        }

        if (ligne[0] > '9' || ligne[0] < '0') {
            printf("Erreur dans le fichier à la ligne %d: Pas un arc correcte\n", nbLigne);
            exit(-1);
        }

        // Lire les arcs (utilisation de sscanf pour lire directement les valeurs)
        sscanf(ligne, "%d %d %f", &s1, &s2, &pond);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, pond);
        graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, pond); // Si non orienté
    }

    fclose(ifs);
    return graphe;
}





