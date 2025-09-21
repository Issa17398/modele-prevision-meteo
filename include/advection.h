#ifndef ADVECTION_H
#define ADVECTION_H

#include "grid.h"

/* Calcul du terme d'advection pour une cellule (i,j) */
double advection_term(Grid *g, int i, int j);

#endif
