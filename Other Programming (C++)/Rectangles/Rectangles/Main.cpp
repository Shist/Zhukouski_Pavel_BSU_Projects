#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ifstream fin("rect.in");
	ofstream fout("rect.out");
	long long Xmax = 0;
	fin >> Xmax;
	long long Ymax = 0;
	fin >> Ymax;
	long long N = 0;
	fin >> N;
	N *= 2;
	vector<pair<long long, char>> Shadow(N);
	for (long long i = 0; i < N; i++)
	{
		long long b_l_X = 0;
		fin >> b_l_X;
		long long b_l_Y = 0;
		fin >> b_l_Y;
		long long t_r_X = 0;
		fin >> t_r_X;
		long long t_r_Y = 0;
		fin >> t_r_Y;
		long long t_l_X = b_l_X;
		long long t_l_Y = t_r_Y;
		long long b_r_X = t_r_X;
		long long b_r_Y = b_l_Y;
		long long Coord = 0;
		if (t_l_Y != 0)
		{
			long long Check_1 = t_l_X * Ymax;
			long long Check_2 = t_l_Y * Xmax;
			if (Check_1 < Check_2)
				Coord = (t_l_Y - 1 + Check_1) / t_l_Y;
			else
				Coord = Xmax - Check_2 / t_l_X + Ymax;
		}
		else
			Coord = INT_MAX;
		Shadow[i] = make_pair(Coord, '(');
		i++;
		if (b_r_Y != 0)
		{
			long long Check_1 = b_r_X * Ymax;
			long long Check_2 = b_r_Y * Xmax;
			if (Check_1 < Check_2)
				Coord = Check_1 / b_r_Y;
			else
				Coord = Xmax - (b_r_X - 1 + Check_2) / b_r_X + Ymax;
		}
		else
			Coord = INT_MAX;
		Shadow[i] = make_pair(Coord, ')');
	}
	sort(Shadow.begin(), Shadow.end());
	long long curr_count = 0;
	long long max_count = 0;
	long long result_Coord = 0;
	for (pair<long long, char> sh : Shadow)
	{
		if (sh.second == '(')
			curr_count++;
		else if (sh.second == ')')
			curr_count--;
		if (curr_count > max_count)
		{
			max_count = curr_count;
			result_Coord = sh.first;
		}
	}
	long long result_X = 0;
	long long result_Y = 0;
	if (result_Coord > Xmax)
	{
		result_X = Xmax;
		result_Y = Xmax + Ymax - result_Coord;
	}
	else
	{
		result_X = result_Coord;
		result_Y = Ymax;
	}
	fout << max_count << " " << result_X << " " << result_Y;
	fin.close();
	fout.close();
	return 0;
}