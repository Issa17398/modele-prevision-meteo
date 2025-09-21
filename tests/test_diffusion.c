#include <stdio.h>
#include "grid.h"
#include "diffusion.h"

int main() {
    Grid g;
    init_grid(&g, 10, 10, 0.1, 0.1);

    // Mettre une valeur au centre
    g.data[IDX(&g, 5, 5)] = 1.0;

    // Calcul du terme de diffusion avec kappa = 0.1
    double val = diffusion_term(&g, 5, 5, 0.1);
    printf("Diffusion at (5,5) = %f\n", val);

    free_grid(&g);
    return 0;
}
