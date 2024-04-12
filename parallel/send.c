#include <stdio.h>
#include <mpi.h>

int
main(int argc, char **argv)
{
    int np, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    if (np == 2) {
        if (rank == 0) {
            int x = 100500;
            MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        } else {
            int y = 0;
            MPI_Recv(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            printf("y = %d\n", y);
        }
    }
    
    MPI_Finalize();
    return 0;
}