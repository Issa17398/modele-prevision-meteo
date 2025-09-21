#include "diffusion.h"

double diffusion_term(Grid *g, int i, int j, double kappa) {
    double dx = g->dx;
    double T = g->data[IDX(g,i,j)];
    double lap = 0.0;

    lap += g->data[IDX(g,i+1,j)];
    lap += g->data[IDX(g,i-1,j)];
    lap += g->data[IDX(g,i,j+1)];
    lap += g->data[IDX(g,i,j-1)];
    lap -= 4.0 * T;

    /* Laplacien approximé = lap / dx^2 ; dT/dt contribution = kappa * Laplacian */
    return kappa * (lap / (dx * dx));
}
