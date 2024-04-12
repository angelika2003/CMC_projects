#include <stdio.h>
#include <mpi.h>


int main(int argc, char **argv) {

	int rank, size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int x = 0, y = 0;
	MPI_Status status;

	if (rank == 0) {
		x = 1;

		MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&y, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
		printf("rank:%d _ получил%d\n", rank, y);
	} else if (rank < size - 1) {
		MPI_Recv(&y, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);

		printf("rank:%d _ получил%d\n", rank, y);

		x = y * 2;

		MPI_Send(&x, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
	} else {//rank == size - 1
		MPI_Recv(&y, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);

		printf("rank:%d _ получил%d\n", rank, y);

		x = y * 2;

		MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}


	MPI_Finalize();

	return 0;
}