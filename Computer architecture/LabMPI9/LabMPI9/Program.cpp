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
		auto process = Process(argc, argv);

		int len = process.GetVectorLength(),
			num = process.GetProcessNumber();
		
		int *slices = nullptr, *positions = nullptr, 
			*firstVector = nullptr, *secondVector = nullptr,
			*firstSlice = nullptr, *secondSlice = nullptr,
			sliceSize;
		if (process.IsMaster())
		{
			firstVector = createVector(len);
			secondVector = createVector(len);
			
			std::cout << "The first vector is: ";
			printVector(firstVector, len);
			std::cout << "The second vector is: ";
			printVector(secondVector, len);
			
			countSlices(len, num, slices, positions);
			for (int i = 0; i < num; ++i)
				if (i != Process::MasterRank)
					MPI_Send(slices + i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			sliceSize = slices[process.GetRank()];
		}
		else
			MPI_Recv(&sliceSize, 1, MPI_INT, Process::MasterRank,
					 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		firstSlice = new int[sliceSize];
		secondSlice = new int[sliceSize];
		scatter(firstVector, firstSlice, slices, positions, sliceSize);
		scatter(secondVector, secondSlice, slices, positions, sliceSize);

		int product = computeProduct(firstSlice, secondSlice, sliceSize);
		int theProduct = 0;
		MPI_Reduce(&product, &theProduct, 1, MPI_INT, MPI_SUM, Process::MasterRank, MPI_COMM_WORLD);
		if (process.IsMaster())
			std::cout << "The scalar product is " << theProduct << '\n';
		
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

	static int * createVector(int length)
	{
		int *result = new int[length];
		std::generate
		(
			result, 
			result + length,
			[]() { return distrib(device) & 1 ? -1 : 1; }
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

	static void scatter(int *vector, int *slice,
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
			Process::MasterRank,
			MPI_COMM_WORLD
		);
	}

	static int computeProduct(int *firstSlice, int *secondSlice, int sliceSize)
	{
		int result = 0;
		for (int i = 0; i < sliceSize; ++i)
			result += firstSlice[i] * secondSlice[i];
		return result;
	}

	static void printVector(const int *vector, int size)
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