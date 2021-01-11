#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

unsigned long long iteration_count = 1; // ��� ���������� ����� ������������ �������� �� ����� ���������� ������

const int N = 26; // ������ ��������
string need_key = "HARR";
char Alphabet[N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };


double English_Alphabet_Repetition_Rate(vector<string> text)
{ // �������, ������������, ��������� ������ ��� ��� ���� ����� ����� �� ������� ����� �� ����������� �����
	double differene = 0.0; // � ���� ���������� ����� �������� ����� �������
	// ����� ������ ��� (������, ��� ���������� � ������)
	int letters_num = 0; // ����� ���������� �������� � ������
	vector<double> Letters_amount = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	for (size_t k = 0; k < text.size(); k++) // ��� ������ ������ ������
	{
		for (size_t i = 0; i < text[k].size(); i++, letters_num++) // ��� ������� ������� ������
			if (text[k][i] == 'A')
				Letters_amount[0]++;
			else if (text[k][i] == 'B')
				Letters_amount[1]++;
			else if (text[k][i] == 'C')
				Letters_amount[2]++;
			else if (text[k][i] == 'D')
				Letters_amount[3]++;
			else if (text[k][i] == 'E')
				Letters_amount[4]++;
			else if (text[k][i] == 'F')
				Letters_amount[5]++;
			else if (text[k][i] == 'G')
				Letters_amount[6]++;
			else if (text[k][i] == 'H')
				Letters_amount[7]++;
			else if (text[k][i] == 'I')
				Letters_amount[8]++;
			else if (text[k][i] == 'J')
				Letters_amount[9]++;
			else if (text[k][i] == 'K')
				Letters_amount[10]++;
			else if (text[k][i] == 'L')
				Letters_amount[11]++;
			else if (text[k][i] == 'M')
				Letters_amount[12]++;
			else if (text[k][i] == 'N')
				Letters_amount[13]++;
			else if (text[k][i] == 'O')
				Letters_amount[14]++;
			else if (text[k][i] == 'P')
				Letters_amount[15]++;
			else if (text[k][i] == 'Q')
				Letters_amount[16]++;
			else if (text[k][i] == 'R')
				Letters_amount[17]++;
			else if (text[k][i] == 'S')
				Letters_amount[18]++;
			else if (text[k][i] == 'T')
				Letters_amount[19]++;
			else if (text[k][i] == 'U')
				Letters_amount[20]++;
			else if (text[k][i] == 'V')
				Letters_amount[21]++;
			else if (text[k][i] == 'W')
				Letters_amount[22]++;
			else if (text[k][i] == 'X')
				Letters_amount[23]++;
			else if (text[k][i] == 'Y')
				Letters_amount[24]++;
			else if (text[k][i] == 'Z')
				Letters_amount[25]++;
		if (text[k].find("ING") != -1)
			differene -= 0.1;
		if (text[k].find("TION") != -1)
			differene -= 0.1;
		if (text[k].find("THE") != -1)
			differene -= 0.1;
		if (text[k].find("IES") != -1)
			differene -= 0.1;
		if (text[k].find("DONT") != -1)
			differene -= 0.1;
		if (text[k].find("JUST") != -1)
			differene -= 0.1;
		if (text[k].find("AND") != -1)
			differene -= 0.1;
		if (text[k].find("YOU") != -1)
			differene -= 0.1;
		if (text[k].find("NOW") != -1)
			differene -= 0.1;
	}
	for (int i = 0; i < 26; i++) // ��� ������ �����
		Letters_amount[i] = Letters_amount[i] / letters_num; // ����� � ���������� � ������ �� ����� ����� ����, ����� ��������� �������
	// ���� �������� ������ �� �������������������� �������������� ���� � ���������� �����
	vector<double> Frequency_of_Occurrence_in_English = // ������� ������������� ���� � ���������� ��������
	{ 0.081, 0.014, 0.027, 0.038,  0.13, 0.029, 0.02, 0.052, 0.063, 0.0013, 0.004, 0.034, 0.025, 0.071,
		0.079, 0.019, 0.0011, 0.068, 0.061, 0.105, 0.024, 0.009, 0.015, 0.0015, 0.019, 0.0007 };
	for (int i = 0; i < 26; i++) // ���������� �� ������ ������� ����
		differene += abs(Frequency_of_Occurrence_in_English[i] - Letters_amount[i]);
	return differene; // ������� ���������� ����� ������� (������ ��� ���������� �� 0.4 �� 0.7)
}

vector<string> Shift_Decipher(int key, vector<string> in)
{ // ����������� ����� ������ (�� ���� �����)
	vector<string> decrypt_result(in.size());
	for (size_t k = 0; k < in.size(); k++)
	{
		string decrypt_str = "";
		for (unsigned int i = 0; i < in[k].size(); i++)
		{
			int new_crypt_letter_ind = in[k][i] - 65; // �������� ������� ASCII �������� �� ������ ����� 65 (� ����� 'A' ����� 65), ����� �������� ������ � ��������
			new_crypt_letter_ind -= key; // �������� ����
			new_crypt_letter_ind %= N;
			while (new_crypt_letter_ind < 0)
				new_crypt_letter_ind += N; // ���������� ������ ��������, ���� ������ �� ������ �������������
			decrypt_str += Alphabet[new_crypt_letter_ind];
		}
		decrypt_result[k] = decrypt_str;
	}
	return decrypt_result;
}

void Hack_Shift_Cipher(ofstream &fout_key, ofstream &fout, vector<string> CipheredText)
{ // ����� ����� ������ (������� ������ �� 1 �� 27)

	// ���� ����� ������� ������ ��� �����
	//int used_key = 0; // ����, ������� �������� �������� ��� �����������
	//vector<string> UsedText(CipheredText.size()); // �����, ������� �������� �������� ��� ����������
	//for (int key = 1; key <= N; key++)
	//{
	//	cout << "Hacking Caesar's Cipher... Checking key number: " << key << endl;
	//	vector<string> temp_UsedText; // ������� ������ ������, ������� ��� ����������
	//	temp_UsedText = Shift_Decipher(key, CipheredText);
	//	UsedText = temp_UsedText;
	//	used_key = key; // ����� ���������� ����, �� �������� ���� ����� ��� ����������
	//	fout << "KEY " << used_key << ":" << endl;
	//	fout << UsedText[0];
	//	for (size_t k = 1; k < UsedText.size(); k++)
	//		fout << endl << UsedText[k];
	//	fout << endl;
	//}

	int used_key = 0; // ����, ������� �������� �������� ��� �����������
	vector<string> UsedText(CipheredText.size()); // �����, ������� �������� �������� ��� ����������
	for (int key = 1; key <= N; key++)
	{
		cout << "Hacking Caesar's Cipher... Checking key number: " << key << endl;
		vector<string> temp_UsedText; // ������� ������ ������, ������� ��� ����������
		temp_UsedText = Shift_Decipher(key, CipheredText);
		if (English_Alphabet_Repetition_Rate(temp_UsedText) < English_Alphabet_Repetition_Rate(UsedText) || key == 1)
		{ // ���� ������� �����, ������� ������ ����� �� ��������� �����, �� ���������� ���
			UsedText = temp_UsedText;
			used_key = key; // ����� ���������� ����, �� �������� ���� ����� ��� ����������
		}
	}
	fout_key << used_key;
	fout << UsedText[0];
	for (size_t k = 1; k < UsedText.size(); k++)
		fout << endl << UsedText[k];
	// ������ ������ (����: 7)
	/* ������� ������
AAVUPNOAPTNVUUHOHCLTFZLSMHYLHSNVVKAPTL
PMLLSHSPCLHUKAOLDVYSKPSSABYUPAPUZPKLVBAFLHO
HUKMSVHAPUNHYVBUKPULJZAHZF
ZVKVUAZAVWTLUVDKVUAZAVWTL
JHBZLPTOHCPUNHNVVKAPTLOHCPUNHNVVKAPTL
PTHZOVVAPUNZAHYSLHWPUNAOYVBNOAOLZRF
SPRLHAPNLYKLMFPUNAOLSHDZVMNYHCPAF
PTHYHJPUNJHYWHZZPUNIFSPRLSHKFNVKPCH
PTNVUUHNVNVNV
AOLYLZUVZAVWWPUNTL
PTIBYUPUAOYVBNOAOLZRFFLHO
ADVOBUKYLKKLNYLLZ
AOHAZDOFAOLFJHSSTLTPZALYMHOYLUOLPA
PTAYHCSPUNHAAOLZWLLKVMSPNOA
PDHUUHTHRLHZBWLYZVUPJTHUVBAVMFVB
KVUAZAVWTLUVDPTOHCPUNZBJOHNVVKAPTL
PTOHCPUNHIHSS
KVUAZAVWTLUVD
PMFVBDHUUHOHCLHNVVKAPTLQBZANPCLTLHJHSS
KVUAZAVWTLUVDJHBZLPTOHCPUNHNVVKAPTL
KVUAZAVWTLUVDFLZPTOHCPUHNVVKAPTL
PKVUADHUAAVZAVWHAHSS
FLHOPTHYVJRLAZOPWVUTFDHFAVTHYZ
VUHJVSSPZPVUJVBYZL
PHTHZHALSSPALPTVBAVMJVUAYVS
PHTHZLETHJOPULYLHKFAVYLSVHK
SPRLHUHAVTIVTIHIVBAAV
VOVOVOVOVOLEWSVKL
PTIBYUPUAOYVBNOAOLZRFFLHO
ADVOBUKYLKKLNYLLZ
AOHAZDOFAOLFJHSSTLTPZALYMHOYLUOLPA
PTAYHCSPUNHAAOLZWLLKVMSPNOA
PDHUUHTHRLHZBWLYZVUPJDVTHUVMFVB
KVUAZAVWTLKVUAZAVWTL
KVUAZAVWTLOLFOLFOLF
KVUAZAVWTLKVUAZAVWTL
VVOVVOVVOPSPRLPA
KVUAZAVWTLKVUAZAVWTL
OHCLHNVVKAPTLNVVKAPTL
KVUAZAVWTLKVUAZAVWTLHO
VOFLHO
HSYPNOA
VOPTIBYUPUAOYVBNOAOLZRFFLHO
ADVOBUKYLKKLNYLLZ
AOHAZDOFAOLFJHSSTLTPZALYMHOYLUOLPA
PTAYHCSPUNHAAOLZWLLKVMSPNOA
PDHUUHTHRLHZBWLYZVUPJTHUVBAVMFVB
KVUAZAVWTLUVDPTOHCPUNZBJOHNVVKAPTL
PTOHCPUNHIHSS
KVUAZAVWTLUVD
PMFVBDHUUHOHCLHNVVKAPTLDVVO
QBZANPCLTLHJHSSHSYPNOA
KVUAZAVWTLUVDJHBZLPTOHCPUNHNVVKAPTLFLHOFLHO
KVUAZAVWTLUVDFLZPTOHCPUHNVVKAPTL
PKVUADHUAAVZAVWHAHSS
SHKHKHKHKHHO
KHKHKHOHH
OHKHKHOHOHOHHH
OHKHKHHOHKHKHHHH
VVOVVOVVO*/
	// �����
	/*
TTONIGHTIMGONNAHAVEMYSELFAREALGOODTIME
IFEELALIVEANDTHEWORLDILLTURNITINSIDEOUTYEAH
ANDFLOATINGAROUNDINECSTASY
SODONTSTOPMENOWDONTSTOPME
CAUSEIMHAVINGAGOODTIMEHAVINGAGOODTIME
IMASHOOTINGSTARLEAPINGTHROUGHTHESKY
LIKEATIGERDEFYINGTHELAWSOFGRAVITY
IMARACINGCARPASSINGBYLIKELADYGODIVA
IMGONNAGOGOGO
THERESNOSTOPPINGME
IMBURNINTHROUGHTHESKYYEAH
TWOHUNDREDDEGREES
THATSWHYTHEYCALLMEMISTERFAHRENHEIT
IMTRAVLINGATTHESPEEDOFLIGHT
IWANNAMAKEASUPERSONICMANOUTOFYOU
DONTSTOPMENOWIMHAVINGSUCHAGOODTIME
IMHAVINGABALL
DONTSTOPMENOW
IFYOUWANNAHAVEAGOODTIMEJUSTGIVEMEACALL
DONTSTOPMENOWCAUSEIMHAVINGAGOODTIME
DONTSTOPMENOWYESIMHAVINAGOODTIME
IDONTWANTTOSTOPATALL
YEAHIMAROCKETSHIPONMYWAYTOMARS
ONACOLLISIONCOURSE
IAMASATELLITEIMOUTOFCONTROL
IAMASEXMACHINEREADYTORELOAD
LIKEANATOMBOMBABOUTTO
OHOHOHOHOHEXPLODE
IMBURNINTHROUGHTHESKYYEAH
TWOHUNDREDDEGREES
THATSWHYTHEYCALLMEMISTERFAHRENHEIT
IMTRAVLINGATTHESPEEDOFLIGHT
IWANNAMAKEASUPERSONICWOMANOFYOU
DONTSTOPMEDONTSTOPME
DONTSTOPMEHEYHEYHEY
DONTSTOPMEDONTSTOPME
OOHOOHOOHILIKEIT
DONTSTOPMEDONTSTOPME
HAVEAGOODTIMEGOODTIME
DONTSTOPMEDONTSTOPMEAH
OHYEAH
ALRIGHT
OHIMBURNINTHROUGHTHESKYYEAH
TWOHUNDREDDEGREES
THATSWHYTHEYCALLMEMISTERFAHRENHEIT
IMTRAVLINGATTHESPEEDOFLIGHT
IWANNAMAKEASUPERSONICMANOUTOFYOU
DONTSTOPMENOWIMHAVINGSUCHAGOODTIME
IMHAVINGABALL
DONTSTOPMENOW
IFYOUWANNAHAVEAGOODTIMEWOOH
JUSTGIVEMEACALLALRIGHT
DONTSTOPMENOWCAUSEIMHAVINGAGOODTIMEYEAHYEAH
DONTSTOPMENOWYESIMHAVINAGOODTIME
IDONTWANTTOSTOPATALL
LADADADADAAH
DADADAHAA
HADADAHAHAHAAA
HADADAAHADADAAAA
OOHOOHOOH
	*/
}

// ������ ����� ABCDEFGHIJKLMNOPQRSTUVWX ZY
vector<string> Simple_Replacement_Decipher(string key, vector<string> in)
{ // ����������� ����� ������� ������ (�� ���� ���� �� 27 �������� - ���� ��������)
	vector<string> decrypt_result(in.size());
	char New_Alphabet[N]; // ����� �������, ��������� �� ��������� �� �����
	for (int i = 0; i < N; i++)
		New_Alphabet[i] = key[i];
	for (size_t k = 0; k < in.size(); k++)
	{
		string decrypt_str = "";
		for (unsigned int i = 0; i < in[k].size(); i++)
			for (int j = 0; j < N; j++)
				if (in[k][i] == New_Alphabet[j])
				{
					decrypt_str += Alphabet[j];
					break;
				}
		decrypt_result[k] = decrypt_str;
	}
	return decrypt_result;
}

void Hack_Simple_Replacement_Cipher(ofstream &fout_key, ofstream &fout, vector<string> CipheredText)
{ // ����� ����� ������� ������ (������� ������ �� ����� ����� �������� �����, � ����� ��������������� ����� �����)
	vector<string> MainText; // �������� ����, ������� �� ����� ������ �� �����������
	vector<string> temp_UsedText; // ������� ������ ������, ������� ��� ����������
	string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	do { // ���� ����, ������� ����������� ����� � ����� ����� ������� �� ������� ����� ����������� �����
		cout << iteration_count << ") Hacking Simple Replacement's Cipher... Checking key number: " << key << endl;
		temp_UsedText = Simple_Replacement_Decipher(key, CipheredText);
		if (English_Alphabet_Repetition_Rate(temp_UsedText) < 0.3) // ����� ����� �������������� "����������� �������� � ���������� ������", � �������� 0.3)
		{ // ���� ������� �����, ������� ������ ����� �� ��������� �����, �� ���������� ���
			MainText = temp_UsedText;
			cout << iteration_count << ") Main key has chosen: " << key << endl << "Trying to change it for correct key..." << endl;
			break; // ������� �� �����, �.�. �� ��� ����� ����� ����� ������� ����
		}
		iteration_count++;
	} while (std::next_permutation(key.begin(), key.end()));
	// ������ ������� ������ ������������ �� ��������� �����, ����� �������� ����������
	double previous_difference = English_Alphabet_Repetition_Rate(MainText); // ������� �������, ������� ��� ������� ������� ��������� �� ���������� ����
	double new_difference = 0.0; // ����� �������, ������� ��� ������ ���� ������� ��������� �� ���������� ����
	int k = 0;
	cout << "Main key have chosen. Starting to imporove that key..." << endl;
	for (;; k++) // ���� ����������� ��������� �� ���������, ������� ������ ������������
	{ // ����� �������������� ���� �� ��� ���, ���� ����������� ������� � ���������� ����� �� ������ ����������
		string new_key = key; // ����� ����� ������� ����� ����
		srand((unsigned int)time(0)); // �������� ������ ��� ����� � �����
		int random_first_ind = rand() % (N - 1); // ������ ��������� ������ �� �����
		int random_second_ind = rand() % (N - 1); // ������ ��������� ������ �� �����
		char temp_letter = new_key[random_first_ind];
		new_key[random_second_ind] = new_key[random_first_ind]; // �� ������ ���������� ������
		new_key[random_first_ind] = temp_letter; // � ������ ���������� ������
		temp_UsedText = Simple_Replacement_Decipher(new_key, CipheredText); // ��������� �����������
		if (English_Alphabet_Repetition_Rate(temp_UsedText) < English_Alphabet_Repetition_Rate(MainText))
		{ // ���� ���� ����� ��� ������ ����� �� ���������� ����, ��� ����������, ��...
			k = 0;
			cout << "New main key have chosen (old key improved), k = 0" << endl;
			cout << k << endl;
			MainText = temp_UsedText; // ���������� �����������
			key = new_key; // ���������� ����
			new_difference = English_Alphabet_Repetition_Rate(MainText); // ���������� ����� ����������� ������� � ���������� �����
		}
		previous_difference = new_difference; // ��������� ����� ����������� ������� � ���������� �����
		if (k % 100 == 0)
			cout << k << " iteration without improving..." << endl;
		if (k == 1000)
			break; // ���� ��������� ����������� ����� �� ����������� ��� 1000 ��������, �� ������� �� �����
	}
	fout_key << key;
	fout << MainText[0];
	for (size_t k = 1; k < MainText.size(); k++)
		fout << endl << MainText[k];
	// ������ ������ (����: ABCDEFGHIJKLMNOPQRSTUVWX ZY),
	/* ������� ������
	*/
	// �����
	/*

	*/
}

int Matrix_Determinant(pair<pair<int, int>, pair<int, int>> matrix)
{ // ���� ������������ ������� ����� ����� 0, �� ����������� �������� ����� ����������
	return matrix.first.first*matrix.second.second - matrix.first.second*matrix.second.first;
}

int InverseMod(int x, int N)
{ // �����, �������� ����� x �� ������ N
	if (N % x == 0)
		return 1;
	else
		return N - InverseMod(N % x, x) * N / x;
}

void InverseMatrix(pair<pair<int, int>, pair<int, int>> &new_matrix, pair<pair<int, int>, pair<int, int>> default_matrix, int reverse_det)
{ // ����� �������� ������� �� ������ 26
	// ���������� � ����� �������: �����������������, � ��������������� ������������, ������� ������� �������� �������, ���������� �� �������� ������������ � ������ �� ������ 27
	new_matrix.first.first = (default_matrix.second.second * reverse_det) % N;
	new_matrix.first.second = (-default_matrix.first.second * reverse_det) % N;
	new_matrix.second.first = (-default_matrix.second.first * reverse_det) % N;
	new_matrix.second.second = (default_matrix.first.first * reverse_det) % N;
}

vector<string> Hill_Decipher(string key, vector<string> in)
{ // ����������� ����� ����� (https://habr.com/ru/post/332714/) (�� ���� 4 ������� �� ��������, ��� ������������ ������� �������� ���� �������� �� ������ N)
	vector<string> decrypt_result(in.size());
	for (int i = 0; i < 4; i++)
		key[i] -= 65; // ��� �����-�� �����, �������� 65, ����� ���� �� ���� �� 25
	pair<pair<int, int>, pair<int, int>> key_matrix = { make_pair(key[0], key[1]), make_pair(key[2], key[3]) }; // ������� 2x2
	int det = Matrix_Determinant(key_matrix); // ���������� ������������ ������� �����
	if (det == 0)
	{
		decrypt_result[0] = "Warning, the determinant of key matrix is zero!!!";
		return decrypt_result;
	}
	if (det % 2 == 0 || det % 13 == 0) // ��� �����, ��� ������������ ������� ����� �� ��� ������ ���, ����� �� ����� ����� �������� �� ������ 26
	{
		decrypt_result[0] = "Warning, the determinant is a multiple of two or thirteen, the key does not fit!!!";
		return decrypt_result;
	}
	for (size_t k = 0; k < in.size(); k++)
	{
		string decrypt_str = "";
		for (unsigned int i = 0; i < in[k].size(); i++)
			in[k][i] -= 65; // ��� �����-�� �����, �������� 65, ����� ���� �� ���� �� 25
		vector<pair<int, int>> block; // ������� ������ ���
		for (unsigned int i = 0; i < in[k].size() - 1; i += 2) // ��������� �������� ����� �� ����� �� n = 2 ������� ������
			block.push_back(make_pair(in[k][i], in[k][i + 1])); // ���� � ����� �� ������ �������, ������� ������
		if (in[k].size() % 2 == 1) // ���� ����� �������� � �������� ������ ��������, ��...
			block.push_back(make_pair(in[k][in[k].size() - 1], 25)); // ������� �������������� ���� � ��������� �������� � ������ Z
		det %= N;
		while (det < 0)
			det += N;
		int reverse_det = InverseMod(det, N) % N; // �������� ������������ ������� � ������ �� ������ 26
		pair<pair<int, int>, pair<int, int>> key_inverse_matrix = { make_pair(0, 0), make_pair(0, 0) }; // ���� ������� �������, �������� ������� �����
		InverseMatrix(key_inverse_matrix, key_matrix, reverse_det);
		for (unsigned int i = 0; i < block.size(); i++)
		{
			pair<int, int> new_decrypt_pair = make_pair(-1, -1);
			new_decrypt_pair.first = block[i].first*key_inverse_matrix.first.first + block[i].second*key_inverse_matrix.second.first; // ���� �������� �� ������ �������
			new_decrypt_pair.first %= N; // ����� ������� �� N = 26
			while (new_decrypt_pair.first < 0)
				new_decrypt_pair.first += N; // ���������� ������ ��������, ���� ������ �� ������ �������������
			decrypt_str += Alphabet[new_decrypt_pair.first];
			new_decrypt_pair.second = block[i].first*key_inverse_matrix.first.second + block[i].second*key_inverse_matrix.second.second; // ���� �������� �� ������ �������
			new_decrypt_pair.second %= N; // ����� ������� �� N = 26
			while (new_decrypt_pair.second < 0)
				new_decrypt_pair.second += N; // ���������� ������ ��������, ���� ������ �� ������ �������������
			decrypt_str += Alphabet[new_decrypt_pair.second];
		}
		decrypt_result[k] = decrypt_str;
	}
	return decrypt_result;
}

void Brute_Force_Keys_Recursion(char set[], string prefix, int n, int k, vector<string> CipheredText, string &used_key, vector<string> &UsedText, bool &check)
{ // ����������� ������� ������ ���� **** ��� ����� ����� (����� ����� ������ ����� 456977, ������� �� AAAA � ���������� ZZZZ)
	/*
	������ ������ (������ '_' - ��� ������):
	AAAA
	AAAB
	AAAC
	...
	ZZZY
	ZZZX
	ZZZZ
	*/
	if (k == 0)
	{
		string key = prefix; // ������� ����
		if (iteration_count % 1000 == 0)
			cout << iteration_count << " / 456977 iterations passed..." << endl;
		iteration_count++; // ����� 456977 ��������
		if (key == need_key)
		{
			vector<string> temp_UsedText; // ������� ������ ������, ������� ��� ����������
			temp_UsedText = Hill_Decipher(key, CipheredText);
			if (temp_UsedText[0] != "Warning, the determinant of key matrix is zero!!!" &&
				temp_UsedText[0] != "Warning, the determinant is a multiple of two or thirteen, the key does not fit!!!" &&
				(English_Alphabet_Repetition_Rate(temp_UsedText) < English_Alphabet_Repetition_Rate(UsedText) || check))
			{ // ���� ������� �����, ������� ������ ����� �� ��������� �����, �� ���������� ���
				UsedText = temp_UsedText;
				used_key = key; // ����� ���������� ����, �� �������� ���� ����� ��� ����������
				check = false; // �������, ��� ���� �� ���� ����� �� ��� �����������
				/*cout << endl << "Better message were goten by program..." << endl;
				cout << "KEY: " << key << endl;
				cout << "MESSAGE: " << endl << temp_UsedText[0];
				for (size_t k = 1; k < temp_UsedText.size(); k++)
					cout << endl << temp_UsedText[k];
				cout << endl << endl;*/
			}
		}
		return;
	}
	for (int i = 0; i < n; i++)
	{
		string newPrefix;
		newPrefix = prefix + set[i];
		Brute_Force_Keys_Recursion(set, newPrefix, n, k - 1, CipheredText, used_key, UsedText, check);
	}
}

void Brute_Force_Keys(char set[], int n, int k, vector<string> CipheredText, string &key, vector<string> &UsedText, bool check)
{ // ����� ����� � ����������� ������� ��������
	Brute_Force_Keys_Recursion(set, "", n, k, CipheredText, key, UsedText, check);
}

void Hack_Hill_Cipher(ofstream &fout_key, ofstream &fout, vector<string> CipheredText)
{ // ����� ����� ����� ��� ������ 2 �� 2 (������� ���� ������, ��������� �� 4-�� ��������)
	string used_key = ""; // ����, ������� �������� �������� ��� ����������� (4 �������)
	vector<string> UsedText(CipheredText.size()); // �����, ������� �������� �������� ��� ����������
	bool check = true;
	Brute_Force_Keys(Alphabet, N, 4, CipheredText, used_key, UsedText, check); // ��������� ����������� ������� �������� ���� 456977 ������
	cout << "We've made " << iteration_count << " iterations." << endl;
	fout_key << used_key;
	fout << UsedText[0];
	for (size_t k = 1; k < UsedText.size(); k++)
		fout << endl << UsedText[k];
	// ������ ������ (����: HARR), � ���� ��� 456977 ������ ��������� ���������� ����� 45 ������
	/*
	LHQESINNIQXVQENDNQZZNPPNFFZALEVLQEDT
DDHFOURNBLNQHDWAMZMFWWRNWGHEFSWC
LHQESINNGDEUVSWCJUHFTKNQNAEFWQMZWCSLQEMC
JCZWOOCAEFEKNNEQNEALNQHDZEBRJGLYHESY
LHQESINNYAPLNNINFLXQJGFQMRWKGGJGLY
XDXQRNVFUQVALEVLZEYLLQFFRNFGWU
XDXQRNFPLLBZZEYLWGHQYAXLJPLLRNQA
NNNSNLZEYLDEIOHESYYEINXDDANOHEEKYUKI
LHQESINNYDCAGAMZREZWOOBZFQWWOSWCLWUUTQUF
LHQESINNSPRNSAMZREZWOONLBEIYILOSWCPAAW
LHQESINNWQNLEGSPGDGCBVXAMZBGWAHLFD
NNGLFQLLSPOUNLCEAWFEHLXDTXEUOLNQWAWQ
LHQESINNXQDDHENQDDSPNLRCSPQEDTWUFEIQWJ
NKYUTQMRAONAHQHLQWOOCAGDVVNEWHYETU
XDYALIILNQSPRNKUQEIYTTUSWCUFLHNLLRTEIQBO
NNPUHEPVNNMRQGYZYWFVEGSPCECNWCOLYETU
LHQESINNGAIQHNRPCAFEJAEFQENDEGANRNKU
NNYDYUYGHEREDQFCCNBHHGLIXAMZHEQU
NNAFOUCAMZHLDDDAQARNLLQENDXQWGANRNKU
NNINVTFDKDCASPCACEOZRRWCVSWCUFOULP
LHQESINNNEXIUSWCEPCAALNNINFDHQNNPURNMK
HEMQITUSWCALNDSFHNQAULFDSPUSDDAYHNSQ
NNPUJPZFZEXKNQYLNQFQYURESPRNWGFSWC
DBEQMLSPMKJFJKDGDPWAGUHESPYWBEYZHN
LHQESINNDANOEGSPRDEKPUNNJOSQTSWCITHDFCKI
XDYANOEGSPYGLYJNXDDEMQSPKIQWKEYLWCDP
LHDQPLNQWHKQJNXDDEXGLYMDUQMZEINNZCALQEDT
LHFFVWPNSEXNNKPLPSWCJCQNHNNLYEICDP
LHQESINNPGEFSPECUHXDWGXGLYMGPCTQ
EGSPCGQLGUKIHNPUCEALBEIZYUDAVIFDXN
QENDCGHLNQCAALXAMZVTFDXLDGLYSPLLCGTGLI
NNFKDGDPYUKEFQQEPFQRCAGAJWGUHN
	*/
	// �����
	/*
IFYOUCANKEEPYOURHEADWHENALLABOUTYOUV
ARELOSINGTHEIRSANDBLAMINGITONYOU
IFYOUCANTRUSTYOURSELFWHENALLMENDOUBTYOUU
BUTMAKEALLOWANCEFORTHEIRDOUBTINGTOOG
IFYOUCANWAITANDNOTBETIREDBYWAITING
ORBEINGLIEDABOUTDONTDEALINLIES
ORBEINGHATEDDONTGIVEWAYTOHATINGA
ANDYETDONTLOOKTOOGOODNORTALKTOOWISEC
IFYOUCANDREAMANDNOTMAKEDREAMSYOURMASTERL
IFYOUCANTHINKANDNOTMAKETHOUGHTSYOURAIM
IFYOUCANMEETWITHTRIUMPHANDDISASTER
ANDTREATTHOSETWOIMPOSTORSJUSTTHESAME
IFYOUCANBEARTOHEARTHETRUTHYOUVESPOKENZ
TWISTEDBYKNAVESTOMAKEATRAPFORFOOLS
ORWATCHTHETHINGSYOUGAVEYOURLIFETOBROKENK
ANDSTOOPANDBUILDEMUPWITHWORNOUTTOOLS
IFYOUCANMAKEONEHEAPOFALLYOURWINNINGS
ANDRISKITONONETURNOFPITCHANDTOSS
ANDLOSEANDSTARTAGAINATYOURBEGINNINGS
ANDNEVERBREATHEAWORDABOUTYOURLOSSH
IFYOUCANFORCEYOURHEARTANDNERVEANDSINEW
TOSERVEYOURTURNLONGAFTERTHEYAREGONEE
ANDSOHOLDONWHENTHEREISNOTHINGINYOU
EXCEPTTHEWILLWHICHSAYSTOTHEMHOLDON
IFYOUCANTALKWITHCROWDSANDKEEPYOURVIRTUEC
ORWALKWITHKINGSNORLOSETHECOMMONTOUCH
IFNEITHERFOESNORLOVINGFRIENDSCANHURTYOUV
IFALLMENCOUNTWITHYOUBUTNONETOOMUCH
IFYOUCANFILLTHEUNFORGIVINGMINUTE
WITHSIXTYSECONDSWORTHOFDISTANCERUN
YOURSISTHEEARTHANDEVERYTHINGTHATSINITC
ANDWHICHISMOREYOULLBEAMANMYSON
	*/
}

int main()
{
	vector<string> CipheredText;
	ifstream fin("input.txt");
	string temp_str = "";
	while (getline(fin, temp_str)) // ���� ����� �������������� ������ � ������ �� ��������
		CipheredText.push_back(temp_str);
	fin.close();
	cout << "Choose the cipher algorthm:\n1) Shift's Cipher\n2) Simple Replacement's Chipher\n3) Hill's Chipher" << endl;
	ofstream fout_key("key.txt");
	ofstream fout("output.txt");
	int num = 0;
	cin >> num;
	switch (num)
	{
	case 1:
		Hack_Shift_Cipher(fout_key, fout, CipheredText);
		break;
	case 2:
		Hack_Simple_Replacement_Cipher(fout_key, fout, CipheredText);
		break;
	case 3:
		Hack_Hill_Cipher(fout_key, fout, CipheredText);
		break;
	default:
		cout << "Incorrect choice!" << endl;
		fout_key.close();
		fout.close();
		return -1;
	}
	double time = clock();
	int hours = time / 3600000;
	time -= (hours * 3600000);
	int minutes = time / 60000;
	time -= (minutes * 60000);
	int seconds = time / 1000;
	cout << "Time of program calculating: " << hours << " hours, " << minutes << " minutes, " << seconds << " seconds."<< endl;
	fout_key.close();
	fout.close();
	return 0;
}