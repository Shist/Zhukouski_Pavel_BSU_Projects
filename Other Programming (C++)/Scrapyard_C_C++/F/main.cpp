#include <iostream>
#include <windows.h>
#include <random>
#include <string>
using namespace std;

string Foo(int num1, int num2)
{
	string part1 = "";
	string part2 = "";
	if (num1 == 0)
		part1 = "0";
	else if (num1 == 1)
		part1 = "1";
	else if (num1 == 2)
		part1 = "2";
	else if (num1 == 3)
		part1 = "3";
	else if (num1 == 4)
		part1 = "4";
	else if (num1 == 5)
		part1 = "5";
	else if (num1 == 6)
		part1 = "6";
	else if (num1 == 7)
		part1 = "7";
	else if (num1 == 8)
		part1 = "8";
	else if (num1 == 9)
		part1 = "9";
	else if (num1 == 10)
		part1 = "A";
	else if (num1 == 11)
		part1 = "B";
	else if (num1 == 12)
		part1 = "C";
	else if (num1 == 13)
		part1 = "E";
	else if (num1 == 14)
		part1 = "F";
	if (num2 == 0)
		part2 = "0";
	else if (num2 == 1)
		part2 = "1";
	else if (num2 == 2)
		part2 = "2";
	else if (num2 == 3)
		part2 = "3";
	else if (num2 == 4)
		part2 = "4";
	else if (num2 == 5)
		part2 = "5";
	else if (num2 == 6)
		part2 = "6";
	else if (num2 == 7)
		part2 = "7";
	else if (num2 == 8)
		part2 = "8";
	else if (num2 == 9)
		part2 = "9";
	else if (num2 == 10)
		part2 = "A";
	else if (num2 == 11)
		part2 = "B";
	else if (num2 == 12)
		part2 = "C";
	else if (num2 == 13)
		part2 = "E";
	else if (num2 == 14)
		part2 = "F";
	return (part1 + part2);
}

int main(int argc, char* argv[])
{
	random_device generator;
	uniform_int_distribution<int> distribution(0, 15);
	int num1 = distribution(generator);
	int num2 = distribution(generator);
	string color = "color ";
	color += Foo(num1, num2);
	system(color.c_str());
	printf_s("                                                                    \n");
	printf_s("           FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	printf_s("           FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	printf_s("           FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	printf_s("           FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	printf_s("           FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	printf_s("           FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	printf_s("           FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	printf_s("           FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	printf_s("           FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	printf_s("           FFFFFFFFFFFFFFFF                                         \n");
	return 0;
}