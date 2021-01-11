#include <mpi.h>
#include <iostream>
#include "Process.h"

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		// ������ ������� � ������ 0 ��������� ������� (������-�������). 
		// � ��������� ������� �� �������� ������ ������ ��������� � �������� �� �������.
		if (process.GetRank() == 0)
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
		// �������� ������ ���� ��������� ���������.
		for (auto rank = 1; rank < process.GetProcessCount(); ++rank)
		{
			SendIntData(rank);
			SendFloatData(rank);
			SendDoubleData(rank);
		}
		std::cout << "Sending is finished." << std::endl;
	}

	static void SendIntData(int targetRank)
	{
		int intData = 100 + targetRank;
		MPI_Send(                // 1a: ������� ������:
			&intData,            // ��������� �� ������ ������.
			1,                   // ����� ������� ������.
			MPI_INT,             // ��� ������.
			targetRank,          // ���� ������������ ��������.
			0,                   // ��� � ����� ��������� (����� ���������� �����).
			MPI_COMM_WORLD);     // ������ ���������, � ������� ��� ������.
	}

	static void SendFloatData(int targetRank)
	{
		float floatData = 200.02f + targetRank;
		MPI_Send(&floatData, 1, MPI_FLOAT, targetRank, 0, MPI_COMM_WORLD); // 2a.
	}

	static void SendDoubleData(int targetRank)
	{
		double* doubleArrayData = new double[2] { 300.03 + targetRank, 400.04 + targetRank };

		MPI_Send(
			doubleArrayData, // 3a: �������� ��������, ��� ��� �������� ��������� ��� ���������, ��� ��������� &.
			2, MPI_DOUBLE, targetRank, 0, MPI_COMM_WORLD);

		delete[] doubleArrayData;
	}

	static void ReceiveData(const MPI::Process& process)
	{
		ReceiveIntData(process);
		ReceiveFloatData(process);
		ReceiveDoubleData(process);
	}

	static void ReceiveIntData(const MPI::Process& process)
	{
		const int MasterRank = 0;

		// ��������� ������ �� �������� ��������.

		int intData;

		MPI_Recv(                   // 1b: ���� ������:
			&intData, 				// ��������� �� ������ ������.
			1, 						// ����� ������� ������.
			MPI_INT, 				// ��� ������.
			MasterRank, 			// ���� ������������ ��������.
			0, 						// ��� � ����� ��������� (����� ���������� �����).
			MPI_COMM_WORLD, 		// ������ ���������, � ������� ��� ������.
			MPI_STATUS_IGNORE);     // �������������� ���������� (����� ����������� �����), ����� �� � ����������.

		std::cout << "#" << process.GetRank() << " got int: " << intData << std::endl;
	}

	static void ReceiveFloatData(const MPI::Process& process)
	{
		const int MasterRank = 0;

		float floatData;
		MPI_Recv(&floatData, 1, MPI_FLOAT, MasterRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // 2b.
		std::cout << "#" << process.GetRank() << " got float: " << floatData << std::endl;
	}

	static void ReceiveDoubleData(const MPI::Process& process)
	{
		const int MasterRank = 0;

		double* doubleArrayData = new double[2];

		MPI_Recv(
			doubleArrayData, // 3b: ��� � ��� ��������, ������������ ��� ��������� �� ������ �������.
			2, MPI_DOUBLE, MasterRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		std::cout << "#" << process.GetRank() << " got doubles: " << doubleArrayData[0] << ", " << doubleArrayData[1] << std::endl;

		delete[] doubleArrayData;
	}
};

int main()
{
	Program::Main();
	return 0;
}