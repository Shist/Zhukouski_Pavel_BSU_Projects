#include <mpi.h>
#include <iostream>

namespace MPI
{
	// ����������� �����, �������������� �������������� ������������� � �����������.
	class Process
	{
		int _processCount;
		int _rank;

	public:
		Process()
		{
			MPI_Init(nullptr, nullptr); // null � ��� �������� ��������.
			MPI_Comm_size(MPI_COMM_WORLD, &_processCount);
			MPI_Comm_rank(MPI_COMM_WORLD, &_rank);
		}

		~Process()
		{
			MPI_Finalize();
		}

		int GetRank() const
		{
			return _rank;
		}

		int GetProcessCount() const
		{
			return _processCount;
		}
	};
}

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();  // ������������� ������� ��������� �������� ���������������� ����.
		Hi(process);					// 1: ����� � �������.
		MPI_Barrier(MPI_COMM_WORLD);    // 2: ������ � ��������, ���� ��� �������� �� ������ �� ���� �������.
		Bye(process);					// 3: ����� � �������. �������� �������� �� ������� ������.
	}

private:
	static void Hi(const MPI::Process& process)
	{
		std::cout << "Hi from process #" << process.GetRank() << " (total: " << process.GetProcessCount() << ")!" << std::endl;
	}

	static void Bye(const MPI::Process& process)
	{
		std::cout << "Bye from process #" << process.GetRank() << "!" << std::endl;
	}
};

void main()
{
	Program::Main();
}