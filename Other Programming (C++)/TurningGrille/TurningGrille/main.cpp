#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	ifstream fin("grille.in");
	ofstream fout("grille.out");
	int N = 0;
	fin >> N;
	fin.get();
	vector<string> Grille(N);
	for (int i = 0; i < N; i++)
	{
		string temp = "";
		getline(fin, temp);
		Grille[i] = temp;
	}
	vector<vector<bool>> Holes(N);
	for (int i = 0; i < N; i++)
	{
		Holes[i].resize(N);
		for (int j = 0; j < N; j++)
		{
			Holes[i][j] = false;
			if (Grille[i][j] == '*')
				Holes[i][j] = true;
		}
	}
	bool check = true;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			if (Holes[i][j] == true)
			{
				int curr_i = j;
				int curr_j = N - i - 1;
				if (Grille[curr_i][curr_j] == '*')
				{
					check = false;
					break;
				}
				else
					Grille[curr_i][curr_j] = '*';
				int curr_i_2 = curr_j;
				int curr_j_2 = N - curr_i - 1;
				if (Grille[curr_i_2][curr_j_2] == '*')
				{
					check = false;
					break;
				}
				else
					Grille[curr_i_2][curr_j_2] = '*';
				int curr_i_3 = curr_j_2;
				int curr_j_3 = N - curr_i_2 - 1;
				if (Grille[curr_i_3][curr_j_3] == '*')
				{
					check = false;
					break;
				}
				else
					Grille[curr_i_3][curr_j_3] = '*';
			}
		if (!check)
			break;
	}
	if (check)
		fout << "YES";
	else
		fout << "NO";
	fin.close();
	fout.close();
	return 0;
}