#include <mpi.h>
#include <iostream>

class Program
{
	static int _processCount;
	static int _rank;

public: 
	static void Main(int argc, char* argv[])
	{
		MPI_Init(&argc, &argv);                        // 1: Инициализация окружения MPI и передача аргументов командной строки.
													   // Эта функция должна быть вызвана до всех других функций MPI.
													   // Допустимо передавать null, если аргументы не нужны.

		MPI_Comm_size(MPI_COMM_WORLD, &_processCount); // 2: Получение числа процессов.
		MPI_Comm_rank(MPI_COMM_WORLD, &_rank);		   // 3: Получение «номера» процесса (отсчёт от 0), в MPI он называется «ранг».
													   // MPI_COMM_WORLD — это группа всех процессов. Подробнее работа с группами разбирается далее.

		Hi();										   // 4: Вывод в консоль.
		Bye();										   // 5: Вывод в консоль. Обратите внимание на порядок вывода.

		MPI_Finalize();								   // 6: Освобождение ресурсов MPI. Эта функция должна вызываться после всех других функций MPI.
	}

private:
	static void Hi()
	{
		std::cout << "Hi from process #" << _rank << " (total: " << _processCount << ")!" << std::endl;
	}

	static void Bye()
	{
		std::cout << "Bye from process #" << _rank << "!" << std::endl;
	}
};

int Program::_processCount = 0;
int Program::_rank = 0;

int main(int argc, char* argv[])
{
	Program::Main(argc, argv);
	return 0;
}