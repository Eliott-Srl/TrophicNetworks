#ifndef TROPHICNETWORKS_PROCESSING_H
#define TROPHICNETWORKS_PROCESSING_H

#include "../Graphe/Graphe.h"

#include <conio.h>
#include <math.h>

#define EPSILON 0.0001 // Tolérance pour la convergence
#define MAX_ITER 1000  // Nombre maximum d'itérations

void isolateSpecie(Graphe *graphe);

#endif //TROPHICNETWORKS_PROCESSING_H
