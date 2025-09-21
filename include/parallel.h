#ifndef PARALLEL_H
#define PARALLEL_H

#include <mpi.h>
#include <omp.h>

/* Initialisation MPI */
void parallel_init(int *argc, char ***argv, int *rank, int *size);

/* Finalisation MPI */
void parallel_finalize();

/* Diffusion des paramètres */
void broadcast_params(int *Nx, int *Ny, double *dx, double *dy, double *dt, int root);

/* Réduction globale */
double parallel_reduce(double local_value);

#endif
