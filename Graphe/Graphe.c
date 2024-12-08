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
    int taille, ordre, s1, s2, pond;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    u_fscanf(ifs, "%d", &ordre);

    graphe = CreerGraphe(ordre); // créer le graphe d'ordre "ordre"

    u_fscanf(ifs,"%d", &taille);
    graphe->taille = taille;

    // Créer les sommets du graphe
    for (int i = 0; i < ordre; i++) {
        graphe->pSommet[i] = (pSommet) malloc(sizeof(struct Sommet));
        u_fscanf(ifs, "%d", &graphe->pSommet[i]->id);
        graphe->pSommet[i]->arc = NULL;
    }

    // créer les arêtes du graphe
    for (int i = 0; i < taille; ++i) {
        u_fscanf(ifs,"%d%d%f", &s1, &s2, &pond);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, pond);
        graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, pond);
    }

    return graphe;
}

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num) {
    printf(" sommet %d :\n", num);

    pArc arc = sommet[num]->arc;

    while(arc != NULL) {
        printf("%d \t %.02f\n", arc->sommet, arc->poids);
        arc = arc->arc_suivant;
    }
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe) {
    printf("graphe\n");

    printf("ordre = %d\n",graphe->ordre);

    printf("listes d'adjacence :\n");

    for (int i = 0; i < graphe->ordre; i++) {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }
}
