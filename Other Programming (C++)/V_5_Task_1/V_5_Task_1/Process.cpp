#include "Process.h"
#include <mpi.h>

namespace MPI
{
	Process::Process()
	{
		MPI_Init(nullptr, nullptr);
		MPI_Comm_size(MPI_COMM_WORLD, &_processCount);
		MPI_Comm_rank(MPI_COMM_WORLD, &_rank);
	}

	Process::~Process()
	{
		MPI_Finalize();
	}

	int Process::GetProcessCount() const
	{
		return _processCount;
	}

	int Process::GetRank() const
	{
		return _rank;
	}

	bool Process::IsMaster() const
	{
		return GetRank() == MasterRank;
	}
}