#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <future>

using namespace std;

int n = 2000000;
int a = 0;
int b = 50;

int FooSearch(int* mas)
{
	int amount = 0;
	bool flag = true;
	for (int i = 0; i < n; i++)
	{
		if (mas[i] != 0 && mas[i] != 1 && mas[i] % 2 != 0)
		{
			for (int j = 3; j < mas[i]; j += 1)
			{
				if (mas[i] % j == 0)
				{
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				amount++;
			}
		}
		flag = true;
	}
	return amount;
}

int main()
{
	int* mas = new int[n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = rand() % b;
	}
	clock_t start = clock();
	future<int> the_answer = async(FooSearch, mas);
	cout << "\nThe answer is " << the_answer.get() << std::endl;
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\nThe time: %f seconds\n", seconds);
	return 0;
}