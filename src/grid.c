#include "grid.h"
#include <math.h>

void init_grid(Grid *g, int nx, int ny, double dx, double dy) {
    g->nx = nx;
    g->ny = ny;
    g->dx = dx;
    g->dy = dy;
    g->data = (double*) malloc(nx * ny * sizeof(double));
    g->new_data = (double*) malloc(nx * ny * sizeof(double));
    if (!g->data || !g->new_data) {
        fprintf(stderr, "Erreur allocation mémoire grille\n");
        free(g->data);
        free(g->new_data);
        exit(1);
    }
    /* initialisation à zéro */
    for (int i = 0; i < nx * ny; i++) {
        g->data[i] = 0.0;
        g->new_data[i] = 0.0;
    }
}

// Fonction pour initialiser la grille avec des valeurs non nulles
void set_initial_conditions(Grid *g) {
    for (int i = 0; i < g->nx; i++) {
        for (int j = 0; j < g->ny; j++) {
            g->data[IDX(g,i,j)] = sin(i * M_PI / g->nx) * sin(j * M_PI / g->ny);
        }
    }
}


void free_grid(Grid *g) {
    if (g->data) free(g->data);
    if (g->new_data) free(g->new_data);
}
