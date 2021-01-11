#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <future>
#include <numeric>
using namespace std;

int a = 0;
int b = 100000;
const int N = 8000; // == num_threads
vector<double> results(N);
vector<thread> threads(N - 1);

void DAC_Avg(double** matrix, vector<double> v, int index, double &temp)
{
	for (int i = 0; i < N; i++)
	{
		temp += matrix[index][i] * v[i];
	}
}

void parallel_accumulate(double** matrix, vector<double>& v)
{
	for (int i = 0; i < (N - 1); i++)
	{
		threads[i] = thread(&DAC_Avg, matrix, v, i, ref(results[i]));
	}
	DAC_Avg(matrix, v, N - 1, ref(results[N - 1]));
	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
	/*cout << "\n";
	for (int i = 0; i < N; i++)
	{
		cout << i + 1 << " thread: " << results[i] << endl;
	}*/
}

int main()
{
	double** matrix = new double* [N];
	for (int i = 0; i < N; i++)
		matrix[i] = new double[N];
	vector<double> v(N);
	//cout << "Matrix: \n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matrix[i][j] = rand() % b;
			//cout << matrix[i][j] << " ";
		}
		//cout << endl;
	}
	//cout << "\nVector: \n";
	for (int i = 0; i < N; i++)
	{
		v[i] = rand() % b;
		//cout << v[i] << " - " << i + 1 << " element of vector" << endl;
	}
	clock_t start = clock();
	parallel_accumulate(matrix, v);
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\nThe time: %f seconds\n", seconds);
	return 0;
}