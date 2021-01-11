#include <iostream>
#include <iomanip>
#include <iterator>
#include <future>
#include <numeric>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

vector<double> results(num_threads);
vector<thread> threads(num_threads - 1);

int a = 0;
int b = 1000;
double sum = 0;
unsigned long const num_threads = 100;
unsigned long const block_size = (b - a) / num_threads;

double Foo(double x)
{
	return x / sqrt(pow(x, 4) + 16);
}

void Avrg(double a, double index, double &temp)
{
	temp = Foo(a + index * block_size) * block_size;
}

void ParalCalculate()
{
	for (int i = 0; i < (num_threads - 1); i++)
	{
		threads[i] = thread(&Avrg, a, i, ref(results[i]));
	}
	Avrg(a, num_threads - 1, ref(results[num_threads - 1]));
	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
	//accumulate_block()(block_start, last, results[num_threads - 1]);
	//for_each(threads.begin(), threads.end(),std::mem_fn(&std::thread::join));
	for (int i = 0; i < num_threads; i++)
	{
		cout << i + 1 << " thread: " << results[i] << endl;
		sum += results[i];
	}
	cout << "Integral with my Foo = " << sum << endl;
}

int main()
{
	cout << "Integral (real) = " << 400000000 << endl;
	ParalCalculate();
	return 0;
}