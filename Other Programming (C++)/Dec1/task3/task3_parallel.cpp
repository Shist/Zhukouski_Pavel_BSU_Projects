#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <future>
#include <numeric>
using namespace std;

#pragma comment(linker, "/STACK:16777216")

int n = 500000000;
int a = 0;
int b = 50;
double sum = 0;
int index = 0;

double DAC_Avg(double* begin, double* end, double init)
{
	return accumulate(begin, end, init) / (n / 2);
}

double comp2(vector<double>& v)
{
	using Task_type = double(double*, double*, double);
	packaged_task<Task_type> pt0{ DAC_Avg };
	packaged_task<Task_type> pt1{ DAC_Avg };
	future<double> f0{ pt0.get_future() };
	future<double> f1{ pt1.get_future() };
	auto v0 = &v[0];
	auto sz = v.size();
	thread t1{ move(pt0), v0, v0 + sz / 2, 0.0 };
	thread t2{ move(pt1), v0 + sz / 2, v0 + sz, 0.0 };
	return (f0.get() + f1.get()) / 2;
}

double comp4(vector<double>& v)
{
	auto v0 = &v[0];
	auto sz = v.size();
	auto f0 = async(DAC_Avg, v0, v0 + sz / 2, 0.0);
	auto fl = async(DAC_Avg, v0 + sz / 2, v0 + sz, 0.0);
	return (f0.get() + fl.get()) / 2;
}

int main()
{
	vector<double> v(n);
	for (int i = 0; i < n; i++)
	{
		v[i] = rand() % b;
	}
	/*for (int i = 0; i < n; i++)
	{
		cout << v.at(i) << " ";
	}*/
	clock_t start = clock();
	double avg = comp4(v);
	cout << "\nThe avg of elements of vector is " << avg << endl;
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\nThe time: %f seconds\n", seconds);
	return 0;
}