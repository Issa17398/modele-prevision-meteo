#include "boundary.h"

void apply_boundary(Grid *g) {
    // Bords mis à zéro (conditions Dirichlet simples)
    for (int i = 0; i < g->nx; i++) {
        g->data[i] = 0.0; // bas
        g->data[(g->ny-1)*g->nx + i] = 0.0; // haut
    }
    for (int j = 0; j < g->ny; j++) {
        g->data[j*g->nx] = 0.0; // gauche
        g->data[j*g->nx + (g->nx-1)] = 0.0; // droite
    }
}
