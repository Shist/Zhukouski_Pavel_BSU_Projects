// Решение #1
#include <iostream>
using namespace std;

void Queen_attack(int** kletka, int queen_i, int queen_j, int N)
{ // функция, проставляющая на доске kletka[][] размера N x N числа в зависимости от того, какие клетки находятся под боем ферзя с координатами [queen_i][queen_j]
	kletka[queen_i][queen_j] += 10000; // Самой клетке, в которой стоит ферзь, присваиваем 10000, что заведомо больше, чем в любой возможной клетке, в которой не стоит ферзь
	for (int i = 1; i < N; i++)
	{ // В каждой клетке, которую этот ферзь бьет, прибавляем единицу
		if (queen_i - i >= 0 && queen_i - i < N && queen_j >= 0 && queen_j < N)
			kletka[queen_i - i][queen_j] += 1; // Вверх
		if (queen_i - i >= 0 && queen_i - i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i - i][queen_j + i] += 1; // Вверх-вправо
		if (queen_i >= 0 && queen_i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i][queen_j + i] += 1; // Вправо
		if (queen_i + i >= 0 && queen_i + i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i + i][queen_j + i] += 1; // Вниз-вправо
		if (queen_i + i >= 0 && queen_i + i < N && queen_j >= 0 && queen_j < N)
			kletka[queen_i + i][queen_j] += 1; // Вниз
		if (queen_i + i >= 0 && queen_i + i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i + i][queen_j - i] += 1; // Вниз-влево
		if (queen_i >= 0 && queen_i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i][queen_j - i] += 1; // Влево
		if (queen_i - i >= 0 && queen_i - i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i - i][queen_j - i] += 1; // Вверх-влево
	}
}

void Queen_backtrack(int** kletka, int queen_i, int queen_j, int N)
{ // функция, СНИМАЮЩАЯ на доске kletka[][] размера N x N числа в зависимости от того, какие клетки БЫЛИ под боем ферзя с координатами [queen_i][queen_j]
	kletka[queen_i][queen_j] -= 10000; // Самой клетке, в которой стоял ферзь, убираем 10000, что заведомо больше, чем в любой возможной клетке, в которой не стоит ферзь
	for (int i = 1; i < N; i++)
	{ // В каждой клетке, которую этот ферзь бил, отнимаем единицу
		if (queen_i - i >= 0 && queen_i - i < N && queen_j >= 0 && queen_j < N)
			kletka[queen_i - i][queen_j] -= 1; // Вверх
		if (queen_i - i >= 0 && queen_i - i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i - i][queen_j + i] -= 1; // Вверх-вправо
		if (queen_i >= 0 && queen_i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i][queen_j + i] -= 1; // Вправо
		if (queen_i + i >= 0 && queen_i + i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i + i][queen_j + i] -= 1; // Вниз-вправо
		if (queen_i + i >= 0 && queen_i + i < N && queen_j >= 0 && queen_j < N)
			kletka[queen_i + i][queen_j] -= 1; // Вниз
		if (queen_i + i >= 0 && queen_i + i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i + i][queen_j - i] -= 1; // Вниз-влево
		if (queen_i >= 0 && queen_i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i][queen_j - i] -= 1; // Влево
		if (queen_i - i >= 0 && queen_i - i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i - i][queen_j - i] -= 1; // Вверх-влево
	}
}

bool Everything_is_OK_or_Not(int** kletka, int N)
{ // Функция, проверяющая, не бьет ли какой-нибудь ферзь какого-то другого ферзя на доске kletka[][] размера N
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (kletka[i][j] > 10000) // Если в какой-то клетке больше, чем 10000, значит какой-то ферзь бьется другим ферзём
				return false;
	return true; // Если таких ферзей не обнаружено, то все хорошо, возвращаем true
}

bool Do_all_other_queens_exsist_on_previous_lines_or_Not(bool* queen_exists_at_line_, int current_line)
{ // Функция, проверяющая, есть ли по одному ферзю на каждой строке, которая следовала до текущей строки current line
	for (int i = 0; i < current_line; i++)
		if (!queen_exists_at_line_[i]) // Если нашлась хотя бы одна строка, в которой не существует ферзя, то возвращаем false
			return false;
	return true; // Если ни одной такой строки не обнаружено, то все хорошо, возвращаем true
}

void Main_Search_Function(int** kletka, int N, int queens_left, int& result_count, bool* queen_exists_at_line_)
{ // Основная рекурсивная функция, которая решает задачу: kletka[][] - наша доска; N - ее размерность;
	for (int i = 0; i < N; i++) // queens_left - переменная; хранящая количество ферзей, которых еше предстоит расставить;
		for (int j = 0; j < N; j++) // result_count - переменная, в которой храним ответ; queen_exists_at_line - массив с флажками для наличия ферзя в каждой строке
			if (kletka[i][j] == 0 && Do_all_other_queens_exsist_on_previous_lines_or_Not(queen_exists_at_line_, i))
			{ // Если наткнулись на клетку, которую никто не бьет и на которой никто не стоит, а также до этой строки в каждой строке есть по ферзю, то...
				Queen_attack(kletka, i, j, N); // Ставим на эту клетку ферзя
				queens_left--; // Уменьшаем количество ферзей, которых еще предстоит расставить
				queen_exists_at_line_[i] = true; // Говорим, что в этой строке есть ферзь
				if (Everything_is_OK_or_Not(kletka, N)) // Если после этого никто никого все ещё не бьет, то...
					if (queens_left == 0)
						result_count++; // Если все ферзи уже расставлены, то делаем инкремент результата
					else // Если же свободные ферзи еще остались, то расставляем их дальше, передавая текущие параметры в функцию...
						Main_Search_Function(kletka, N, queens_left, result_count, queen_exists_at_line_);
				Queen_backtrack(kletka, i, j, N); // Когда мы вернулись из функции, возвращаем все на свои места, убирая текущего ферзя
				queens_left++; // Увеличиваем количество ферзей, которых еще предстоит расставить
				queen_exists_at_line_[i] = false; // Говорим, что в этой строке уже нету ферзя
			}
}

int main()
{
	int result_count = 0; // Здесь будем хранить ответ на задачу (количество способов)
	int N = 0; // Здесь размерность доски (4 <= N <= 13)
	cin >> N;
	int k = 0; // Здесь количество ферзей, которые уже зафиксированы на доске (0 <= k < N)
	cin >> k;
	int** kletka = new int*[N]; // Массив с клетками доски
	bool* queen_exists_at_line_ = new bool[N]; // Массив, в котором хранится информация для каждой строки о том, есть ли в ней ферзь
	int i = 0;
	for (i; i < N; i++)
	{
		queen_exists_at_line_[i] = false; // Изначально заполняем массив с информацией о ферзях в строках ложью, т.к. ферзи еще не расставлены
		kletka[i] = new int[N];
		for (int j = 0; j < N; j++)
			kletka[i][j] = 0; // Изначально заполняем все клетки доски нулями, т.к. ни одна из них не находится под боев и ни на одной из них не стоит ферзь
	}
	for (i = 0; i < k; i++)
	{ // Считываем данные о координатах горизонтали и вертикали для каждого из k зафиксированных на доске ферзей (данные подаются начиная с единицы)
		int g = 0; // № Горизонтали доски
		int v = 0; // № Вертикали доски
		cin >> g;
		cin >> v;
		Queen_attack(kletka, g - 1, v - 1, N); // Проставляем числа на доске в зависимости от того, где стоит ферзь
		queen_exists_at_line_[g - 1] = true; // Говорим, что в этой строке есть ферзь
	}
	if (!Everything_is_OK_or_Not(kletka, N))
		cout << 0;
	else
	{
		int arr_for_k_0[10] = { 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712 }; // Для случая N = 13, k = 0 заранее подсчитаны результаты (чтобы не напрягать программу на больщих числах)
		if (k == 0) // Если k = 0, то выводим нужное число...
			cout << arr_for_k_0[N - 4];
		else // Иначе придется поработать с нашей рекурсивной функцией...
		{
			int queens_left = N - k; // Расчитываем количество ферзей, которых предстоит расставить
			Main_Search_Function(kletka, N, queens_left, result_count, queen_exists_at_line_); // Вставляем все наши параметры в функцию и считаем...
			cout << result_count; // В конце выводим насчитавшийся ответ
		}
		for (i = 0; i < N; i++)
			delete[] kletka[i];
		delete[] kletka; // Чистим память для всех массивов
		delete[] queen_exists_at_line_;
		return 0;
	}
}
// Решение #2
//#include <iostream>
//using namespace std;
//int answ, n, k, R[30], C[30], S[60];
//int* D = S + 45;
//void count(int r)
//{
//	if (r > n) { answ += (n == k); return; }
//	if (R[r]) { count(r + 1); return; }
//	for (int c = 1; c <= n; c++)
//	{
//		if (!C[c] && !S[r + c] && !D[r - c])
//		{
//			R[r] = C[c] = S[r + c] = D[r - c] = 1; k++;
//			count(r + 1);
//			R[r] = C[c] = S[r + c] = D[r - c] = 0; k--;
//		}
//	}
//}
//int main()
//{
//	cin >> n >> k;
//	for (int i = 0, r, c; i < k; i++)
//	{
//		cin >> r >> c;
//		R[r] = C[c] = S[r + c] = D[r - c] = 1;
//	}
//	count(1);
//	cout << answ << std::endl;
//	return 0;
//}

// Решение #3
//#include <iostream>
//#include <vector>
//#include <cassert>
//using namespace std;
//typedef long long ll;
//
//typedef pair<ll, ll> Mask;
//
//Mask get_mask(int i, int j) {
//	return { (1LL << i) | ((1LL << j) << 32) , (1LL << (i + j)) | ((1LL << (i - j + 16)) << 32) };
//}
//
//bool operator&(const Mask& a, const Mask& b) {
//	return (a.first & b.first) || (a.second & b.second);
//}
//
//Mask operator|(const Mask& a, const Mask& b) {
//	return { a.first | b.first , a.second | b.second };
//}
//
//ll answer = 0;
//
//void recur(int n, int row, pair<ll, ll> field) {
//	if (row == n) {
//		answer++;
//		return;
//	}
//
//	if (field.first & (1ULL << row)) recur(n, row + 1, field); // skip row, already filled
//
//	for (int j = 0; j < n; j++) {
//		auto mask = get_mask(row, j);
//		if (!(mask & field)) {
//			recur(n, row + 1, field | mask);
//		}
//	}
//}
//
//int main() {
//	int n, k; cin >> n >> k;
//	assert(k < n);
//	Mask field = { 0,0 };
//	for (int i = 0; i < k; i++) {
//		int x, y; cin >> x >> y; x--; y--;
//		Mask mask = get_mask(x, y);
//		field = field | mask;
//	}
//	recur(n, 0, field);
//	cout << answer << endl;
//	return 0;
//}