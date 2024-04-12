#include <stdio.h>
#include <mpi.h>
int
main(int argc, char **argv)
{
	int rank, np;
	printf("hey\n");
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("%d/%d: hello world!\n", rank, np);
	MPI_Finalize();
	return 0;
}