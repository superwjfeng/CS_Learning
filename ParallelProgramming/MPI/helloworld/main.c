#include <mpi.h>
#include <stdio.h>
void main(int argc, char *argv[]) {
    int myrank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Hello world from process %d of %d\n", myrank, size);
    MPI_Finalize();
}
