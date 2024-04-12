#include <stdio.h>
#include <mpi.h>


int main(int argc, char **argv) {

	int rank, size;
	double sum = 0.0, total_sum = 0.0;
	int n = atoi(argv[1]);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	for (int i = rank + 1; i <= n; i += size) {
		sum+= 1.0 / i;
	}

	MPI_Reduce(&sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0){
		printf("sum = %f", total_sum);
	}
	

	MPI_Finalize();

	return 0;
}