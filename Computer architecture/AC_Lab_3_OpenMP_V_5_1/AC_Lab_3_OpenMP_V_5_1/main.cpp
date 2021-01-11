#include<omp.h>
#include<iostream>
#include<math.h>

class Program
{
public:
	static void Main(int N, int b)
	{
		if (N <= 0)
		{
			printf("Incorrect parameter N");
			return;
		}
		double L = (double)(b + 1) / N + 1;
		double maxValue = DBL_MIN_10_EXP;
		double temp;
		double startDivide;

		startDivide = (double(b + 1)) / 4;

		L /= 4;

		double startValue;
		double startPoint;
		omp_set_nested(true);
		int i = 0;

#pragma omp parallel sections firstprivate(startValue,startPoint,temp,startDivide) 
		{
#pragma omp section
			{
				startPoint = -1;
#pragma omp parallel for schedule(static) firstprivate(startValue,startPoint,temp)
				for (int i = 0; i < N; i++)
				{
					startValue = countValue(startPoint + i * L);
					temp = fabs((countValue(startPoint + (i + 1) * L) - startValue) / L);
#pragma omp critical
					{
						if (temp > maxValue)
							maxValue = temp;
					}
				}
			}
#pragma omp section
			{
				startPoint = (double)-1 + startDivide;
#pragma omp parallel for schedule(static) firstprivate(startValue,startPoint,temp)
				for (int i = 0; i < N; i++)
				{
					startValue = countValue(startPoint + i * L);
					temp = fabs((countValue(startPoint + (i + 1) * L) - startValue) / L);
#pragma omp critical
					{
						if (temp > maxValue)
							maxValue = temp;
					}
				}
			}
#pragma omp section
			{
				startPoint = (double)-1 + startDivide * 2;
#pragma omp parallel for schedule(static) firstprivate(startValue,startPoint,temp)
				for (int i = 0; i < N; i++)
				{
					startValue = countValue(startPoint + i * L);
					temp = fabs((countValue(startPoint + (i + 1) * L) - startValue) / L);
#pragma omp critical
					{
						if (temp > maxValue)
							maxValue = temp;
					}
				}

			}
#pragma omp section
			{

				startPoint = (double)-1 + startDivide * 3;
#pragma omp parallel for schedule(static) firstprivate(startValue,startPoint,temp)
				for (int i = 0; i < N; i++)
				{
					startValue = countValue(startPoint + i * L);
					temp = fabs((countValue(startPoint + (i + 1) * L) - startValue) / L);
#pragma omp critical
					{
						if (temp > maxValue)
							maxValue = temp;
					}
				}
			}
		}

		std::cout << "Result: " << maxValue << "\n";
		system("pause");
	}


private:
	static double countValue(double x)
	{
		return x < 1 ? (x*x - 5 * x / 2 + (double)1 / 2) : (-pow(x, (double)1 / 2));
	}
};



int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "incorrect parameters";
		return 1;
	}
	Program::Main(std::atoi(argv[1]), std::atoi(argv[2]));
}