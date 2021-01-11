#include <mpi.h>
#include <iostream>
#include "Process.h"

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		int dataLength = 3;
		double* data = new double[dataLength];
		Fill(data, dataLength, process.GetRank());

		double* sums = process.IsMaster() ? new double[dataLength] : nullptr;

		MPI_Reduce(			  // Применяет выбранную операцию к i-ым элементам входных массивов 
			                  // и записывает результат в i-ый элемент выходного массива мастер-процесса:
			data,             // Входной массив процесса.
			sums,             // Выходной массив (имеет значение только для мастер-процесса).
			dataLength,       // Длина массивов.
			MPI_DOUBLE,       // Тип данных.
			MPI_SUM,          // Операция.
			MPI::MasterRank,  // Ранг мастер-процесса.
			MPI_COMM_WORLD);  // Рабочая группа.

		if (process.IsMaster())
		{
			Print(sums, dataLength);
		}

		delete sums;
	}

private:
	static void Fill(double* data, int length, int rank)
	{
		for (auto i = 0; i < length; ++i)
		{
			data[i] = 10 * rank + i;
		}
	}

	static void ChangeData(double* data, int length)
	{
		for (auto i = 0; i < length; ++i)
		{
			data[i] += 1000;
		}
	}

	static void Print(double* sums, int length)
	{
		for (auto i = 0; i < length; ++i)
		{
			std::cout << "sums[" << i << "] = " << sums[i] << std::endl;
		}
	}
};

int main()
{
	Program::Main();
	return 0;
}