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

double Avrg(double* begin, double* end, double init)
{
	return accumulate(begin, end, init) / (n / 2);
}

double FooCalc_2(vector<double>& v)
{
	using Task_type = double(double*, double*, double);
	packaged_task<Task_type> pt0{ Avrg };
	packaged_task<Task_type> pt1{ Avrg };
	future<double> f0{ pt0.get_future() };
	future<double> f1{ pt1.get_future() };
	auto v0 = &v[0];
	auto sz = v.size();
	thread t1{ move(pt0), v0, v0 + sz / 2, 0.0 };
	thread t2{ move(pt1), v0 + sz / 2, v0 + sz, 0.0 };
	return (f0.get() + f1.get()) / 2;
}

double FooCalc_4(vector<double>& v)
{
	auto v0 = &v[0];
	auto sz = v.size();
	auto f0 = async(Avrg, v0, v0 + sz / 2, 0.0);
	auto fl = async(Avrg, v0 + sz / 2, v0 + sz, 0.0);
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
	double avg = FooCalc_4(v);
	cout << "\nThe avg of elements of vector is " << avg << endl;
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\nThe time: %f seconds\n", seconds);
	return 0;
}