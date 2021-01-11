#include <iostream>
#include <string>
using namespace std;

string From_Binary_str_To_Base64(string binary_str)
{
	string result_str = "";
	string base64_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	string temp_str = "";
	for (int i = 0; i < binary_str.size(); i++)
	{
		temp_str += binary_str[i];
		if (temp_str.size() == 6)
		{
			int num = 0;
			int two = 1;
			for (int j = 5; j >= 0; j--)
			{
				num += ((int)temp_str[j] - 48) * two;
				two *= 2;
			}
			result_str += base64_str[num];
			temp_str = "";
		}
	}
	return result_str;
}

int main()
{
	int N = 0;
	cin >> N;
	int size = 3 * N;
	char* str = new char[size];
	cin.getline(str, size);
	cin.getline(str, size);
	string binary_str = "";
	int i = 0;
	while (i < size)
	{
		if (str[i] == ' ')
		{
			i++;
			continue;
		}
		if (str[i] == '0')
			binary_str += "0000";
		else if (str[i] == '1')
			binary_str += "0001";
		else if (str[i] == '2')
			binary_str += "0010";
		else if (str[i] == '3')
			binary_str += "0011";
		else if (str[i] == '4')
			binary_str += "0100";
		else if (str[i] == '5')
			binary_str += "0101";
		else if (str[i] == '6')
			binary_str += "0110";
		else if (str[i] == '7')
			binary_str += "0111";
		else if (str[i] == '8')
			binary_str += "1000";
		else if (str[i] == '9')
			binary_str += "1001";
		else if (str[i] == 'A')
			binary_str += "1010";
		else if (str[i] == 'B')
			binary_str += "1011";
		else if (str[i] == 'C')
			binary_str += "1100";
		else if (str[i] == 'D')
			binary_str += "1101";
		else if (str[i] == 'E')
			binary_str += "1110";
		else if (str[i] == 'F')
			binary_str += "1111";
		i++;
	}
	string result_str = "";
	if (N % 3 == 0)
		result_str = From_Binary_str_To_Base64(binary_str);
	else if (N % 3 == 1)
	{
		binary_str += "0000";
		result_str = From_Binary_str_To_Base64(binary_str);
		result_str += "==";
	}
	else if (N % 3 == 2)
	{
		binary_str += "00";
		result_str = From_Binary_str_To_Base64(binary_str);
		result_str += "=";
	}
	cout << result_str;
	delete[] str;
	return 0;
}