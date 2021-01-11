#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int N = 27; // ������ ��������
char Alphabet[N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ' };

string Shift_Cipher(int key, string in)
{ // ���� ������ (�� ���� �����)
	string crypt_result = "";
	for (unsigned int i = 0; i < in.size(); i++)
	{
		int new_crypt_letter_ind = in[i] - 65; // �������� ������� ASCII �������� �� ������ ����� 65 (� ����� 'A' ����� 65), ����� �������� ������ � ��������
		if (in[i] == ' ')
			new_crypt_letter_ind = 26; // ���� ������� ������, �� �������, ��� ��� 27-�� ������ 26
		new_crypt_letter_ind += key; // ���������� ����
		new_crypt_letter_ind %= N; // ����� ������� �� ������ ����� ���� � ��������
		crypt_result += Alphabet[new_crypt_letter_ind];
	}
	return crypt_result;
}

string Shift_Decipher(int key, string in)
{ // ����������� ����� ������ (�� ���� �����)
	string decrypt_result = "";
	for (unsigned int i = 0; i < in.size(); i++)
	{
		int new_crypt_letter_ind = in[i] - 65; // �������� ������� ASCII �������� �� ������ ����� 65 (� ����� 'A' ����� 65), ����� �������� ������ � ��������
		if (in[i] == ' ')
			new_crypt_letter_ind = 26; // ���� ������� ������, �� �������, ��� ��� 27-�� ������ 26
		new_crypt_letter_ind -= key; // �������� ����
		new_crypt_letter_ind %= N;
		while (new_crypt_letter_ind < 0)
			new_crypt_letter_ind += N; // ���������� ������ ��������, ���� ������ �� ������ �������������
		decrypt_result += Alphabet[new_crypt_letter_ind];
	}
	return decrypt_result;
}

string Simple_Replacement_Cipher(string key, string in)
{ // ���� ������� ������ (�� ���� ���� �� 27 �������� - ���� ��������)
	string crypt_result = "";
	char New_Alphabet[N]; // ����� �������, ��������� �� ��������� �� �����
	for (int i = 0; i < N; i++)
		New_Alphabet[i] = key[i];
	for (unsigned int i = 0; i < in.size(); i++)
	{
		int new_crypt_letter_ind = in[i] - 65; // �������� ������� ASCII �������� �� ������ ����� 65 (� ����� 'A' ����� 65), ����� �������� ������ � ��������
		if (in[i] == ' ')
			new_crypt_letter_ind = 26; // ���� ������� ������, �� �������, ��� ��� 27-�� ������ 26
		crypt_result += New_Alphabet[new_crypt_letter_ind]; // ������� ������ ������ ��������, ��������� ������ ���� �� ����� ��� ������� ��������
	}
	return crypt_result;
}
// ������ ����� NBCDWF HIZKLMAOPQRSTUVEXYGJ
string Simple_Replacement_Decipher(string key, string in)
{ // ����������� ����� ������� ������ (�� ���� ���� �� 27 �������� - ���� ��������)
	string decrypt_result = "";
	char New_Alphabet[N]; // ����� �������, ��������� �� ��������� �� �����
	for (int i = 0; i < N; i++)
		New_Alphabet[i] = key[i];
	for (unsigned int i = 0; i < in.size(); i++)
		for (int j = 0; j < N; j++)
			if (in[i] == New_Alphabet[j])
			{
				decrypt_result += Alphabet[j];
				break;
			}
	return decrypt_result;
}

int Matrix_Determinant(pair<pair<int, int>, pair<int, int>> matrix)
{ // ���� ������������ ������� ����� ����� 0, �� ����������� �������� ����� ����������
	return matrix.first.first*matrix.second.second - matrix.first.second*matrix.second.first;
}

string Hill_Cipher(string key, string in)
{ // ���� ����� (https://habr.com/ru/post/332714/) (�� ���� 4 ������� �� ��������, ��� ������������ ������� �������� ���� �������� �� ������ N)
	string crypt_result = "";
	for (int i = 0; i < 4; i++)
		if (key[i] == ' ')
			key[i] = 26; // ���� ������, �� ����������� 27-�� ������ 26
		else
			key[i] -= 65; // ����� ��� �����-�� �����, �������� 65, ����� ���� �� ���� �� 25
	pair<pair<int, int>, pair<int, int>> key_matrix = { make_pair(key[0], key[1]), make_pair(key[2], key[3]) }; // ������� 2x2
	int det = Matrix_Determinant(key_matrix);
	if (det == 0)
		return "Warning, the determinant of key metrix is zero!!!";
	if (det % 3 == 0) // ��� �����, ��� ������������ ������� ����� �� ��� ������ ���, ����� �� ����� ����� �������� �� ������ 27
		return "Warning, the determinant is a multiple of three, the key does not fit!!!";
	for (unsigned int i = 0; i < in.size(); i++)
		if (in[i] == ' ')
			in[i] = 26; // ���� ������, �� ����������� 27-�� ������ 26
		else
			in[i] -= 65; // ����� ��� �����-�� �����, �������� 65, ����� ���� �� ���� �� 25
	vector<pair<int, int>> block; // ������� ������ ���
	for (unsigned int i = 0; i < in.size() - 1; i += 2) // ��������� �������� ����� �� ����� �� n = 2 ������� ������
		block.push_back(make_pair(in[i], in[i + 1])); // ���� � ����� �� ������ �������, ������� ������
	if (in.size() % 2 == 1) // ���� ����� �������� � �������� ������ ��������, ��...
		block.push_back(make_pair(in[in.size() - 1], 26)); // ������� �������������� ���� � ��������� �������� � ��������
	for (unsigned int i = 0; i < block.size(); i++)
	{
		pair<int, int> new_crypt_pair = make_pair(-1, -1);
		new_crypt_pair.first = block[i].first*key_matrix.first.first + block[i].second*key_matrix.second.first; // ���� �������� �� ������ �������
		new_crypt_pair.first %= N; // ����� ������� �� N = 27
		crypt_result += Alphabet[new_crypt_pair.first];
		new_crypt_pair.second = block[i].first*key_matrix.first.second + block[i].second*key_matrix.second.second; // ���� �������� �� ������ �������
		new_crypt_pair.second %= N; // ����� ������� �� N = 27
		crypt_result += Alphabet[new_crypt_pair.second];
	}
	return crypt_result;
}

int InverseMod(int x, int N)
{ // �����, �������� ����� x �� ������ N
	if (N % x == 0)
		return 1;
	else
		return N - InverseMod(N % x, x) * N / x;
}

void InverseMatrix(pair<pair<int, int>, pair<int, int>> &new_matrix, pair<pair<int, int>, pair<int, int>> default_matrix, int reverse_det)
{ // ����� �������� ������� �� ������ 27
	// ���������� � ����� �������: �����������������, � ��������������� ������������, ������� ������� �������� �������, ���������� �� �������� ������������ � ������ �� ������ 27
	new_matrix.first.first = (default_matrix.second.second * reverse_det) % N;
	new_matrix.first.second = (-default_matrix.first.second * reverse_det) % N;
	new_matrix.second.first = (-default_matrix.second.first * reverse_det) % N;
	new_matrix.second.second = (default_matrix.first.first * reverse_det) % N;
}

string Hill_Decipher(string key, string in)
{ // ����������� ����� ����� (https://habr.com/ru/post/332714/) (�� ���� 4 ������� �� ��������, ��� ������������ ������� �������� ���� �������� �� ������ N)
	string decrypt_result = "";
	for (int i = 0; i < 4; i++)
		if (key[i] == ' ')
			key[i] = 26; // ���� ������, �� ����������� 27-�� ������ 26
		else
			key[i] -= 65; // ����� ��� �����-�� �����, �������� 65, ����� ���� �� ���� �� 25
	pair<pair<int, int>, pair<int, int>> key_matrix = { make_pair(key[0], key[1]), make_pair(key[2], key[3]) }; // ������� 2x2
	int det = Matrix_Determinant(key_matrix); // ���������� ������������ ������� �����
	if (det == 0)
		return "Warning, the determinant of key metrix is zero!!!";
	if (det % 3 == 0) // ��� �����, ��� ������������ ������� ����� �� ��� ������ ���, ����� �� ����� ����� �������� �� ������ 27
		return "Warning, the determinant is a multiple of three, the key does not fit!!!";
	for (unsigned int i = 0; i < in.size(); i++)
		if (in[i] == ' ')
			in[i] = 26; // ���� ������, �� ����������� 27-�� ������ 26
		else
			in[i] -= 65; // ����� ��� �����-�� �����, �������� 65, ����� ���� �� ���� �� 25
	vector<pair<int, int>> block; // ������� ������ ���
	for (unsigned int i = 0; i < in.size() - 1; i += 2) // ��������� �������� ����� �� ����� �� n = 2 ������� ������
		block.push_back(make_pair(in[i], in[i + 1])); // ���� � ����� �� ������ �������, ������� ������
	if (in.size() % 2 == 1) // ���� ����� �������� � �������� ������ ��������, ��...
		block.push_back(make_pair(in[in.size() - 1], 26)); // ������� �������������� ���� � ��������� �������� � ��������
	det %= N;
	while (det < 0)
		det += N;
	int reverse_det = InverseMod(det, N) % N; // �������� ������������ ������� � ������ �� ������ 27
	pair<pair<int, int>, pair<int, int>> key_inverse_matrix = { make_pair(0, 0), make_pair(0, 0) }; // ���� ������� �������, �������� ������� �����
	InverseMatrix(key_inverse_matrix, key_matrix, reverse_det);
	for (unsigned int i = 0; i < block.size(); i++)
	{
		pair<int, int> new_decrypt_pair = make_pair(-1, -1);
		new_decrypt_pair.first = block[i].first*key_inverse_matrix.first.first + block[i].second*key_inverse_matrix.second.first; // ���� �������� �� ������ �������
		new_decrypt_pair.first %= N; // ����� ������� �� N = 27
		while (new_decrypt_pair.first < 0)
			new_decrypt_pair.first += N; // ���������� ������ ��������, ���� ������ �� ������ �������������
		decrypt_result += Alphabet[new_decrypt_pair.first];
		new_decrypt_pair.second = block[i].first*key_inverse_matrix.first.second + block[i].second*key_inverse_matrix.second.second; // ���� �������� �� ������ �������
		new_decrypt_pair.second %= N; // ����� ������� �� N = 27
		while (new_decrypt_pair.second < 0)
			new_decrypt_pair.second += N; // ���������� ������ ��������, ���� ������ �� ������ �������������
		decrypt_result += Alphabet[new_decrypt_pair.second];
	}
	return decrypt_result;
}

int main()
{
	string key = ""; // ����
	ifstream f_key("key.txt");
	getline(f_key, key);
	f_key.close();
	string in = ""; // �������� �����
	ifstream fin("in.txt");
	getline(fin, in);
	fin.close();
	ofstream fout_cr("crypt.txt");
	ofstream fout_dcr("decrypt.txt");
	string crypt_text = ""; // ������������� �����
	string decrypt_text = ""; // �������������� �����
	cout << "Choose the cipher algorthm:\n1) Shift's Cipher\n2) Simple Replacement's Chipher\n3) Hill's Chipher" << endl;
	int num = 0;
	cin >> num;
	switch (num)
	{
	case 1:
		crypt_text = Shift_Cipher(atoi(key.c_str()), in);
		fout_cr << crypt_text;
		decrypt_text = Shift_Decipher(atoi(key.c_str()), crypt_text);
		fout_dcr << decrypt_text;
		break;
	case 2:
		crypt_text = Simple_Replacement_Cipher(key, in);
		fout_cr << crypt_text;
		decrypt_text = Simple_Replacement_Decipher(key, crypt_text);
		fout_dcr << decrypt_text;
		break;
	case 3:
		crypt_text = Hill_Cipher(key, in);
		fout_cr << crypt_text;
		decrypt_text = Hill_Decipher(key, crypt_text);
		fout_dcr << decrypt_text;
		break;
	default:
		cout << "Incorrect choice!" << endl;
		fout_cr.close();
		fout_dcr.close();
		return -1;
	}
	fout_cr.close();
	fout_dcr.close();
	return 0;
}