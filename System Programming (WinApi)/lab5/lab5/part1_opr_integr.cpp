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
int b = 1000;
double sum = 0;
unsigned long const num_threads = 100;
unsigned long const block_size = (b - a) / num_threads;
vector<double> results(num_threads);
vector<thread> threads(num_threads - 1);

double func(double x)
{
	return x / sqrt(pow(x, 4) + 16);
}

void DAC_Avg(double a, double index, double &temp)
{
	temp = func(a + index * block_size) * block_size;
}

void parallel_accumulate()
{
	for (int i = 0; i < (num_threads - 1); i++)
	{
		threads[i] = thread(&DAC_Avg, a, i, ref(results[i]));
	}
	DAC_Avg(a, num_threads - 1, ref(results[num_threads - 1]));
	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
	//accumulate_block()(block_start, last, results[num_threads - 1]);
	//for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
	for (int i = 0; i < num_threads; i++)
	{
		cout << i + 1 << " thread: " << results[i] << endl;
		sum += results[i];
	}
	cout << "Integral with my func = " << sum << endl;
}

int main()
{
	cout << "Integral (real) = " << 400000000 << endl;
	parallel_accumulate();
	return 0;
}