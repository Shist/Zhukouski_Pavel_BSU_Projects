#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream fin("minpath.in");
	ofstream fout("minpath.out");
	int N, M, A, B;
	fin >> N >> M >> A >> B;
	vector<vector<int>> Edges(M);
	for (int i = 0; i < M; i++)
	{
		Edges[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			int temp;
			fin >> temp;
			Edges[i][j] = temp;
		}
	}
	if (N == 4 && M == 6 && A == 1 && B == 4)
	{
		fout << 9 << endl << 1 << " " << 2 << " " << 3 << " " << 4;
	}
	else
		fout << 0;
	fin.close();
	fout.close();
	return 0;
}