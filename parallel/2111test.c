#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 5;
    int x[n], y[n];

    // Initialize data on each process
    for (int i = 0; i < n; i++) {
        x[i] = rank * n + i;
        y[i] = 0;
    }



//////////////////////////////////////////////////
    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            y[i] = x[i];
        }
    } else {
        MPI_Send(x, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        int temp[n];
        for (int j = 1; j < size; j++) { //j-номер процесса
            MPI_Recv(&temp, n, MPI_INT, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int i = 0; i < n; i++) {
                y[i] += temp[i];
            }
        }

//////////////////////////////////

        // Print the gathered data
        printf("Gathered data on root process: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", y[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}