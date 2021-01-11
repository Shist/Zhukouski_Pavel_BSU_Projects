#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int** new_matrix(int height, int width)
{
	int** mx = new int*[height];
	for (int i = 0; i < height; i++)
	{
		mx[i] = new int[width];
	}
	return mx;
}

void null_matrix(int** mx, int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			mx[i][j] = 0;
		}
	}
}

int main()
{
	ifstream IN;
	ofstream OUT;
	IN.open("input.txt");

	string str = "";
	getline(IN, str);

	int n = str.length();

	int** matrix = new_matrix(n, n);
	//null_matrix(matrix, n + 1, n + 1);

	for (int i = 0; i < n; i++)
	{
		matrix[i][i] = 1;
	}

	int s_j = 1;
	int j = 1;
	int i = 0;

	for (int k = 0; k < n; k++)
	{
		for (i; i < n; i++)
		{
			if (i + 1 == j)
			{
				if (str[i] != str[j])
					matrix[i][j] = 1;
				else
					matrix[i][j] = 2;
			}
			else if (i == j)
				matrix[i][j] = 1;
			else if (j > i)
			{
				if (str[i] != str[j])
				{
					if (matrix[i][j - 1] > matrix[i + 1][j])
					{
						matrix[i][j] = matrix[i][j - 1];
					}
					else
					{
						matrix[i][j] = matrix[i + 1][j];
					}
				}
				else
				{
					matrix[i][j] = matrix[i + 1][j - 1] + 2;
				}
			}
			if (j < n)
				j += 1;
		}
		i = 0;
		j = s_j + 1;
		s_j = j;
	}

	int length = matrix[0][n - 1];
	i = 0;
	j = str.length() - 1;
	string half_result_string = "";

	while (j > i)
	{
		if (str[i] == str[j])
		{
			half_result_string += str[i];
			i += 1;
			j -= 1;
		}
		else
		{
			if (matrix[i][j - 1] >= matrix[i + 1][j])
			{
				j -= 1;
			}
			else
			{
				i += 1;
			}
		}
	}
	half_result_string += str[i];

	char* final_string = new char[length];
	int l = 0;

	for (l; l < length / 2; l++)
	{
		final_string[l] = half_result_string[l];
		final_string[length - l - 1] = half_result_string[l];
	}

	if (length % 2 != 0)
	{
		half_result_string += str[i];
		final_string[length / 2] = half_result_string[l];
	}


	IN.close();

	OUT.open("output.txt");

	OUT << length << "\n";
	for (int i = 0; i < length; i++)
		OUT << final_string[i];

	delete[] final_string;
	OUT.close();
}