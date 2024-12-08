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

    // Lecture de l'ordre et de la taille
    u_fscanf(ifs, "%d", &ordre);
    graphe = CreerGraphe(ordre); // Créer le graphe d'ordre "ordre"
    u_fscanf(ifs, "%d", &taille);
    graphe->taille = taille;

    // Lecture des sommets avec leurs informations
    char ligne[1024]; // Pour stocker une ligne du fichier
    for (int i = 0; i < ordre; i++) {
        graphe->pSommet[i] = (pSommet) malloc(sizeof(struct Sommet));
        graphe->pSommet[i]->arc = NULL;

        // Lire une ligne complète du fichier
        fgets(ligne, 1024, ifs);

        // Découper la ligne en champs séparés par des points-virgules
        char *token = strtok(ligne, ";");

        // Associer chaque champ à l'attribut correspondant
        graphe->pSommet[i]->id = i; // Identifiant du sommet
        graphe->pSommet[i]->niveau_trophique = strdup(token); token = strtok(NULL, ";");

        // Prédateurs naturels
        graphe->pSommet[i]->predateurs = strdup(token); token = strtok(NULL, ";");

        // Proies (ensemble séparé par des virgules)
        graphe->pSommet[i]->proies = strdup(token); token = strtok(NULL, ";");

        // Prédécesseurs
        graphe->pSommet[i]->predecesseurs = strdup(token); token = strtok(NULL, ";");

        // Successeurs
        graphe->pSommet[i]->successeurs = strdup(token); token = strtok(NULL, ";");

        // Biomasse
        graphe->pSommet[i]->biomasse = (token[0] == 'N' || token[0] == '-') ? 0 : atof(token); token = strtok(NULL, ";");

        // Taux de reproduction
        graphe->pSommet[i]->taux_reproduction = atof(token); token = strtok(NULL, ";");

        // Taux de mortalité
        graphe->pSommet[i]->taux_mortalite = atof(token); token = strtok(NULL, ";");

        // Feedback
        graphe->pSommet[i]->feedback = strdup(token); token = strtok(NULL, ";");

        // Variations saisonnières
        graphe->pSommet[i]->variations_saison = strdup(token); token = strtok(NULL, ";");

        // Aliments principaux
        graphe->pSommet[i]->aliments_principaux = strdup(token); token = strtok(NULL, ";");

        // Aliments secondaires
        graphe->pSommet[i]->aliments_secondaires = strdup(token); token = strtok(NULL, ";");

        // Part des aliments
        graphe->pSommet[i]->part_aliments = (token[0] == 'N' || token[0] == '-') ? 0 : atof(token); token = strtok(NULL, ";");

        // Type d'interaction
        graphe->pSommet[i]->type_interaction = strdup(token); token = strtok(NULL, ";");

        // Rôle écologique
        graphe->pSommet[i]->role_ecologique = strdup(token); token = strtok(NULL, ";");

        // Centralité radiale des degrés
        graphe->pSommet[i]->centralite_radiale = atof(token); token = strtok(NULL, ";");

        // Centralité d’intermédiarité
        graphe->pSommet[i]->centralite_intermed = atof(token); token = strtok(NULL, ";");

        // Conséquences de la disparition
        graphe->pSommet[i]->consequences_disparition = strdup(token); token = strtok(NULL, ";");

        // Effets de feedback
        graphe->pSommet[i]->effets_feedback = strdup(token); token = strtok(NULL, ";");

        // Contribution au cycle des nutriments
        graphe->pSommet[i]->contribution_nutriments = strdup(token); token = strtok(NULL, ";");

        // Dépendance alimentaire
        graphe->pSommet[i]->dependance_alimentaire = strdup(token); token = strtok(NULL, ";");

        // Risque lié à la spécialisation
        graphe->pSommet[i]->risque_specialisation = strdup(token); token = strtok(NULL, ";");

        // Impact du niveau trophique
        graphe->pSommet[i]->impact_trophique = strdup(token); token = strtok(NULL, ";");

        // Interdépendances supplémentaires
        graphe->pSommet[i]->interdépendances = strdup(token); token = strtok(NULL, ";");

        // Conséquences supplémentaires
        graphe->pSommet[i]->consequences_supp = strdup(token); token = strtok(NULL, ";");
    }

    // Lecture des arcs
    for (int i = 0; i < taille; ++i) {
        u_fscanf(ifs, "%d%d%f", &s1, &s2, &pond);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, pond);
        graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, pond); // Si non orienté
    }

    fclose(ifs);
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

