#include <mpi.h>
#include <iostream>
#include "Process.h"

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		// ����� �������� �� ��� ������: ������ � ��������.

		auto worldSet = GetWorldRankSet();
		auto evenSet = GetEvenRankSet(worldSet, process);
		auto evenCommunicator = CreateCommunicator(evenSet);
		if (process.IsMaster())
		{
			// 4: ���� ������� �� ������ � ������, �� �������� ������������� ����� MPI_COMM_NULL.
			auto isIncludedInEvenCommunicator = (evenCommunicator == MPI_COMM_NULL); 
			std::cout << "Master is inculuded to evenComm: " << BoolToString(isIncludedInEvenCommunicator) << std::endl;
		}

		auto oddSet = GetOddRankSet(worldSet, evenSet);
		auto oddCommunicator = CreateCommunicator(oddSet);
		if (process.IsMaster())
		{
			std::cout << "Master is inculuded to oddComm: " << BoolToString(oddCommunicator == MPI_COMM_NULL) << std::endl;
		}

		// ���������� ������ ����� ��������.
		auto data = process.IsMaster() ? 1 : 0;
		if (evenCommunicator != MPI_COMM_NULL) 
		{
			MPI_Bcast(&data, 1, MPI_INT, MPI::MasterRank, evenCommunicator); // ����� ������ ������ ��� �������� ���������.
		}
		std::cout << "Process #" << process.GetRank() << " has data = " << data << std::endl;

		// 6: ����������� �������.
		MPI_Group_free(&worldSet); 
		MPI_Group_free(&evenSet);
		MPI_Group_free(&oddSet);
		if (evenCommunicator != MPI_COMM_NULL) MPI_Comm_free(&evenCommunicator);
		if (oddCommunicator != MPI_COMM_NULL) MPI_Comm_free(&oddCommunicator);
	}

private:
	static MPI_Group& GetWorldRankSet()
	{
		MPI_Group worldSet;
		MPI_Comm_group(MPI_COMM_WORLD, &worldSet); // 1: �������� ��������� ������ �� ��������� ������������� ������.
		return worldSet;
	}

	static MPI_Group& GetEvenRankSet(const MPI_Group& worldSet, const MPI::Process& process)
	{
		auto evenGroupSize = process.GetProcessCount() / 2;
		auto evenGroupRanks = GetEvenRanks(evenGroupSize);

		MPI_Group evenSet;
		MPI_Group_incl(     // 2: �������� ����� ������������ �� �������� ������.
			worldSet,       // ������������ ���������.
			evenGroupSize,  // ������� ������ ����.
			evenGroupRanks, // ����� ����� ����.
			&evenSet);      // ���������.

		return evenSet;
	}

	static int* GetEvenRanks(int groupSize)
	{
		auto evenGroupRanks = new int[groupSize];
		for (auto i = 0; i < groupSize; ++i)
		{
			evenGroupRanks[i] = 2 * i;
		}
		return evenGroupRanks;
	}

	static MPI_Comm& CreateCommunicator(const MPI_Group& set)
	{
		MPI_Comm evenComm;
		MPI_Comm_create(MPI_COMM_WORLD, set, &evenComm); // 3: ������ ������������ ��� ��������� ��������� ������ �� ������������ ������.
		return evenComm;
	}

	static const char* BoolToString(bool b)
	{
		return b ? "true" : "false";
	}

	static MPI_Group& GetOddRankSet(const MPI_Group& worldSet, MPI_Group& evenSet)
	{
		MPI_Group oddGroup;
		MPI_Group_difference(worldSet, evenSet, &oddGroup); // 5: ��������� ��������: odd = world \ even.
		return oddGroup;
	}
};

int main()
{
	Program::Main();
	return 0;
}