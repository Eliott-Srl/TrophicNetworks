#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../Utils/Utils.h"
#include <string.h>

#define bool int

/* Structure d'un arc*/
struct Arc {
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    double poids; // Pondération
    struct Arc *arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc *pArc;

/* Structure d'un sommet*/
struct Sommet {
    struct Arc *arc;
    double quantity;
    double croissance;
    int Niv;
    // int portageEnvironnement;
    int id;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet *pSommet;

/* Alias d'un Graphe */
typedef struct Graphe {
    int taille;
    int ordre;
    char **names; // Tableau des noms des sommets, l'index du nom correspond à l'id du sommet
    pSommet *pSommet;
} Graphe;

// créer le graphe
Graphe *CreerGraphe(int ordre);

/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe *lire_graphe(char *nomFichier);

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet *CreerArete(pSommet *sommet, int s1, int s2, float pond);

// Récupére
void afficher(Graphe *graphe, bool timeRunning);
void generate_dynamic_dot_file(Graphe *graphe, const char *output_file);

#endif // GRAPHE_H_INCLUDED
