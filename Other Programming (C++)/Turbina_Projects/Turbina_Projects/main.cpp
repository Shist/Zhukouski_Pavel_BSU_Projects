#include<iostream>
#include<algorithm>
using namespace std;

void main()
{
	int x, y, z;
	int arr[3];	
	cout << "Input prices" << endl;
	cin >> x >> y >> z;
	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
	sort(arr, arr + 3);
	cout << "minimal value = " << arr[0] + arr[1] << endl;
}