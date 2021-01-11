#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N = 0, M = 0;
	fin >> N >> M;
	int MN = M * N;
	int* arr = new int[MN]; // Массив
	int i = 0;
	for (i; i < MN; i++)
		fin >> arr[i];
	sort(arr, arr + MN);
	i = 0;
	for (i; i < MN - 1; i++)
	{
		fout << arr[i] << " ";
	}
	fout << arr[i];
	delete[] arr;
	fin.close();
	fout.close();
	return 0;
}