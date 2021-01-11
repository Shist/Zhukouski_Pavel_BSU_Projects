#include <mpi.h>
#include <iostream>
#include "Process.h"

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		// Обычно процесс с рангом 0 считается главным (мастер-процесс). 
		// В топологии «звезда» он посылает данные другим процессам и собирает их обратно.
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
		// Посылаем данные всем остальным процессам.
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
		MPI_Send(                // 1a: Посылка данных:
			&intData,            // Указатель на начало данных.
			1,                   // Длина массива данных.
			MPI_INT,             // Тип данных.
			targetRank,          // Ранг принимающего процесса.
			0,                   // Тэг — номер сообщения (будет рассмотрен далее).
			MPI_COMM_WORLD);     // Группа процессов, в которой идёт работа.
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
			doubleArrayData, // 3a: Обратите внимание, что для массивов передаётся сам указатель, без оператора &.
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

		// Принимаем данные от главного процесса.

		int intData;

		MPI_Recv(                   // 1b: Приём данных:
			&intData, 				// Указатель на начало данных.
			1, 						// Длина массива данных.
			MPI_INT, 				// Тип данных.
			MasterRank, 			// Ранг отправившего процесса.
			0, 						// Тэг — номер сообщения (будет рассмотрен далее).
			MPI_COMM_WORLD, 		// Группа процессов, в которой идёт работа.
			MPI_STATUS_IGNORE);     // Дополнительная информация (будет рассмотрено далее), здесь мы её игнорируем.

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
			doubleArrayData, // 3b: Как и при передаче, используется сам указатель на начало массива.
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