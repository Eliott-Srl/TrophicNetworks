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

    // Lire l'ordre du graphe
    char ligne[1024]; // Pour stocker une ligne du fichier
    do {
        fgets(ligne, sizeof(ligne), ifs);
    } while (ligne[0] == '#' || ligne[0] == '\n');  // Ignorer les lignes de commentaires et vides
    sscanf(ligne, "%d", &ordre);  // Lecture de l'ordre du graphe

    graphe = CreerGraphe(ordre); // Créer le graphe d'ordre "ordre"

    // Lire la taille du graphe
    do {
        fgets(ligne, sizeof(ligne), ifs);
    } while (ligne[0] == '#' || ligne[0] == '\n');  // Ignorer les lignes de commentaires et vides
    sscanf(ligne, "%d", &taille);  // Lecture de la taille du graphe
    graphe->taille = taille;

    // Lecture des sommets avec leurs informations
    for (int i = 0; i < ordre; i++) {
        graphe->pSommet[i] = (pSommet) malloc(sizeof(struct Sommet));
        graphe->pSommet[i]->arc = NULL;

        // Lire une ligne complète du fichier pour chaque sommet
        do {
            fgets(ligne, sizeof(ligne), ifs);
        } while (ligne[0] == '#' || ligne[0] == '\n');  // Ignorer les lignes de commentaires et vides

        // Supprimer le caractère de nouvelle ligne si présent
        ligne[strcspn(ligne, "\n")] = 0;

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

        // Biomasse : Utilisation de strtof au lieu de atof
        graphe->pSommet[i]->biomasse = (token[0] == 'N' || token[0] == '-') ? 0 : strtof(token, NULL); token = strtok(NULL, ";");

        // Taux de reproduction : strtof
        graphe->pSommet[i]->taux_reproduction = strtof(token, NULL); token = strtok(NULL, ";");

        // Taux de mortalité : strtof
        graphe->pSommet[i]->taux_mortalite = strtof(token, NULL); token = strtok(NULL, ";");

        // Feedback
        graphe->pSommet[i]->feedback = strdup(token); token = strtok(NULL, ";");

        // Variations saisonnières
        graphe->pSommet[i]->variations_saison = strdup(token); token = strtok(NULL, ";");

        // Aliments principaux
        graphe->pSommet[i]->aliments_principaux = strdup(token); token = strtok(NULL, ";");

        // Aliments secondaires
        graphe->pSommet[i]->aliments_secondaires = strdup(token); token = strtok(NULL, ";");

        // Part des aliments : strtof
        graphe->pSommet[i]->part_aliments = (token[0] == 'N' || token[0] == '-') ? 0 : strtof(token, NULL); token = strtok(NULL, ";");

        // Type d'interaction
        graphe->pSommet[i]->type_interaction = strdup(token); token = strtok(NULL, ";");

        // Rôle écologique
        graphe->pSommet[i]->role_ecologique = strdup(token); token = strtok(NULL, ";");

        // Centralité radiale des degrés : strtof
        graphe->pSommet[i]->centralite_radiale = strtof(token, NULL); token = strtok(NULL, ";");

        // Centralité d’intermédiarité : strtof
        graphe->pSommet[i]->centralite_intermed = strtof(token, NULL); token = strtok(NULL, ";");

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
        do {
            fgets(ligne, sizeof(ligne), ifs);
        } while (ligne[0] == '#' || ligne[0] == '\n');  // Ignorer les lignes de commentaires et vides

        // Lire les arcs (utilisation de sscanf pour lire directement les valeurs)
        sscanf(ligne, "%d %d %f", &s1, &s2, &pond);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, pond);
        graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, pond); // Si non orienté
    }

    fclose(ifs);
    return graphe;
}





