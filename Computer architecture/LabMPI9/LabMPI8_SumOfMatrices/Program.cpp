#include <mpi.h>
#include <iostream>
#include <random>
#include <iterator>
#include "Process.h"

class Program
{
public:
	static void Main(int argc, char* argv[])
	{
		auto process = Process(argc, argv);

		int dimL, dimK;
		if (process.IsMaster())
		{
			std::cout << "Please input the number of rows and columns in your matrices: ";
			std::cin >> dimL >> dimK;
		}
		MPI_Bcast(&dimK, 1, MPI_INT, Process::MasterRank, MPI_COMM_WORLD);

		int num = process.GetProcessNumber();

		float *firstMatrix = nullptr, *secondMatrix = nullptr,
			  *firstSlice = nullptr, *secondSlice = nullptr;
		int sliceSize, *slices = nullptr, *positions = nullptr;
		if (process.IsMaster())
		{
			firstMatrix = generateMatrix(dimL, dimK);
			secondMatrix = generateMatrix(dimL, dimK);
			
			std::cout << "The first matrix:\n";
			printMatrix(firstMatrix, dimL, dimK);
			std::cout << "The second matrix:\n";
			printMatrix(secondMatrix, dimL, dimK);

			countSlices(num, dimL, dimK, slices, positions);
			for (int i = 0; i < num; ++i)
				if (i != Process::MasterRank)
					MPI_Send(slices + i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			sliceSize = slices[process.GetRank()];
		}
		else
			MPI_Recv(&sliceSize, 1, MPI_INT, Process::MasterRank,
					 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		firstSlice = new float[sliceSize];
		secondSlice = new float[sliceSize];
		scatterMatrix(firstMatrix, firstSlice, slices, positions, sliceSize);
		scatterMatrix(secondMatrix, secondSlice, slices, positions, sliceSize);

		firstSlice = addMatrixSlices(firstSlice, secondSlice, sliceSize);

		gatherMatrices(firstMatrix, firstSlice, slices, positions, sliceSize);
		if (process.IsMaster())
		{
			std::cout << "The sum:\n";
			printMatrix(firstMatrix, dimL, dimK);
		}

		delete[] firstSlice;
		delete[] secondSlice;
		if (process.IsMaster())
		{
			delete[] firstMatrix;
			delete[] secondMatrix;
			delete[] slices;
			delete[] positions;
		}
	}

private:
	static std::random_device device;
	static std::uniform_int_distribution<> distrib;

	static float * generateMatrix(int N, int M)
	{
		float *result = new float[N * M];
		std::generate
		(
			result, 
			result + (N * M), 
			[]() { return distrib(device); }
		);
		return result;
	}

	static void countSlices
		(int processNumber, int rows, int columns,
		 int * &slices, int * &positions)
	{
		slices = new int[processNumber];
		std::fill(slices, slices + processNumber, (rows / processNumber) * columns);
		positions = new int[processNumber];
		int i = 0;
		std::generate
		(
			positions,
			positions + processNumber,
			[&]() { return (i++) * (rows / processNumber) * columns; }
		);
		int shift = 0;
		for (i = 1; i < (rows % processNumber) + 1; ++i)
		{
			slices[i] += columns;
			positions[i] += shift;
			shift += columns;
		}
	}

	static void scatterMatrix
		(float *matrix, float *slice,
		 int *slices, int *positions, int sliceSize)
	{
		MPI_Scatterv
		(
			matrix,
			slices,
			positions,
			MPI_FLOAT,
			slice,
			sliceSize,
			MPI_FLOAT,
			Process::MasterRank,
			MPI_COMM_WORLD
		);
	}

	static void gatherMatrices
		(float *matrix, float *slice,
		 int *slices, int *positions, int sliceSize)
	{
		MPI_Gatherv
		(
			slice,
			sliceSize,
			MPI_FLOAT,
			matrix,
			slices,
			positions,
			MPI_FLOAT,
			Process::MasterRank,
			MPI_COMM_WORLD
		);
	}

	static void printMatrix(float *matrix, int N, int M)
	{
		for (int i = 0; i < N; ++i)
		{
			std::copy(matrix + i * M, matrix + (i + 1) * M,
					  std::ostream_iterator<float>(std::cout, " "));
			std::cout << '\n';
		}
	}

	static float * addMatrixSlices
		(float *firstMatrix, float *secondMatrix, int sliceSize)
	{
		for (int i = 0; i < sliceSize; ++i)
			firstMatrix[i] += secondMatrix[i];
		return firstMatrix;
	}
};

std::random_device Program::device;
std::uniform_int_distribution<> Program::distrib(1, 10);

int main(int argc, char* argv[])
{
	Program::Main(argc, argv);
	return 0;
}