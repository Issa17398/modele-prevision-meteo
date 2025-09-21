#ifndef IO_H
#define IO_H

#include "grid.h"

/* Écrit un fichier CSV sous la forme : output/output_step_XXXX.csv */
void save_output(Grid *g, int step);

#endif /* IO_H */
