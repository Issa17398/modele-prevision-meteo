#ifndef DIFFUSION_H
#define DIFFUSION_H

#include "grid.h"

/* Calcul du terme de diffusion pour une cellule (i,j) */
double diffusion_term(Grid *g, int i, int j, double kappa);

#endif
