#include <fstream>
using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	long long N = 0;
	fin >> N;
	bool check = false;
	long long i = 0;
	for (i; N != 0; i++)
	{
		if (N % 2 == 1)
		{
			fout << i;
			check = true;
		}
		N /= 2;
		if (N != 1 && check)
			fout << endl;
		check = false;
	}
	fin.close();
	fout.close();
	return 0;
}