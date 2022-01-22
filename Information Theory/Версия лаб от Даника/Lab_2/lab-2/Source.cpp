#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <queue>
#include <map>
#include <cmath>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

double factorial(int i)
{
	if (i == 0) return 1;
	else return i * factorial(i - 1);
}

int main()
{
	double p, e, n;
	fin >> p >> e >> n;
	double H = -p * log(p)/log(2.0) - (1 - p) * log(1 - p)/log(2.0);
	fout << "Энтропия: " << H << "\n";
	double minLimitCount = (1.0 - e) * pow(2.0, double(double(n) * (H - e)));
	double maxLimitCount = pow(2, n * (H + e));
	fout << "Нижняя граница: " << minLimitCount << "\nВерхняя граница: " << maxLimitCount << "\n";
	double sum = 0.0, totalP = 0.0;
	for (int i = 1; i < n + 1; i++)
	{
		double e1 = e / log((1 - p) / p)/log(2.0);
		double currentE = abs(i / double(n) - p);
		if (currentE <= e1)
		{
			double factN = (factorial(n) / (factorial(i) * factorial(n - i)));
			sum += factN;
			totalP += factN * (pow(p, i)) * (pow(1.0 - p, n - i));
		}
	}
	fout << "Число e-типичных последовательностей: " << sum << "\n";
	fout << "Относительно всех: " << sum / (pow(2, n)) << "\n";
	fout << "Сумма вероятностей e-типичных последовательностей: " << totalP << "\n";
	if (totalP > 1 - e)
		fout << "P > 1-e: " << totalP << ">" << 1 - e << " ~ TRUE" << "\n";
	else
		fout << "P > 1-e: " << totalP << ">" << 1 - e << " ~ FALSE" << "\n";
}

/*
LAB1 input
4
e 0.1
g 0.3
o 0.2
r 0.4
*/