#include "Process.h"
#include <mpi.h>
#include <cstdlib>

Process::Process(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processNumber);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
}

Process::~Process()
{
	MPI_Finalize();
}

int Process::GetRank() const
{
	return rank;
}

int Process::GetProcessNumber() const
{
	return processNumber;
}

bool Process::IsMaster() const
{
	return rank == MasterRank;
}