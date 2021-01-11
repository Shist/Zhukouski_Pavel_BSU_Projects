#include <iostream>
#include <fstream>
#include <string>
using namespace std;

long double fact(int N) // вз€л с инетрнета эту функцию :P
{
	if (N < 0) // если пользователь ввел отрицательное число
		return 0; // возвращаем ноль
	if (N == 0) // если пользователь ввел ноль,
		return 1; // возвращаем факториал от нул€ - не удивл€етесь, но это 1 =)
	else // ¬о всех остальных случа€х
		return N * fact(N - 1); // делаем рекурсию.
}

int From_Fact(int ch, int ch_amount)
{
	int result = 0;
	int dop_temp_1 = 10;
	int dop_temp_2 = 1;
	for (int i = ch_amount - 1; i != 0; i--)
	{
		dop_temp_2 *= 10;
	}
	while (ch_amount != 0)
	{
		result += ((ch / dop_temp_2) % dop_temp_1) * (int)fact(ch_amount);
		dop_temp_2 /= 10;
		ch_amount--;
	}
	return result;
}

int To_Fact(int ch)
{
	if (ch == 1)
		return 1;
	int result = 0;
	int count = 1;
	int shetchik = 0;
	bool check = true;
	while (ch != 0)
	{
		result = ((result *= 10) + (ch % count));
		if (ch % count == 0 && check)
			shetchik++;
		else
		{
			check = false;
		}
		ch = ch / count;
		count++;
	}
	int y = 0;
	while (result > 0)
	{
		y = y * 10 + result % 10;
		result /= 10;
	}
	if (shetchik != 0)
	{
		y *= 10;
		shetchik--;
	}
	return y;
}

int main()
{
	ifstream fin("factoradic.in.txt");
	ofstream fout("factoradic.out.txt");
	string str = "";
	string str0;
	getline(fin, str0);
	for (int i = 0; i < str0.length(); i++)
	{
		str.push_back(str0[i]);
	}
	bool plus_or_not = false;
	int ch_1 = 0;
	int ch_2 = 0;
	int ch_1_amount = 0;
	int ch_2_amount = 0;
	int dop_temp = 1;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '+')
		{
			plus_or_not = true;
			ch_1_amount = i;
			ch_2_amount = str.length() - i - 1;
			break;
		}
		else if (str[i] == '-')
		{
			ch_1_amount = i;
			ch_2_amount = str.length() - i - 1;
			break;
		}
	}
	int dop_temp_1 = 1;
	int dop_temp_2 = 1;
	for (int i = ch_1_amount; i > 0; i--)
		dop_temp_1 *= 10;
	for (int i = ch_2_amount; i > 0; i--)
		dop_temp_2 *= 10;
	for (int i = 0; i < ch_1_amount; i++)
	{
		dop_temp_1 /= 10;
		ch_1 += (str[i] - '0') * dop_temp_1;
	}
	for (int i = ch_1_amount + 1; i < str.length(); i++)
	{
		dop_temp_2 /= 10;
		ch_2 += (str[i] - '0') * dop_temp_2;
	}
	ch_1 = From_Fact(ch_1, ch_1_amount);
	ch_2 = From_Fact(ch_2, ch_2_amount);
	int result = 0;
	if (plus_or_not)
		result = ch_1 + ch_2;
	else
		result = ch_1 - ch_2;
	fout << To_Fact(result);
	fin.close();
	fout.close();
	return 0;
}