#include <mpi.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Process.h"

namespace Direction
{
	enum
	{
		Up    = 0,
		Down  = 1,
		Left  = 2,
		Right = 3,
	};
}

namespace Dimension 
{
	enum
	{
		I = 0,
		J = 1,
	};
}

class Program
{
public:
	static void Main()
	{
		auto process = MPI::Process();

		const auto iSize = 4;
		const auto jSize = 2;

		const auto dimensionCount = 2;
		const int dimensionSizes[dimensionCount] = { iSize, jSize };
		const int shouldReorder = false;
		const int isPeriodicDimension[dimensionCount] = { false, false };

		// 1. Создаём виртуальную топологию.
		MPI_Comm cartesianCommunicator;
		MPI_Cart_create(MPI_COMM_WORLD, dimensionCount, dimensionSizes, isPeriodicDimension, shouldReorder, &cartesianCommunicator);

		// 2. Вычисляем свойства для текущего процесса.
		int rank;
		MPI_Comm_rank(cartesianCommunicator, &rank);

		int coordinates[dimensionCount];
		MPI_Cart_coords(cartesianCommunicator, rank, dimensionCount, coordinates);

		int neighborRanks[4];
		MPI_Cart_shift(cartesianCommunicator, Dimension::I, +1, &neighborRanks[Direction::Up], &neighborRanks[Direction::Down]);
		MPI_Cart_shift(cartesianCommunicator, Dimension::J, +1, &neighborRanks[Direction::Left], &neighborRanks[Direction::Right]);

		// 3. Вывод:
		auto buffer = std::stringstream();
		buffer
			<< "Rank: " << rank << std::endl
			<< "Coordinates: (i: " << coordinates[Dimension::I] << ", j: " << coordinates[Dimension::J] << ")" << std::endl
			<< "Neighbors: [up: " << RankToString(neighborRanks[Direction::Up]) 
			<< ", down: " << RankToString(neighborRanks[Direction::Down])
			<< ", left: " << RankToString(neighborRanks[Direction::Left])
			<< ", right: " << RankToString(neighborRanks[Direction::Right])
			<< "]" << std::endl
			<< std::endl;
		std::cout << buffer.str();
	}

private:
	static std::string RankToString(int rank)
	{
		return (rank != -1)
			? std::to_string(rank)
			: "none";
	}
};

int main()
{
	Program::Main();
	return 0;
}