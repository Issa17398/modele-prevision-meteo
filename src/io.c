#include <stdio.h>
#include "io.h"

void save_output(Grid *g, int step) {
    char filename[128];
    snprintf(filename, sizeof(filename), "output/output_step_%04d.csv", step);
    FILE *f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Impossible d'ouvrir %s\n", filename);
        return;
    }
    for (int j = 0; j < g->ny; j++) {
        for (int i = 0; i < g->nx; i++) {
            fprintf(f, "%.6f", g->data[IDX(g,i,j)]);
            if (i < g->nx-1) fputc(',', f);
        }
        fputc('\n', f);
    }
    fclose(f);
}
