#include <mpi.h>
#include <iostream>

namespace MPI
{
	// Простенький класс, поддерживающий автоматическую инициализацию и финализацию.
	class Process
	{
		int _processCount;
		int _rank;

	public:
		Process()
		{
			MPI_Init(nullptr, nullptr); // null — это вадидный аргумент.
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
		auto process = MPI::Process();  // Использование классов позволяет избежать вспомогательного кода.
		Hi(process);					// 1: Вывод в консоль.
		MPI_Barrier(MPI_COMM_WORLD);    // 2: Барьер — ожидание, пока все процессы не придут до этой строчки.
		Bye(process);					// 3: Вывод в консоль. Обратите внимание на порядок вывода.
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