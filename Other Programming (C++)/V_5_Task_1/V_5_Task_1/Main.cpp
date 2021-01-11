#include <mpi.h>
#include <iostream>
#include <random>
#include <iterator>
#include <algorithm>
#include "Process.h"

class Program
{
public:
	static void Main(int argc, char* argv[])
	{
		auto process = MPI::Process();
		int len = 10;
		int num = process.GetProcessCount();
		int *slices = nullptr, *positions = nullptr, sliceSize;
		float *firstVector = nullptr;
		float *secondVector = nullptr;
		float* firstSlice = nullptr;
		float* secondSlice = nullptr;
		if (process.IsMaster())
		{
			firstVector = createVector(len);
			secondVector = createVector(len);

			std::cout << "The first vector: ";
			printVector(firstVector, len);
			std::cout << "The second vector: ";
			printVector(secondVector, len);

			countSlices(len, num, slices, positions);
			for (int i = 0; i < num; ++i)
				if (i != MPI::MasterRank)
					MPI_Send(slices + i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			sliceSize = slices[process.GetRank()];
		}
		else
			MPI_Recv(&sliceSize, 1, MPI_INT, MPI::MasterRank,
				0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		firstSlice = new float[sliceSize];
		secondSlice = new float[sliceSize];
		scatter(firstVector, firstSlice, slices, positions, sliceSize);
		scatter(secondVector, secondSlice, slices, positions, sliceSize);

		int product = computeProduct(firstSlice, secondSlice, sliceSize);
		int theProduct = 0;
		MPI_Reduce(&product, &theProduct, 1, MPI_INT, MPI_SUM, MPI::MasterRank, MPI_COMM_WORLD);
		if (process.IsMaster())
			std::cout << "The result: " << theProduct << '\n';

		delete[] firstSlice;
		delete[] secondSlice;
		if (process.IsMaster())
		{
			delete[] slices;
			delete[] positions;
			delete[] firstVector;
			delete[] secondVector;
		}
	}

private:
	static std::random_device device;
	static std::uniform_int_distribution<> distrib;

	static float * createVector(int length)
	{
		float *result = new float[length];
		std::generate
		(
			result,
			result + length,
			[]()
		    {
			float x = 0.0;
			if (distrib(device) % 3 == 0)
				x = -1.0;
			else if (distrib(device) % 3 == 1)
				x = 0.0;
			else
				x = 1.0;
			return x;
		    }
		);
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

	static void scatter(float *vector, float *slice,
		int *slices, int *positions, int sliceSize)
	{
		MPI_Scatterv
		(
			vector,
			slices,
			positions,
			MPI_INT,
			slice,
			sliceSize,
			MPI_INT,
			MPI::MasterRank,
			MPI_COMM_WORLD
		);
	}

	static int computeProduct(float *firstSlice, float *secondSlice, int sliceSize)
	{
		int result = 0;
		for (int i = 0; i < sliceSize; ++i)
			result += firstSlice[i] * secondSlice[i];
		return result;
	}

	static void printVector(const float *vector, int size)
	{
		std::cout << "(";
		std::copy(vector, vector + size - 1,
			std::ostream_iterator<int>(std::cout, ", "));
		std::cout << vector[size - 1] << ")\n";
	}
};

std::random_device Program::device;
std::uniform_int_distribution<> Program::distrib;

int main(int argc, char* argv[])
{
	Program::Main(argc, argv);
	return 0;
}