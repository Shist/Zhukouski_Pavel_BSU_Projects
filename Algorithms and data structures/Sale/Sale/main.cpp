#include <iostream>
using namespace std;

int Max_from_three(int x, int y, int z)
{
	int result = 0;
	if (x > y)
		result = x;
	else
		result = y;
	if (z > result)
		result = z;
	return result;
}

int main()
{
	int x = 0;
	int y = 0;
	int z = 0;
	cin >> x >> y >> z;
	int answer = x + y + z - Max_from_three(x, y, z);
	cout << answer;
	return 0;
}