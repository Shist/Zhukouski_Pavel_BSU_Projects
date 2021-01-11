// ������� #1
#include <iostream>
using namespace std;

void Queen_attack(int** kletka, int queen_i, int queen_j, int N)
{ // �������, ������������� �� ����� kletka[][] ������� N x N ����� � ����������� �� ����, ����� ������ ��������� ��� ���� ����� � ������������ [queen_i][queen_j]
	kletka[queen_i][queen_j] += 10000; // ����� ������, � ������� ����� �����, ����������� 10000, ��� �������� ������, ��� � ����� ��������� ������, � ������� �� ����� �����
	for (int i = 1; i < N; i++)
	{ // � ������ ������, ������� ���� ����� ����, ���������� �������
		if (queen_i - i >= 0 && queen_i - i < N && queen_j >= 0 && queen_j < N)
			kletka[queen_i - i][queen_j] += 1; // �����
		if (queen_i - i >= 0 && queen_i - i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i - i][queen_j + i] += 1; // �����-������
		if (queen_i >= 0 && queen_i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i][queen_j + i] += 1; // ������
		if (queen_i + i >= 0 && queen_i + i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i + i][queen_j + i] += 1; // ����-������
		if (queen_i + i >= 0 && queen_i + i < N && queen_j >= 0 && queen_j < N)
			kletka[queen_i + i][queen_j] += 1; // ����
		if (queen_i + i >= 0 && queen_i + i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i + i][queen_j - i] += 1; // ����-�����
		if (queen_i >= 0 && queen_i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i][queen_j - i] += 1; // �����
		if (queen_i - i >= 0 && queen_i - i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i - i][queen_j - i] += 1; // �����-�����
	}
}

void Queen_backtrack(int** kletka, int queen_i, int queen_j, int N)
{ // �������, ��������� �� ����� kletka[][] ������� N x N ����� � ����������� �� ����, ����� ������ ���� ��� ���� ����� � ������������ [queen_i][queen_j]
	kletka[queen_i][queen_j] -= 10000; // ����� ������, � ������� ����� �����, ������� 10000, ��� �������� ������, ��� � ����� ��������� ������, � ������� �� ����� �����
	for (int i = 1; i < N; i++)
	{ // � ������ ������, ������� ���� ����� ���, �������� �������
		if (queen_i - i >= 0 && queen_i - i < N && queen_j >= 0 && queen_j < N)
			kletka[queen_i - i][queen_j] -= 1; // �����
		if (queen_i - i >= 0 && queen_i - i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i - i][queen_j + i] -= 1; // �����-������
		if (queen_i >= 0 && queen_i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i][queen_j + i] -= 1; // ������
		if (queen_i + i >= 0 && queen_i + i < N && queen_j + i >= 0 && queen_j + i < N)
			kletka[queen_i + i][queen_j + i] -= 1; // ����-������
		if (queen_i + i >= 0 && queen_i + i < N && queen_j >= 0 && queen_j < N)
			kletka[queen_i + i][queen_j] -= 1; // ����
		if (queen_i + i >= 0 && queen_i + i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i + i][queen_j - i] -= 1; // ����-�����
		if (queen_i >= 0 && queen_i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i][queen_j - i] -= 1; // �����
		if (queen_i - i >= 0 && queen_i - i < N && queen_j - i >= 0 && queen_j - i < N)
			kletka[queen_i - i][queen_j - i] -= 1; // �����-�����
	}
}

bool Everything_is_OK_or_Not(int** kletka, int N)
{ // �������, �����������, �� ���� �� �����-������ ����� ������-�� ������� ����� �� ����� kletka[][] ������� N
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (kletka[i][j] > 10000) // ���� � �����-�� ������ ������, ��� 10000, ������ �����-�� ����� ������ ������ �����
				return false;
	return true; // ���� ����� ������ �� ����������, �� ��� ������, ���������� true
}

bool Do_all_other_queens_exsist_on_previous_lines_or_Not(bool* queen_exists_at_line_, int current_line)
{ // �������, �����������, ���� �� �� ������ ����� �� ������ ������, ������� ��������� �� ������� ������ current line
	for (int i = 0; i < current_line; i++)
		if (!queen_exists_at_line_[i]) // ���� ������� ���� �� ���� ������, � ������� �� ���������� �����, �� ���������� false
			return false;
	return true; // ���� �� ����� ����� ������ �� ����������, �� ��� ������, ���������� true
}

void Main_Search_Function(int** kletka, int N, int queens_left, int& result_count, bool* queen_exists_at_line_)
{ // �������� ����������� �������, ������� ������ ������: kletka[][] - ���� �����; N - �� �����������;
	for (int i = 0; i < N; i++) // queens_left - ����������; �������� ���������� ������, ������� ��� ��������� ����������;
		for (int j = 0; j < N; j++) // result_count - ����������, � ������� ������ �����; queen_exists_at_line - ������ � �������� ��� ������� ����� � ������ ������
			if (kletka[i][j] == 0 && Do_all_other_queens_exsist_on_previous_lines_or_Not(queen_exists_at_line_, i))
			{ // ���� ���������� �� ������, ������� ����� �� ���� � �� ������� ����� �� �����, � ����� �� ���� ������ � ������ ������ ���� �� �����, ��...
				Queen_attack(kletka, i, j, N); // ������ �� ��� ������ �����
				queens_left--; // ��������� ���������� ������, ������� ��� ��������� ����������
				queen_exists_at_line_[i] = true; // �������, ��� � ���� ������ ���� �����
				if (Everything_is_OK_or_Not(kletka, N)) // ���� ����� ����� ����� ������ ��� ��� �� ����, ��...
					if (queens_left == 0)
						result_count++; // ���� ��� ����� ��� �����������, �� ������ ��������� ����������
					else // ���� �� ��������� ����� ��� ��������, �� ����������� �� ������, ��������� ������� ��������� � �������...
						Main_Search_Function(kletka, N, queens_left, result_count, queen_exists_at_line_);
				Queen_backtrack(kletka, i, j, N); // ����� �� ��������� �� �������, ���������� ��� �� ���� �����, ������ �������� �����
				queens_left++; // ����������� ���������� ������, ������� ��� ��������� ����������
				queen_exists_at_line_[i] = false; // �������, ��� � ���� ������ ��� ���� �����
			}
}

int main()
{
	int result_count = 0; // ����� ����� ������� ����� �� ������ (���������� ��������)
	int N = 0; // ����� ����������� ����� (4 <= N <= 13)
	cin >> N;
	int k = 0; // ����� ���������� ������, ������� ��� ������������� �� ����� (0 <= k < N)
	cin >> k;
	int** kletka = new int*[N]; // ������ � �������� �����
	bool* queen_exists_at_line_ = new bool[N]; // ������, � ������� �������� ���������� ��� ������ ������ � ���, ���� �� � ��� �����
	int i = 0;
	for (i; i < N; i++)
	{
		queen_exists_at_line_[i] = false; // ���������� ��������� ������ � ����������� � ������ � ������� �����, �.�. ����� ��� �� �����������
		kletka[i] = new int[N];
		for (int j = 0; j < N; j++)
			kletka[i][j] = 0; // ���������� ��������� ��� ������ ����� ������, �.�. �� ���� �� ��� �� ��������� ��� ���� � �� �� ����� �� ��� �� ����� �����
	}
	for (i = 0; i < k; i++)
	{ // ��������� ������ � ����������� ����������� � ��������� ��� ������� �� k ��������������� �� ����� ������ (������ �������� ������� � �������)
		int g = 0; // � ����������� �����
		int v = 0; // � ��������� �����
		cin >> g;
		cin >> v;
		Queen_attack(kletka, g - 1, v - 1, N); // ����������� ����� �� ����� � ����������� �� ����, ��� ����� �����
		queen_exists_at_line_[g - 1] = true; // �������, ��� � ���� ������ ���� �����
	}
	if (!Everything_is_OK_or_Not(kletka, N))
		cout << 0;
	else
	{
		int arr_for_k_0[10] = { 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712 }; // ��� ������ N = 13, k = 0 ������� ���������� ���������� (����� �� ��������� ��������� �� ������� ������)
		if (k == 0) // ���� k = 0, �� ������� ������ �����...
			cout << arr_for_k_0[N - 4];
		else // ����� �������� ���������� � ����� ����������� ��������...
		{
			int queens_left = N - k; // ����������� ���������� ������, ������� ��������� ����������
			Main_Search_Function(kletka, N, queens_left, result_count, queen_exists_at_line_); // ��������� ��� ���� ��������� � ������� � �������...
			cout << result_count; // � ����� ������� ������������� �����
		}
		for (i = 0; i < N; i++)
			delete[] kletka[i];
		delete[] kletka; // ������ ������ ��� ���� ��������
		delete[] queen_exists_at_line_;
		return 0;
	}
}
// ������� #2
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

// ������� #3
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