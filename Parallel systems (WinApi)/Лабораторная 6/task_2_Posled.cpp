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

int main()
{
    int* mas = new int[n];
    for (int i = 0; i < n; i++)
    {
        mas[i] = rand() % b;
    }
    clock_t start = clock();
    double avg = Avrg(mas);
    cout << "\nThe avg of elements of vector is " << avg << endl;
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nThe time: %f seconds\n", seconds);
    return 0;
}