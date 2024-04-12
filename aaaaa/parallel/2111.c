#include <stdio.h>
#include <mpi.h>


void
my_reduce_sum_int(
    int *x, /* входной массив чисел */
    int *y, /* результат (выходной массив) (только для root) */
    int n, /* длина массива в числах типа int */
    int root, /* номер процесса-корня редукции */
    MPI_Comm comm /* коммуникатор */
)
{
	int rank, size;
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	if (rank == root) {
		for (int i = 0; i < n; i++) {
			y[i] = x[i];
		}
	} else {
		MPI_Send(x, n, MPI_INT, root, 0, comm);
	}


	if (rank == root) {
		int temp[n];
		for (int j = 0; j < size; j++) { //j-номер процесса
			if (j != root) {
				MPI_Recv(&temp, n, MPI_INT, j, 0, comm, MPI_STATUS_IGNORE);
				for (int i = 0; i < n; i++) {
					y[i] += temp[i];
				}
			}
		}

	}
}



int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int n = 5;
	int x[n], y[n];

	for (int i = 0; i < n; i++) {
		x[i] = 1;
		y[i] = 0;
	}

	my_reduce_sum_int(x, y, n, 1, MPI_COMM_WORLD);

	if (rank == 1) {
		for (int i = 0; i < n; i++) {
			printf("%d ", y[i]);
		}
		printf("\n");
	}

	MPI_Finalize();
	return 0;
}

