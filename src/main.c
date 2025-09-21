#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "advection.h"
#include "diffusion.h"
#include "boundary.h"
#include "io.h"
#include "parallel.h"

int main(int argc, char **argv) {
    int rank, size;
    int Nx = 100, Ny = 100;
    double dx = 0.1, dy = 0.1, dt = 0.01;
    int steps = 100;

    // Initialisation MPI + OpenMP
    parallel_init(&argc, &argv, &rank, &size);

    // Diffusion des paramètres
    broadcast_params(&Nx, &Ny, &dx, &dy, &dt, 0);

    // Initialisation de la grille
    Grid g;
    init_grid(&g, Nx, Ny, dx, dy);

    // Ajout des conditions initiales (sinon tout reste à zéro !)
    set_initial_conditions(&g);

    if (rank == 0) {
        printf("Simulation %dx%d, %d pas de temps\n", Nx, Ny, steps);
    }

    /// Boucle temporelle
    for (int t = 0; t < steps; t++) {
    // Advection
    for (int i = 0; i < g.nx; i++) {
        for (int j = 0; j < g.ny; j++) {
            g.new_data[IDX(&g,i,j)] = advection_term(&g, i, j);
        }
    }

    // Diffusion
    double kappa = 0.1;
    for (int i = 0; i < g.nx; i++) {
        for (int j = 0; j < g.ny; j++) {
            g.new_data[IDX(&g,i,j)] += diffusion_term(&g, i, j, kappa);
        }
    }

    // Copier new_data → data
    for (int i = 0; i < g.nx * g.ny; i++) {
        g.data[i] = g.new_data[i];
    }

    // Conditions aux limites
    apply_boundary(&g);

    // Sauvegarde tous les 10 pas de temps
    if (rank == 0 && (t % 10 == 0)) {
        save_output(&g, t);
    }
    }


    // Libération mémoire
    free_grid(&g);
    parallel_finalize();

    return 0;
}
