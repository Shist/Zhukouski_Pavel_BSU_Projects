#include <iostream>
using namespace std;

int main()
{
	float num1 = 123456789.1;
	float num2 = 123456787.1;
	float diff1 = num1 - num2;
	cout << "diff1 (4 bytes) = " << diff1 << endl;
	double num3 = 87654321098765432.1;
	double num4 = 87654321098765431.1;
	double diff2 = num3 - num4;
	cout << "diff2 (8 bytes) = " << diff2 << endl;
	return 0;
}