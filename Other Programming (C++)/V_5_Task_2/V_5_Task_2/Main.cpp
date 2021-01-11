#include <mpi.h>
#include <iostream>
#include <random>
#include "Process.h"


class Program
{
private:
	static std::random_device device;
	static std::uniform_int_distribution<> distrib;
	static float*generateMatrix(int N, int M)
	{
		float* result = new float[N * M];
		std::generate(result, result + N * M, []() {return distrib(device); });
		return result;
	}
	static void scatterMatrix(float* matrix, float* slice, int* slices, int* positions, int sliceSize)
	{
		MPI_Scatterv(matrix, slices, positions, MPI_FLOAT, slice, sliceSize, MPI_FLOAT, MPI::MasterRank, MPI_COMM_WORLD);
	}
	static void gather(float* matrix, float* slice, int* slices, int* positions, int sliceSize)
	{
		MPI_Gatherv(slice, sliceSize, MPI_FLOAT, matrix, slices, positions, MPI_FLOAT, MPI::MasterRank, MPI_COMM_WORLD);
	}
	static void printMatrix(float*matrix, int N, int M)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				std::cout << matrix[i*M + j] << " ";
			}
			std::cout << "\n";
		}
	}
	static float* sum(float* firstMatrix, float* secondMatrix, int dimL, int dimM) {
		float* answer = new float[dimL*dimM];
		for (int i = 0; i < dimL; i++)
		{
			for (int j = 0; j < dimM; j++)
			{
				answer[i*dimM + j] = firstMatrix[i*dimM + j] + secondMatrix[i*dimM + j];
			}
		}
		return answer;
	}
	static void countSlice(int processNumber, int N, int M, int *&slices, int *&positions)
	{
		slices = new int[processNumber];
		positions = new int[processNumber];
		std::fill(slices, slices + processNumber, (N / processNumber)*M);
		for (int i = 0; i < processNumber; i++)
			positions[i] = i * (N / processNumber)*M;
		for (int i = 1, shift = 0; i < ((N%processNumber) + 1); i++, shift += M)
		{
			slices[i] = M;
			positions[i] += shift;
		}
	}
public:
	static void Main()
	{
		auto process = MPI::Process();
		int num = process.GetProcessCount();
		int dimL, dimM;
		if (process.IsMaster())
		{
			std::cout << "Input the parameters L and M:\n";
			std::cin >> dimL >> dimM;
		}
		MPI_Bcast(&dimL, 1, MPI_INT, MPI::MasterRank, MPI_COMM_WORLD);
		MPI_Bcast(&dimM, 1, MPI_INT, MPI::MasterRank, MPI_COMM_WORLD);
		float *firstMatrix = nullptr, *secondMatrix = nullptr;
		float *firstSlice = nullptr, *secondSlice = nullptr;
		float *answer = nullptr, *result = nullptr;
		int *firstSlises = nullptr, *firstPositions = nullptr;
		int *secondSlises = nullptr, *secondPositions = nullptr;
		int sliceSizes[2];
		if (process.IsMaster())
		{
			firstMatrix = generateMatrix(dimL, dimM);
			secondMatrix = generateMatrix(dimL, dimM);
			std::cout << "The first matrix: \n";
			printMatrix(firstMatrix, dimL, dimM);
			std::cout << "The second matrix: \n";
			printMatrix(secondMatrix, dimL, dimM);
			countSlice(num, dimL, dimM, firstSlises, firstPositions);
			countSlice(num, dimL, dimM, secondSlises, secondPositions);
			for (int i = 1; i < num; i++)
			{
				sliceSizes[0] = firstSlises[i];
				sliceSizes[1] = secondSlises[i];
				MPI_Send(sliceSizes, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
			sliceSizes[0] = firstSlises[0];
			sliceSizes[1] = secondSlises[0];
		}
		else
			MPI_Recv(sliceSizes, 2, MPI_INT, MPI::MasterRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		firstSlice = new float[sliceSizes[0]];
		secondSlice = new float[sliceSizes[1]];
		scatterMatrix(firstMatrix, firstSlice, firstSlises, firstPositions, sliceSizes[0]);
		scatterMatrix(secondMatrix, secondSlice, secondSlises, secondPositions, sliceSizes[1]);
		result = sum(firstSlice, secondSlice, dimL, dimM);
		if (process.IsMaster())
		{
			answer = new float[dimL*dimM];
		}
		gather(answer, result, firstSlises, firstPositions, sliceSizes[0]);
		if (process.IsMaster())
		{
			std::cout << "Result: \n";
			printMatrix(answer, dimL, dimM);
		}
		delete[] firstSlice;
		delete[] secondSlice;
		delete[] result;
		if (process.IsMaster())
		{
			delete[] firstMatrix;
			delete[] secondMatrix;
			delete[] firstSlises;
			delete[] secondSlises;
			delete[] firstPositions;
			delete[] secondPositions;
			delete[] answer;
		}
	}
};


std::random_device Program::device;
std::uniform_int_distribution<> Program::distrib(-100, 100);

int main()
{
	Program::Main();
	return 0;
}