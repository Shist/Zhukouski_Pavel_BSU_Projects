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

int n = 200000000;
int a = 0;
int b = 50;
double sum = 0;
int index = 0;

double Avrg(double* begin, double* end, double init)
{
	return accumulate(begin, end, init) / n;
}

double FooCalc_4(vector<double>& v)
{
	return Avrg(&v[0], &v[n - 1] + 1, 0.0);
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






/*
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <future>
using namespace std;

#pragma comment(linker, "/STACK:16777216")

int n = 1000;
int a = 0;
int b = 50;
double sum = 0;
int index = 0;

double Avrg(int* mas)
{
	sum += mas[index];
	index++;
	if (index != n)
		Avrg(mas);
	return sum / n;
}

double comp2(int* mas)
{
	using Task_type = double(int*);
	packaged_task<Task_type> pt0{ Avrg };
	packaged_task<Task_type> pt1{ Avrg };
	future<double> f0{ pt0.get_future() };
	future<double> f1{ pt1.get_future() };
	thread t1{ move(pt0), 0, n / 2, 0 };
	thread t2{ move(pt1), n / 2, n, 0 };
	// ...
	return (f0.get() + f1.get())/2;
}

int main()
{
	int* mas = new int[n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = rand() % b;
	}
	clock_t start = clock();
	double avg = comp2(mas);
	cout << "\nThe avg of elements of vector is " << avg << endl;
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\nThe time: %f seconds\n", seconds);
	return 0;
}
*/