#include <mpi.h>
#include <iostream>
#include <random>
#include <iterator>
#include "Process.h"

class Program
{
public:
	static const int dimL = 3, dimK = 3, dimM = 1;

	static void Main(int argc, char* argv[])
	{
		auto process = Process(argc, argv);

		int num = process.GetProcessNumber();

		float *firstMatrix = nullptr, *secondMatrix = nullptr,
			*firstSlice = nullptr, *secondSlice = nullptr,
			*answer = nullptr, *count = nullptr;
		int *firstSlices = nullptr, *firstPositions = nullptr,
			*secondSlices = nullptr, *secondPositions = nullptr,
			sliceSizes[2];
		if (process.IsMaster())
		{
			firstMatrix = generateMatrix(dimL, dimK);
			secondMatrix = generateMatrix(dimL, dimM);
			
			std::cout << "The first matrix:\n";
			printMatrixTranspose(firstMatrix, dimL, dimK);
			std::cout << "The second matrix:\n";
			printMatrix(secondMatrix, dimL, dimM);

			countSlices(num, dimL, dimK, firstSlices, firstPositions);
			countSlices(num, dimL, dimM, secondSlices, secondPositions);
			for (int i = 0; i < num; ++i)
				if (i != Process::MasterRank)
				{
					sliceSizes[0] = firstSlices[i];
					sliceSizes[1] = secondSlices[i];
					MPI_Send(sliceSizes, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
				}
			sliceSizes[0] = firstSlices[process.GetRank()];
			sliceSizes[1] = secondSlices[process.GetRank()];
		}
		else
			MPI_Recv(sliceSizes, 2, MPI_INT, Process::MasterRank,
					 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		firstSlice = new float[sliceSizes[0]];
		secondSlice = new float[sliceSizes[1]];
		scatterMatrix(firstMatrix, firstSlice, firstSlices, firstPositions, sliceSizes[0]);
		scatterMatrix(secondMatrix, secondSlice, secondSlices, secondPositions, sliceSizes[1]);

		count = multiplySlices(firstSlice, secondSlice, dimK, sliceSizes[0] / dimK, dimM);
		
		if (process.IsMaster())
			answer = new float[dimK * dimM];
		reduceToAnswer(answer, count, dimK * dimM);

		if (process.IsMaster())
		{
			std::cout << "The product:\n";
			printMatrix(answer, dimK, dimM);
		}

		delete[] firstSlice;
		delete[] secondSlice;
		if (process.IsMaster())
		{
			delete[] firstMatrix;
			delete[] secondMatrix;
			delete[] firstSlices;
			delete[] firstPositions;
			delete[] secondSlices;
			delete[] secondPositions;
			delete[] answer;
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
			[]() { return distrib(device) & 1 ? -1 : 0; }
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

	static void reduceToAnswer
		(float *answer, float *part, int partSize)
	{
		MPI_Reduce
		(
			part,
			answer,
			partSize,
			MPI_FLOAT,
			MPI_SUM,
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

	static void printMatrixTranspose(float *matrix, int N, int M)
	{
		for (int j = 0; j < M; ++j)
		{
			for (int i = 0; i < N; ++i)
				std::cout << matrix[i * M + j] << ' ';
			std::cout << '\n';
		}
	}

	static float * multiplySlices
		(float *firstMatrix, float *secondMatrix, 
		 int dimK, int dimC, int dimM)
	{
		float *answer = new float[dimK * dimM];
		for (int i = 0; i < dimK; ++i)
			for (int j = 0; j < dimM; ++j)
			{
				answer[i * dimM + j] = 0;
				for (int k = 0; k < dimC; ++k)
					answer[i * dimM + j] +=
					firstMatrix[k * dimK + i] *
					secondMatrix[k * dimM + j];
			}
		return answer;
	}
};

std::random_device Program::device;
std::uniform_int_distribution<> Program::distrib;

int main(int argc, char* argv[])
{
	Program::Main(argc, argv);
	return 0;
}