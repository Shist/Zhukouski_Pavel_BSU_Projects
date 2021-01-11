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
		std::generate(result, result + N * M, []() {return distrib(device) % 2 == 0 ? -1 : 0; });
		return result;
	}
	static void scatterMatrix(float* matrix, float* slice, int* slices, int* positions, int sliceSize)
	{
		MPI_Scatterv(matrix, slices, positions, MPI_FLOAT, slice, sliceSize, MPI_FLOAT, MPI::MasterRank, MPI_COMM_WORLD);
	}
	static void reduce(float* answer, float* part, int partSize)
	{
		MPI_Reduce(part, answer, partSize, MPI_FLOAT, MPI_SUM, MPI::MasterRank, MPI_COMM_WORLD);
	}
	static void printMatrix(float*matrix, int N, int M)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++) {
				std::cout << matrix[i*M + j] << " ";
			}
			std::cout << "\n";
		}
	}
	static void printMatrixTranspose(float*matrix, int N, int M)
	{
		for (int j = 0; j < M; j++)
		{
			for (int i = 0; i < N; i++) {
				std::cout << matrix[i*M + j] << " ";
			}
			std::cout << "\n";
		}
	}
	static float* multiply(float* firstMatrix, float* secondMatrix, int dimK, int dimC, int dimM)
	{
		float* answer = new float[dimK*dimM];
		for (int i = 0; i < dimK; i++)
		{
			for (int j = 0; j < dimM; j++)
			{
				answer[i*dimM + j] = 0;
				for (int k = 0; k < dimC; k++)
				{
					answer[i*dimM + j] += firstMatrix[k*dimK + i] * secondMatrix[k*dimM + j];
				}
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
		int dimk, dimL, dimM;
		if (process.IsMaster())
		{
			std::cout << "Input the parameters K, L, M:\n";
			std::cin >> dimk >> dimL >> dimM;
		}
		MPI_Bcast(&dimk, 1, MPI_INT, MPI::MasterRank, MPI_COMM_WORLD);
		MPI_Bcast(&dimM, 1, MPI_INT, MPI::MasterRank, MPI_COMM_WORLD);
		float *firstMatrix = nullptr, *secondMatrix = nullptr;
		float *firstSlice = nullptr, *secondSlice = nullptr;
		float *answer = nullptr, *result = nullptr;
		int *firstSlises = nullptr, *firstPositions = nullptr;
		int *secondSlises = nullptr, *secondPositions = nullptr;
		int sliceSizes[2];
		if (process.IsMaster())
		{
			firstMatrix = generateMatrix(dimL, dimk);
			secondMatrix = generateMatrix(dimL, dimM);
			std::cout << "The first matrix: \n";
			printMatrixTranspose(firstMatrix, dimL, dimk);
			std::cout << "The second matrix: \n";
			printMatrix(secondMatrix, dimL, dimM);
			countSlice(num, dimL, dimk, firstSlises, firstPositions);
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
		result = multiply(firstSlice, secondSlice, dimk, sliceSizes[0] / dimk, dimM);
		if (process.IsMaster())
		{
			answer = new float[dimk*dimM];
		}
		reduce(answer, result, dimk*dimM);
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
std::uniform_int_distribution<> Program::distrib;

int main()
{
	Program::Main();
	return 0;
}