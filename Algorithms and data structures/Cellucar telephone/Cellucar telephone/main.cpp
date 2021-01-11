#include <fstream>
#include <vector>
using namespace std;

long long Sum_of_letters(vector<long long> vec)
{
	long long result = 0;
	for (unsigned int i = 0; i < vec.size(); i++)
		result += vec[i];
	return result;
}

int main()
{
	long long MAX = INT32_MAX;
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	int N = 0;
	fin >> N; // Число клавиш на клавиатуре телефона
	int M = 0;
	fin >> M; // Число букв алфавита
	vector<long long> use_of_letter; // Массив с коэффициентами использования букв
	use_of_letter.reserve(M);
	for (int i = 0; i < M; i++)
	{
		long long temp = 0;
		fin >> temp;
		use_of_letter.push_back(temp); // Считываем данные об использовании каждой буквы алфавита и помещаем в массив
	}
	if (N >= M) // Если кнопок больше либо равно, чем букв
		fout << Sum_of_letters(use_of_letter); // То просто выводим сумму коэффициентов использования букв
	else
	{
		vector<vector<long long>> Min_Sum_Key_Letter_; // В матрице будем хранить все суммы
		Min_Sum_Key_Letter_.reserve(N);
		for (int i = 0; i < N; i++)
		{ // Заполняем первый столбец Za
			Min_Sum_Key_Letter_.push_back(vector<long long>());
			Min_Sum_Key_Letter_[i].reserve(M);
			Min_Sum_Key_Letter_[i].push_back(use_of_letter[0]);
		}
		int k = 1;
		for (int j = 1; j < M; j++)
		{ // Заполняем первую строку нужными значениями (Za, Za + 2*Zb, ...)
			k++;
			Min_Sum_Key_Letter_[0].push_back(Min_Sum_Key_Letter_[0][j - 1] + use_of_letter[j]*k);
		}
		vector<vector<long long>> letters_sums; // В этой матричке храним суммы от одной буквы до другой (для каждой пары)
		letters_sums.reserve(M);
		for (int i = 0; i < M; i++)
			letters_sums.push_back(vector<long long>());
		for (int i = 0; i < M; i++)
			for (int j = 0; j < M; j++)
			{
				if (i > j)
					letters_sums[i].push_back(0);
				else if (i == j)
					letters_sums[i].push_back(use_of_letter[i]);
				else
				{ // i < j
					int sum = 0;
					int koef = 1;
					for (int f = i; f <= j; f++)
					{
						sum += koef * use_of_letter[f];
						koef++;
					}
					letters_sums[i].push_back(sum);
				}
			}
		for (int i = 1; i < N; i++)
			for (int j = 1; j < M; j++)
			{
				int Min = INT32_MAX;
				for (int k = 0; j - k > 0; k++)
					if (letters_sums[j - k][j] + Min_Sum_Key_Letter_[i - 1][j - 1 - k] < Min)
						Min = letters_sums[j - k][j] + Min_Sum_Key_Letter_[i - 1][j - 1 - k];
				Min_Sum_Key_Letter_[i].push_back(Min);
			}
		fout << Min_Sum_Key_Letter_[N - 1][M - 1];
	}
	fin.close();
	fout.close();
	return 0;
}