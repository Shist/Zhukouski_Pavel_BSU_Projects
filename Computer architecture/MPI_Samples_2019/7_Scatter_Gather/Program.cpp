#include <mpi.h>
#include <iostream>
#include "Process.h"

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		double* data = nullptr;
		auto sliceSize = 20;
		auto dataLength = process.GetProcessCount() * sliceSize;

		if (process.IsMaster())
		{
			data = new double[dataLength];
			Fill(data, dataLength);
		}

		auto slice = new double[sliceSize];
		Scatter(data, slice, sliceSize); // 1. ��������� �� ������(!) �����.

		std::cout << "Process #" << process.GetRank() << " has buffer[" << sliceSize - 1 << "] = " << slice[sliceSize - 1] << std::endl;

		ChangeData(slice, sliceSize); // 2. �������� �����.
		Gather(data, slice, sliceSize); // 3. �������� �� ������ ������.

		if (process.IsMaster())
		{
			std::cout << "data[" << dataLength - 1 << "] = " << data[dataLength - 1] << std::endl;
			delete[] data;
		}

		data = new double[dataLength];
		MPI_Allgather(slice, sliceSize, MPI_DOUBLE, data, sliceSize, MPI_DOUBLE, MPI_COMM_WORLD); // 4: Gather + Broadcast.
		delete[] slice;
		std::cout << "Process #" << process.GetRank() << " has data[" << dataLength - 1 << "] = " << data[dataLength - 1] << std::endl;
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

	static void Scatter(double* data, double* slice, int sliceSize)
	{
		MPI_Scatter(		   // 1: ��������� ������ �� ������ ����� � ���������� ������� �������� ���� �����:
			data, 			   // �������� ������ (��� ������-��������), ��� ��������� ��������� �� ������������.
			sliceSize, 		   // ������ ����� (��� ������-��������), ��� ��������� ��������� �� ������������.
			MPI_DOUBLE, 	   // ��� ������ (��� ������-��������), ��� ��������� ��������� �� ������������.
			slice, 		       // ������, ���� ����� ������������ �����.
			sliceSize, 		   // ������ �����.
			MPI_DOUBLE, 	   // ��� ������.
			MPI::MasterRank,   // ���� ���������� ��������.
			MPI_COMM_WORLD);   // ������� ������.
	}

	static void ChangeData(double* data, int length)
	{
		for (auto i = 0; i < length; ++i)
		{
			data[i] += 1000;
		}
	}

	static void Gather(double* data, double* slice, int sliceSize)
	{
		MPI_Gather(            // 3. �������� ����� � ������� ��������:
			slice, 		       // �����.
			sliceSize, 		   // ������ �����.
			MPI_DOUBLE, 	   // ��� ������.
			data, 			   // ������, � ������� ����� ����������� ����� (��� ������-��������), ��� ��������� ��������� �� ������������.
			sliceSize, 		   // ������ ����� (��� ������-��������), ��� ��������� ��������� �� ������������.
			MPI_DOUBLE, 	   // ��� ������ (��� ������-��������), ��� ��������� ��������� �� ������������.
			MPI::MasterRank,   // ���� ����������� ��������.
			MPI_COMM_WORLD);   // ������� ������.
	}
};

int main()
{
	Program::Main();
	return 0;
}