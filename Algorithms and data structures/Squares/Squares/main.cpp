#include <iostream>
#include <set>
using namespace std;

int main()
{
	int N = 0;
	cin >> N;
	set<pair<int, int>> Set_of_Points;
	int x = 0;
	int y = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> x >> y;
		Set_of_Points.emplace(make_pair(x, y));
	}
	int squares_amount = 0;
	for (set <pair<int, int>> ::iterator it = Set_of_Points.begin(); it != Set_of_Points.end(); it++)
		for (set <pair<int, int>> ::iterator it2 = it; it2 != Set_of_Points.end(); it2++)
			if (it != it2)
			{
				int abscissa_difference = it2->first - it->first;
				int ordinate_difference = it2->second - it->second;
				int need_abscissa_1 = it->first + ordinate_difference;
				int need_ordinata_1 = it->second - abscissa_difference;
				int need_abscissa_2 = it2->first + ordinate_difference;
				int need_ordinata_2 = it2->second - abscissa_difference;
				pair<int, int> need_point_1 = make_pair(need_abscissa_1, need_ordinata_1);
				pair<int, int> need_point_2 = make_pair(need_abscissa_2, need_ordinata_2);
				if (Set_of_Points.find(need_point_1) != Set_of_Points.end() &&
					Set_of_Points.find(need_point_2) != Set_of_Points.end())
					squares_amount++;
				need_abscissa_1 = it->first - ordinate_difference;
				need_ordinata_1 = it->second + abscissa_difference;
				need_abscissa_2 = it2->first - ordinate_difference;
				need_ordinata_2 = it2->second + abscissa_difference;
				need_point_1 = make_pair(need_abscissa_1, need_ordinata_1);
				need_point_2 = make_pair(need_abscissa_2, need_ordinata_2);
				if (Set_of_Points.find(need_point_1) != Set_of_Points.end() &&
					Set_of_Points.find(need_point_2) != Set_of_Points.end())
					squares_amount++;
			}
	squares_amount /= 4;
	cout << squares_amount;
	return 0;
}