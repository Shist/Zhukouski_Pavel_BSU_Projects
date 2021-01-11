#include <mpi.h>
#include <iostream>
#include "Process.h"

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		if (process.IsMaster())
		{
			SendData(process);
		}
		else
		{
			ReceiveData(process);
		}
	}

private:
	static void SendData(const MPI::Process& process)
	{
		for (auto rank = 1; rank < process.GetProcessCount(); ++rank)
		{
			Send(300 + rank, rank, 2); // 1a: ѕоследний аргумент Ч тэг, условный номер сообщени€.
			Send(200 + rank, rank, 1); // 2a
			Send(100 + rank, rank, 0); // 3a
		}
		std::cout << "Sending is finished." << std::endl;
	}

	static void Send(int data, int destinationRank, int tag)
	{
		MPI_Send(&data, 1, MPI_INT, destinationRank, tag, MPI_COMM_WORLD);
	}

	static void ReceiveData(const MPI::Process& process)
	{
		// “эги позвол€ют принимать сообщени€ в нужном пор€дке.
		std::cout << "#" << process.GetRank() << " got int 0: " << ReceiveInt(MPI::MasterRank, 0) << std::endl; // 3b
		std::cout << "#" << process.GetRank() << " got int 1: " << ReceiveInt(MPI::MasterRank, 1) << std::endl; // 2b
		std::cout << "#" << process.GetRank() << " got int 2: " << ReceiveInt(MPI::MasterRank, 2) << std::endl; // 1b
	}

	static int ReceiveInt(int sourceRank, int tag)
	{
		int data;
		MPI_Recv(&data, 1, MPI_INT, sourceRank, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		return data;
	}
};

int main()
{
	Program::Main();
	return 0;
}