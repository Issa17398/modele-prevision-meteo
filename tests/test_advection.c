#include <stdio.h>
#include "grid.h"
#include "advection.h"

int main() {
    Grid g;
    init_grid(&g, 10, 10, 0.1, 0.1);

    // Mettre une valeur dans le centre
    g.data[IDX(&g, 5, 5)] = 1.0;

    // Calcul du terme d'advection
    double val = advection_term(&g, 5, 5);
    printf("Advection at (5,5) = %f\n", val);

    free_grid(&g);
    return 0;
}
