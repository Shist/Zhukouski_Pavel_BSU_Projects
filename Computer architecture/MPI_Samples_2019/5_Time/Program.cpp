#include <mpi.h>
#include <iostream>
#include "Process.h"

namespace MPI
{
	class Timer
	{
		double _startTime;

	public:
		Timer() { _startTime = MPI_Wtime(); }
		double Seconds() const { return MPI_Wtime() - _startTime; }
	};
}

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		int dataLength = 10000;
		double* data = new double[dataLength];
		if (process.IsMaster())
		{
			Fill(data, dataLength);
		}

		auto bcastTime = UseBroadcast(process, data, dataLength);
		auto sendRecvTime = UseSendReceive(process, data, dataLength);

		if (process.IsMaster())
		{
			std::cout << "bcast spends " << bcastTime << " seconds." << std::endl;
			std::cout << "send/recv spends " << sendRecvTime << " seconds." << std::endl;
			std::cout << "Time difference: " << (sendRecvTime / bcastTime - 1) * 100 << "%." << std::endl;
			// –азница может быть намного значительнее, если дл€ вычислений используютс€ несколько машин.
		}
		else
		{
			std::cout << "data[2] = " << data[2] << std::endl;
		}

		delete[] data;
	}

private:
	static void Fill(double* data, int length)
	{
		for (auto i = 0; i < length; ++i)
		{
			data[i] = i + 0.25;
		}
	}

	static double UseBroadcast(const MPI::Process& process, double* data, int dataLength)
	{
		MPI_Barrier(MPI_COMM_WORLD);
		auto time = MPI_Wtime();   // 1: ѕолучить количество секунд с момента запуска процесса.

		MPI_Bcast(data, dataLength, MPI_DOUBLE, MPI::MasterRank, MPI_COMM_WORLD);

		MPI_Barrier(MPI_COMM_WORLD);
		return MPI_Wtime() - time; // 2: ¬рем€ широкого вещани€.
	}

	static double UseSendReceive(const MPI::Process& process, double* data, int dataLength)
	{
		MPI_Barrier(MPI_COMM_WORLD);
		auto timer = MPI::Timer();

		if (process.IsMaster())
		{
			for (auto rank = 1; rank < process.GetProcessCount(); ++rank)
			{
				Send(data, dataLength, rank, 0);
			}
		}
		else
		{
			Receive(data, dataLength, MPI::MasterRank, 0);
		}

		MPI_Barrier(MPI_COMM_WORLD);
		return timer.Seconds();
	}

	static void Send(const double* data, int length, int destinationRank, int tag)
	{
		MPI_Send(data, length, MPI_DOUBLE, destinationRank, tag, MPI_COMM_WORLD);
	}

	static void Receive(double* data, int length, int sourceRank, int tag)
	{
		MPI_Recv(data, length, MPI_DOUBLE, sourceRank, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
};

int main()
{
	Program::Main();
	return 0;
}