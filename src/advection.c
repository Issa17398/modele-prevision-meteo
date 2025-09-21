#include "advection.h"

/* vitesses constantes (tu peux mettre dans config) */
static const double U = 1.0;
static const double V = 0.5;

double advection_term(Grid *g, int i, int j) {
    /* upwind approximations */
    double dx = g->dx;
    double dy = g->dy;
    double T = g->data[IDX(g,i,j)];
    double dudx, dudy;

    if (U > 0)
        dudx = (T - g->data[IDX(g,i-1,j)]) / dx;
    else
        dudx = (g->data[IDX(g,i+1,j)] - T) / dx;

    if (V > 0)
        dudy = (T - g->data[IDX(g,i,j-1)]) / dy;
    else
        dudy = (g->data[IDX(g,i,j+1)] - T) / dy;

    /* contribution dT/dt due to advection = - (U dT/dx + V dT/dy) */
    return - (U * dudx + V * dudy);
}
