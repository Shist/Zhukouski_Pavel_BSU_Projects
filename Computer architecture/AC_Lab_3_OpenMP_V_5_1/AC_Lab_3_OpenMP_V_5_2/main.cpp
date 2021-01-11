#include<omp.h>
#include<iostream>

class Program
{
	const static int a = 2;
	const static int b = 75;

public:
	static void Main(int N)
	{
		if (N <= 0)
		{
			std::cout << "incorrect number of points\n";
			return;
		}
		N++;
		double beginPoint = a;
		double L = (double)(b - a) / N;
		double result = 0;

#pragma omp parallel for schedule(static) reduction(+:result) firstprivate(beginPoint, L)
		bool check = false;
		for (int i = 0; i < N; i++)
		{
			if (!check)
			{ // Самая первая итерация в потоке
				check = true;
				beginPoint += L * i; // Пихаем каждому потоку тот L, который для него насобирался
			}
			else // Таким образом я избавился от критической секции, где я делал beginPoint += L
				beginPoint += L;
			result += (pow(beginPoint, 1.0 / 3.0)) * L;
		}

		std::cout << "Result: " << result << "\n";
		system("pause");
	}
};

int main(int argc, char*argv[])
{
	if (argc != 2)
	{
		std::cout << "incorrect input parameters\n";
		system("pause");
		return -1;
	}
	Program::Main(std::atoi(argv[1]));
}