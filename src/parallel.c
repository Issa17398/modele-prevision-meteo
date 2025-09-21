#include "parallel.h"
#include <stdio.h>

void parallel_init(int *argc, char ***argv, int *rank, int *size) {
    MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    MPI_Comm_size(MPI_COMM_WORLD, size);
    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("[MPI Rank %d] OpenMP threads = %d\n", *rank, omp_get_num_threads());
        }
    }
}

void parallel_finalize() {
    MPI_Finalize();
}

void broadcast_params(int *Nx, int *Ny, double *dx, double *dy, double *dt, int root) {
    MPI_Bcast(Nx, 1, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Bcast(Ny, 1, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Bcast(dx, 1, MPI_DOUBLE, root, MPI_COMM_WORLD);
    MPI_Bcast(dy, 1, MPI_DOUBLE, root, MPI_COMM_WORLD);
    MPI_Bcast(dt, 1, MPI_DOUBLE, root, MPI_COMM_WORLD);
}

double parallel_reduce(double local_value) {
    double global_value;
    MPI_Allreduce(&local_value, &global_value, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    return global_value;
}
