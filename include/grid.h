#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int nx;
    int ny;
    double dx;
    double dy;
    double *data;      // taille nx * ny (ligne-major)
    double *new_data;  // buffer pour la mise à jour
} Grid;

/* indexation : IDX(g,i,j) -> index dans le tableau 1D */
#define IDX(g,i,j) ( (j) * (g)->nx + (i) )

void init_grid(Grid *g, int nx, int ny, double dx, double dy);
void set_initial_conditions(Grid *g);
void free_grid(Grid *g);

#endif /* GRID_H */
