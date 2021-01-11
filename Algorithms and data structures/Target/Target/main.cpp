#include <iostream>
using namespace std;

int main()
{
	int r1 = 0;
	int r2 = 0;
	cin >> r1 >> r2;
	int a = 0;
	int k = 0;
	cin >> a >> k;
	int n = 0;
	cin >> n;
	int result = 0;
	while (n != 0)
	{
		n--;
		int x = 0;
		int y = 0;
		cin >> x >> y;
		if (x == 0 || y == 0 || x >= r2 || y >= r2)
			continue; // Если попадание в самый центр или в границы, или за пределы, то выстрел точно не засчитываем
		if (x < 0)
		{
			if (y < 0)
			{ // 3 четверть
				if (x * x + y * y < r1 * r1)
					result -= k;
				else if (x * x + y * y > r1 * r1 && x * x + y * y < r2 * r2)
					result += a;
			}
			else if (y > 0)
			{ // 2 четверть
				if (x * x + y * y < r1 * r1)
					result += a;
				else if (x * x + y * y > r1 * r1 && x * x + y * y < r2 * r2)
					result -= k;
			}
		}
		else if (x > 0)
		{
			if (y < 0)
			{ // 4 четверть
				if (x * x + y * y < r1 * r1)
					result += a;
				else if (x * x + y * y > r1 * r1 && x * x + y * y < r2 * r2)
					result -= k;
			}
			else if (y > 0)
			{ // 1 четверть
				if (x * x + y * y < r1 * r1)
					result -= k;
				else if (x * x + y * y > r1 * r1 && x * x + y * y < r2 * r2)
					result += a;
			}
		}
	}
	cout << result;
	return 0;
}