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

		float **firstMatrix = nullptr, **secondMatrix = nullptr,
			  **firstPiece = nullptr, **secondPiece = nullptr;

		int *slices = nullptr, *positions = nullptr,
			sliceSize;
		if (process.IsMaster())
		{
			firstMatrix = generateMatrix(dimL, dimK);
			secondMatrix = generateMatrix(dimL, dimK);
			std::cout << "The first matrix:\n";
			printMatrix(firstMatrix, dimL, dimK);
			std::cout << "The second matrix:\n";
			printMatrix(secondMatrix, dimL, dimK);
			countSlices(dimL, num, slices, positions);
			for (int i = 0; i < num; ++i)
				if (i != Process::MasterRank)
					MPI_Send(slices + i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			sliceSize = slices[process.GetRank()];
		}
		else
			MPI_Recv(&sliceSize, 1, MPI_INT, Process::MasterRank, 0, 
					 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		firstPiece = scatterMatrix(num, process.GetRank(), firstMatrix, 
								   sliceSize, dimK, slices, positions);
		secondPiece = scatterMatrix(num, process.GetRank(), secondMatrix,
									sliceSize, dimK, slices, positions);
		firstPiece = addMatrixSlices(firstPiece, secondPiece, sliceSize, dimK);

		if (process.IsMaster())
		{
			for (int i = 0; i < num; ++i)
				if (i == Process::MasterRank)
				{
					for (int j = 0; j < slices[i]; ++j)
						std::copy(firstPiece[j], firstPiece[j] + dimK,
								  firstMatrix[positions[i] + j]);
				}
				else
				{
					for (int j = 0; j < slices[i]; ++j)
						MPI_Recv
						(
							firstMatrix[positions[i] + j],
							dimK,
							MPI_FLOAT,
							i,
							i,
							MPI_COMM_WORLD,
							MPI_STATUS_IGNORE
						);
				}
			std::cout << "The sum:\n";
			printMatrix(firstMatrix, dimL, dimK);
		}
		else
		{
			for (int i = 0; i < sliceSize; ++i)
				MPI_Send
				(
					firstPiece[i],
					dimK,
					MPI_FLOAT,
					Process::MasterRank,
					process.GetRank(),
					MPI_COMM_WORLD
				);
		}

		for (int i = 0; i < sliceSize; ++i)
		{
			delete[] firstPiece[i];
			delete[] secondPiece[i];
		}
		delete[] firstPiece;
		delete[] secondPiece;
		if (process.IsMaster())
		{
			for (int i = 0; i < dimL; ++i)
			{
				delete[] firstMatrix[i];
				delete[] secondMatrix[i];
			}
			delete[] firstMatrix;
			delete[] secondMatrix;
			delete[] slices;
			delete[] positions;
		}
	}

private:
	static std::random_device device;
	static std::uniform_int_distribution<> distrib;

	static float ** generateMatrix(int N, int M)
	{
		float **result = new float*[N];
		for (int i = 0; i < N; ++i)
		{
			result[i] = new float[M];
			std::generate(result[i], result[i] + M, []() { return distrib(device); });
		}
		return result;
	}

	static void countSlices(int totalLength, int processNumber,
							int * &slices, int * &positions)
	{
		slices = new int[processNumber];
		std::fill(slices, slices + processNumber, totalLength / processNumber);
		positions = new int[processNumber];
		int i = 0;
		std::generate
		(
			positions,
			positions + processNumber,
			[&]() { return (i++) * (totalLength / processNumber); }
		);
		int shift = 0;
		for (i = 1; i < totalLength % processNumber + 1; ++i)
		{
			++slices[i];
			positions[i] += shift++;
		}
	}

	static float ** scatterMatrix
	   (int processes, int rank, float **matrix, int sliceSize,
		int sliceWidth, int *slices, int *positions)
	{
		float **result = new float*[sliceSize];
		for (int i = 0; i < sliceSize; ++i)
			result[i] = new float[sliceWidth];
		if (rank == Process::MasterRank)
		{
			for (int i = 0; i < processes; ++i)
				if (i != Process::MasterRank)
				{
					for (int j = 0; j < slices[i]; ++j)
						MPI_Send
						(
							matrix[positions[i] + j], 
							sliceWidth, 
							MPI_FLOAT, 
							i, 
							i, 
							MPI_COMM_WORLD
						);
				}
			int pos = positions[rank];
			for (int i = 0; i < sliceSize; ++i)
				std::copy(matrix[i + pos], matrix[i + pos] + sliceWidth, result[i]);
		}
		else
		{
			for (int i = 0; i < sliceSize; ++i)
				MPI_Recv
				(
					result[i],
					sliceWidth,
					MPI_FLOAT,
					Process::MasterRank,
					rank,
					MPI_COMM_WORLD,
					MPI_STATUS_IGNORE
				);
		}
		return result;
	}

	static void printMatrix(float **matrix, int N, int M)
	{
		for (int i = 0; i < N; ++i)
		{
			std::copy(matrix[i], matrix[i] + M,
					  std::ostream_iterator<float>(std::cout, " "));
			std::cout << '\n';
		}
	}

	static float ** addMatrixSlices
		(float **firstMatrix, float **secondMatrix,
		 int sliceSize, int sliceWidth)
	{
		for (int i = 0; i < sliceSize; ++i)
			for (int j = 0; j < sliceWidth; ++j)
				firstMatrix[i][j] += secondMatrix[i][j];
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