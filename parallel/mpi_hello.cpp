#include <iostream>
#include <mpi.h>
int
main(int argc, char **argv)
{
	MPI::Init(argc, argv);
	int np = MPI::COMM_WORLD.Get_size();
	int rank = MPI::COMM_WORLD.Get_rank();
	std::cout << rank << " / " << np << ": hello world!" << std::endl;
	MPI::Finalize();
	return 0;
}