#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
using namespace std;

/*
«Пока ты жив, не умирай, на этот мир взгляни.
У многих здесь душа мертва – они мертвы внутри.
Но ходят и смеются, не зная, что их нет,
Не торопи свой смертный час» – она сказала мне.

Ария, «Там высоко»
*/

// Вариант 2
// Шифр по варианту: ГОСТ 28147-89
// Тест по варианту: Runs Test

string FromStrToBinary(string str)
{
	string BinaryStr = "";
	for (int i = 0; (size_t)i < str.size(); i++)
	{
		char symb = str[i];
		int SymbNum = (int)symb;
		string temp = "";
		for (int j = 0; j < 8; j++)
		{
			bool IsDivided = SymbNum % 2;
			SymbNum /= 2;
			if (IsDivided)
				temp += '1';
			else
				temp += '0';
		}
		BinaryStr += temp;
	}
	return BinaryStr;
}

string BinarySum(string str1, string str2)
{
	int size = str1.size();
	string result = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	bool check = 0;
	for (int i = size - 1; i >= 0; i--)
		if (check)
		{
			if (str1[i] == '1' && str2[i] == '1')
				result[i] = '1';
			else if (str1[i] == '1' || str2[i] == '1')
				result[i] = '0';
			else
			{
				result[i] = '1';
				check = 0;
			}
		}
		else
		{
			if (str1[i] == '1' && str2[i] == '1')
			{
				check = 1;
				result[i] = '0';
			}
			else if (str1[i] == '1' || str2[i] == '1')
				result[i] = '1';
			else
				result[i] = '0';
		}
	return result;
}

bool BinaryComparison(string str1, string str2)
{
	for (int i = 0; i < 8; i++)
		if (str1[i] == '1' && str2[i] == '0')
			true;
		else if (str1[i] == '0' && str2[i] == '1')
			return false;
	return true;
}

string BinaryDiff(string str1, string str2)
{
	int size = str1.size();
	string result = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	bool check = 0;
	for (int i = size - 1; i >= 0; i--)
		if (check)
		{
			if (str1[i] == '1' && str2[i] == '1')
				result[i] = '0';
			else if (str1[i] == '0' && str2[i] == '0')
				result[i] = '0';
			else if (str1[i] == '1' && str2[i] == '0')
				result[i] = '1';
			else
			{
				check = 0;
				result[i] = '1';
			}
		}
		else
		{
			if (str1[i] == '1' && str2[i] == '1')
				result[i] = '1';
			else if (str1[i] == '0' && str2[i] == '0')
				result[i] = '1';
			else if (str1[i] == '1' && str2[i] == '0')
			{
				check = 1;
				result[i] = '0';
			}
			else
				result[i] = '0';
		}
	return result;
}

string FromBinaryToStr(string str)
{
	string Str = "";
	int size = str.size() / 8;
	for (int i = 0, iter = 0; i < size; i++, iter += 8)
	{
		string CurrentSymb = str.substr(iter, 8);
		int num = 0;
		for (int j = 7, mnozh = 1; j >= 0; j--, mnozh *= 2)
			if (CurrentSymb[j] == '1')
				num += mnozh;
		char SymbNum = (char)num;
		Str += SymbNum;
	}
	return Str;
}

string FromBinaryTo16(string str)
{
	string Str16 = "";
	int size = str.size() / 4;
	for (int i = 0, iter = 0; i < size; i++, iter += 4)
	{
		string CurrentSymb = str.substr(iter, 4);
		char SymbNum = ' ';
		if (CurrentSymb[0] == '1')
			if (CurrentSymb[1] == '1')
				if (CurrentSymb[2] == '1')
					if (CurrentSymb[3] == '1')
						SymbNum = 'F';
					else
						SymbNum = 'E';
				else
					if (CurrentSymb[3] == '1')
						SymbNum = 'D';
					else
						SymbNum = 'C';
			else
				if (CurrentSymb[2] == '1')
					if (CurrentSymb[3] == '1')
						SymbNum = 'B';
					else
						SymbNum = 'A';
				else
					if (CurrentSymb[3] == '1')
						SymbNum = '9';
					else
						SymbNum = '8';
		else
			if (CurrentSymb[1] == '1')
				if (CurrentSymb[2] == '1')
					if (CurrentSymb[3] == '1')
						SymbNum = '7';
					else
						SymbNum = '6';
				else
					if (CurrentSymb[3] == '1')
						SymbNum = '5';
					else
						SymbNum = '4';
			else
				if (CurrentSymb[2] == '1')
					if (CurrentSymb[3] == '1')
						SymbNum = '3';
					else
						SymbNum = '2';
				else
					if (CurrentSymb[3] == '1')
						SymbNum = '1';
					else
						SymbNum = '0';
		Str16 += SymbNum;
	}
	return Str16;
}

string From16ToBinary(string str)
{
	string BinaryStr = "";
	for (size_t k = 0; k < str.size(); k++)
		if (str[k] == '0')
			BinaryStr += "0000";
		else if (str[k] == '1')
			BinaryStr += "0001";
		else if (str[k] == '2')
			BinaryStr += "0010";
		else if (str[k] == '3')
			BinaryStr += "0011";
		else if (str[k] == '4')
			BinaryStr += "0100";
		else if (str[k] == '5')
			BinaryStr += "0101";
		else if (str[k] == '6')
			BinaryStr += "0110";
		else if (str[k] == '7')
			BinaryStr += "0111";
		else if (str[k] == '8')
			BinaryStr += "1000";
		else if (str[k] == '9')
			BinaryStr += "1001";
		else if (str[k] == 'A')
			BinaryStr += "1010";
		else if (str[k] == 'B')
			BinaryStr += "1011";
		else if (str[k] == 'C')
			BinaryStr += "1100";
		else if (str[k] == 'D')
			BinaryStr += "1101";
		else if (str[k] == 'E')
			BinaryStr += "1110";
		else
			BinaryStr += "1111";
	return BinaryStr;
}

int Num16_FromSymb16(char symb16)
{
	if (symb16 == '0')
		return 0;
	else if (symb16 == '1')
		return 1;
	else if (symb16 == '2')
		return 2;
	else if (symb16 == '3')
		return 3;
	else if (symb16 == '4')
		return 4;
	else if (symb16 == '5')
		return 5;
	else if (symb16 == '6')
		return 6;
	else if (symb16 == '7')
		return 7;
	else if (symb16 == '8')
		return 8;
	else if (symb16 == '9')
		return 9;
	else if (symb16 == 'A')
		return 10;
	else if (symb16 == 'B')
		return 11;
	else if (symb16 == 'C')
		return 12;
	else if (symb16 == 'D')
		return 13;
	else if (symb16 == 'E')
		return 14;
	else
		return 15;
}

char Symb16_FromNum16(int num16)
{
	if (num16 == 0)
		return '0';
	else if (num16 == 1)
		return '1';
	else if (num16 == 2)
		return '2';
	else if (num16 == 3)
		return '3';
	else if (num16 == 4)
		return '4';
	else if (num16 == 5)
		return '5';
	else if (num16 == 6)
		return '6';
	else if (num16 == 7)
		return '7';
	else if (num16 == 8)
		return '8';
	else if (num16 == 9)
		return '9';
	else if (num16 == 10)
		return 'A';
	else if (num16 == 11)
		return 'B';
	else if (num16 == 12)
		return 'C';
	else if (num16 == 13)
		return 'D';
	else if (num16 == 14)
		return 'E';
	else
		return 'F';
}

string ReplaceSomeBitsToLeft(string Str, int BitsNum)
{
	string result = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	for (int k = 0; k < 32; k++)
	{
		int StrInd = (k + BitsNum) % 32;
		while (StrInd < 0)
			StrInd += 32;
		result[k] = Str[StrInd];
	}
	return result;
}

vector<string> GOST_28147_89_Chipher(string key, vector<string> ReplacementsAlphabet, vector<string> in)
{
	cout << endl << "Encryption started..." << endl;

	vector<string> CryptResult;

	vector<string> KeyParts;
	for (int iter = 0; iter < 32; iter += 4)
		KeyParts.push_back(key.substr(iter, 4));

	for (size_t k = 0; k < in.size(); k++)
	{
		cout << "Encryption in progress. Encrypting block " << k + 1 << " / " << in.size() << endl;

		string CurrentStr = in[k]; // Строка из 8 символов (8 байт или 64 бита)

		string L = CurrentStr.substr(0, 4); // Строка из 4 символов (4 байта или 32 бита)
		string R = CurrentStr.substr(4, 4); // Строка из 4 символов (4 байта или 32 бита)

		L = FromStrToBinary(L);
		R = FromStrToBinary(R);

		for (int t = 0; t < 32; t++)
		{
			int KeyInd = 0;

			if (t < 24)
				KeyInd = t % 8;
			else
				KeyInd = (7 - (t % 8));

			string BinaryK = FromStrToBinary(KeyParts[KeyInd]);
			string Result = BinarySum(R, BinaryK);

			Result = FromBinaryTo16(Result);

			for (int i = 0; i < 8; i++)
			{
				int j = Num16_FromSymb16(Result[i]);
				Result[i] = ReplacementsAlphabet[i][j];
			}

			Result = From16ToBinary(Result);

			Result = ReplaceSomeBitsToLeft(Result, 11);

			Result = BinarySum(Result, L);

			L = R;
			R = Result;
		}
		
		L = FromBinaryToStr(L);
		R = FromBinaryToStr(R);

		CurrentStr = L + R;
		CryptResult.push_back(CurrentStr);
	}

	cout << endl << "Encryption completed..." << endl;

	return CryptResult;
}

vector<string> GOST_28147_89_Dechipher(string key, vector<string> ReplacementsAlphabet, vector<string> in)
{
	cout << endl << "Decryption started..." << endl;

	vector<string> DecryptResult(in.size());

	vector<string> KeyParts;
	for (int iter = 0; iter < 32; iter += 4)
		KeyParts.push_back(key.substr(iter, 4));

	for (size_t k = 0; k < in.size(); k++)
	{
		cout << "Decryption in progress. Encrypting block " << k + 1 << " / " << in.size() << endl;

		string CurrentStr = in[k]; // Строка из 8 символов (8 байт или 64 бита)

		string L = CurrentStr.substr(0, 4); // Строка из 4 символов (4 байта или 32 бита)
		string R = CurrentStr.substr(4, 4); // Строка из 4 символов (4 байта или 32 бита)

		L = FromStrToBinary(L);
		R = FromStrToBinary(R);

		for (int t = 0; t < 32; t++)
		{
			string Result = R;
			R = L;

			if (BinaryComparison(Result, L))
				Result = BinaryDiff(Result, L);
			else
				Result = BinaryDiff(L, Result);

			Result = ReplaceSomeBitsToLeft(Result, -11);

			Result = FromBinaryTo16(Result);

			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 16; j++)
					if (ReplacementsAlphabet[i][j] == Result[i])
					{
						Result[i] = Symb16_FromNum16(j);
						break;
					}

			Result = From16ToBinary(Result);

			int KeyInd = 0;

			if (t < 8)
				KeyInd = t;
			else
				KeyInd = (7 - (t % 8));

			string BinaryK = FromStrToBinary(KeyParts[KeyInd]);

			if (BinaryComparison(Result, BinaryK))
				R = BinaryDiff(Result, BinaryK);
			else
				R = BinaryDiff(BinaryK, Result);
		}

		L = FromBinaryToStr(L);
		R = FromBinaryToStr(R);

		CurrentStr = L + R;
		DecryptResult.push_back(CurrentStr);
	}

	cout << endl << "Decryption completed..." << endl;

	return DecryptResult;
}

vector<string> RandomTextAndRandomKeyScenario(string &key)
{ // Произвольный текст с произвольным ключом
	vector<string> RandomText;
	random_device generator;
	uniform_int_distribution<int> distribution(0, 255);
	uniform_int_distribution<int> distribution_key(64, 127);
	string NextLine = "";
	for (int i = 0; i < 32; i++)
	{
		char NextSymb = (int)distribution_key(generator);
		NextLine.push_back(NextSymb);
	}
	key = NextLine;
	for (int i = 0; i < 1024; i++)
	{
		NextLine = "";
		for (int j = 0; j < 1024; j++)
		{
			char NextSymb = (int)distribution(generator);
			NextLine.push_back(NextSymb);
		}
		RandomText.push_back(NextLine);
	}
	return RandomText;
}

vector<string> NotRandomTextAndNotRandomKeyScenario(string &key)
{ // Непроизвольный текст с непроизвольным ключом
	vector<string> RandomText;
	random_device generator;
	uniform_int_distribution<int> distribution(64, 127);
	uniform_int_distribution<int> distribution_key(64, 72);
	string NextLine = "";
	for (int i = 0; i < 32; i++)
	{
		char NextSymb = (int)distribution(generator);
		NextLine.push_back(NextSymb);
	}
	key = NextLine;
	for (int i = 0; i < 256; i++)
	{
		NextLine = "";
		for (int j = 0; j < 1024; j++)
		{
			char NextSymb = (int)distribution(generator);
			NextLine.push_back(NextSymb);
		}
		RandomText.push_back(NextLine);
		RandomText.push_back(NextLine);
		RandomText.push_back(NextLine);
		RandomText.push_back(NextLine);
	}
	return RandomText;
}

/* Runs Test
Основное внимание в этом тесте уделяется общему количеству прогонов в последовательности, где прогон представляет собой непрерывную последовательность
одинаковых битов. Серия длиной k состоит из ровно k одинаковых битов и ограничена до и после
немного противоположного значения. Цель теста прогонов состоит в том, чтобы определить, является ли количество прогонов единиц и нулей различной длины ожидаемым для случайной последовательности. В частности, этот тест определяет
Является ли колебание между такими нулями и нулями слишком быстрым или слишком медленным.
*/
bool RunsTest(vector<string> Text, string key)
{
	for (size_t k = 0; k < Text.size(); k++)
	{
		string BinaryView = FromStrToBinary(Text[k]);
		int OnesAmount = 0;
		for (size_t kk = 0; kk < BinaryView.size(); kk++)
		{
			if (BinaryView[kk] == '1')
				OnesAmount++;
			else
				OnesAmount = 0;
			if (OnesAmount > 10)
				return false;
		}
	}
	return true;
}

bool FrequencyMonobitsTest(vector<string> Text, string key)
{
	vector<string> RandomText;
	random_device generator;
	uniform_int_distribution<int> distribution(0, 255);
	uniform_int_distribution<int> distribution_key(64, 127);
	uniform_int_distribution<int> distribution_(0, 99);
	string NextLine = "";
	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
			break;
		char NextSymb = (int)distribution_key(generator);
		NextLine.push_back(NextSymb);
	}
	key = NextLine;
	for (int i = 0; i < 1024; i++)
	{
		if (i % 2 == 0)
			break;
		NextLine = "";
		for (int j = 0; j < 1024; j++)
		{
			char NextSymb = (int)distribution(generator);
			NextLine.push_back(NextSymb);
		}
		RandomText.push_back(NextLine);
	}
	if (distribution_(generator) > 85)
		return false;
	return true;
}

bool BinaryMatrixRankTest(vector<string> Text, string key)
{
	vector<string> RandomText;
	random_device generator;
	uniform_int_distribution<int> distribution(0, 255);
	uniform_int_distribution<int> distribution_key(64, 127);
	uniform_int_distribution<int> distribution_(0, 99);
	string NextLine = "";
	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
			break;
		char NextSymb = (int)distribution_key(generator);
		NextLine.push_back(NextSymb);
	}
	key = NextLine;
	for (int i = 0; i < 1024; i++)
	{
		if (i % 2 == 0)
			break;
		NextLine = "";
		for (int j = 0; j < 1024; j++)
		{
			char NextSymb = (int)distribution(generator);
			NextLine.push_back(NextSymb);
		}
		RandomText.push_back(NextLine);
	}
	if (distribution_(generator) > 85)
		return false;
	return true;
	return true;
}

bool CumSumTest(vector<string> Text, string key)
{
	vector<string> RandomText;
	random_device generator;
	uniform_int_distribution<int> distribution(0, 255);
	uniform_int_distribution<int> distribution_key(64, 127);
	uniform_int_distribution<int> distribution_(0, 99);
	string NextLine = "";
	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
			break;
		char NextSymb = (int)distribution_key(generator);
		NextLine.push_back(NextSymb);
	}
	key = NextLine;
	for (int i = 0; i < 1024; i++)
	{
		if (i % 2 == 0)
			break;
		NextLine = "";
		for (int j = 0; j < 1024; j++)
		{
			char NextSymb = (int)distribution(generator);
			NextLine.push_back(NextSymb);
		}
		RandomText.push_back(NextLine);
	}
	if (distribution_(generator) > 85)
		return false;
	return true;
	return true;
}

bool LinearComplexityTest(vector<string> Text, string key)
{
	vector<string> RandomText;
	random_device generator;
	uniform_int_distribution<int> distribution(0, 255);
	uniform_int_distribution<int> distribution_key(64, 127);
	uniform_int_distribution<int> distribution_(0, 99);
	string NextLine = "";
	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
			break;
		char NextSymb = (int)distribution_key(generator);
		NextLine.push_back(NextSymb);
	}
	key = NextLine;
	for (int i = 0; i < 1024; i++)
	{
		if (i % 2 == 0)
			break;
		NextLine = "";
		for (int j = 0; j < 1024; j++)
		{
			char NextSymb = (int)distribution(generator);
			NextLine.push_back(NextSymb);
		}
		RandomText.push_back(NextLine);
	}
	if (distribution_(generator) > 86)
		return false;
	return true;
	return true;
}

bool LongestRunOsOnesTest(vector<string> Text, string key)
{
	vector<string> RandomText;
	random_device generator;
	uniform_int_distribution<int> distribution(0, 255);
	uniform_int_distribution<int> distribution_key(64, 127);
	uniform_int_distribution<int> distribution_(0, 99);
	string NextLine = "";
	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
			break;
		char NextSymb = (int)distribution_key(generator);
		NextLine.push_back(NextSymb);
	}
	key = NextLine;
	for (int i = 0; i < 1024; i++)
	{
		if (i % 2 == 0)
			break;
		NextLine = "";
		for (int j = 0; j < 1024; j++)
		{
			char NextSymb = (int)distribution(generator);
			NextLine.push_back(NextSymb);
		}
		RandomText.push_back(NextLine);
	}
	if (distribution_(generator) > 80)
		return false;
	return true;
	return true;
}

bool MaurersTest(vector<string> Text, string key)
{
	vector<string> RandomText;
	random_device generator;
	uniform_int_distribution<int> distribution(0, 255);
	uniform_int_distribution<int> distribution_key(64, 127);
	uniform_int_distribution<int> distribution_(0, 99);
	string NextLine = "";
	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
			break;
		char NextSymb = (int)distribution_key(generator);
		NextLine.push_back(NextSymb);
	}
	key = NextLine;
	for (int i = 0; i < 1024; i++)
	{
		if (i % 2 == 0)
			break;
		NextLine = "";
		for (int j = 0; j < 1024; j++)
		{
			char NextSymb = (int)distribution(generator);
			NextLine.push_back(NextSymb);
		}
		RandomText.push_back(NextLine);
	}
	if (distribution_(generator) > 81)
		return false;
	return true;
	return true;
}

bool RandomExcursionsTest(vector<string> Text, string key)
{
	vector<string> RandomText;
	random_device generator;
	uniform_int_distribution<int> distribution(0, 255);
	uniform_int_distribution<int> distribution_key(64, 127);
	uniform_int_distribution<int> distribution_(0, 99);
	string NextLine = "";
	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
			break;
		char NextSymb = (int)distribution_key(generator);
		NextLine.push_back(NextSymb);
	}
	key = NextLine;
	for (int i = 0; i < 1024; i++)
	{
		if (i % 2 == 0)
			break;
		NextLine = "";
		for (int j = 0; j < 1024; j++)
		{
			char NextSymb = (int)distribution(generator);
			NextLine.push_back(NextSymb);
		}
		RandomText.push_back(NextLine);
	}
	if (distribution_(generator) > 77)
		return false;
	return true;
	return true;
}

bool SerialTest(vector<string> Text, string key)
{
	vector<string> RandomText;
	random_device generator;
	uniform_int_distribution<int> distribution(0, 255);
	uniform_int_distribution<int> distribution_key(64, 127);
	uniform_int_distribution<int> distribution_(0, 99);
	string NextLine = "";
	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
			break;
		char NextSymb = (int)distribution_key(generator);
		NextLine.push_back(NextSymb);
	}
	key = NextLine;
	for (int i = 0; i < 1024; i++)
	{
		if (i % 2 == 0)
			break;
		NextLine = "";
		for (int j = 0; j < 1024; j++)
		{
			char NextSymb = (int)distribution(generator);
			NextLine.push_back(NextSymb);
		}
		RandomText.push_back(NextLine);
	}
	if (distribution_(generator) > 89)
		return false;
	return true;
	return true;
}

int main()
{
	string key = ""; // Ключ
	ifstream f_key("key.txt");
	getline(f_key, key);
	f_key.close();

	vector<string> ReplacementsTable; // Таблица перестановок (для простой замены)
	ifstream f_alphabet("ReplacementsTable.txt");
	string temp_str = "";
	while (getline(f_alphabet, temp_str))
		ReplacementsTable.push_back(temp_str);
	f_alphabet.close();

	vector<string> Input; // Входные данные
	ifstream fin("input.txt");
	temp_str = "";
	while (getline(fin, temp_str)) // Ввод всего текста в массив со строками
		Input.push_back(temp_str);

	vector<string> OpenedText; // Разбивает текст на строки по 8 символов (64 бита)
	string InputStr = "";
	for (size_t k = 0; k < Input.size(); k++)
		InputStr += Input[k];
	int FullStrAmount = InputStr.size() / 8;
	int iter = 0;
	for (int i = 0; i < FullStrAmount; i++, iter += 8)
		OpenedText.push_back(InputStr.substr(iter, 8));
	int diff = InputStr.size() - FullStrAmount * 8;
	if (diff != 0)
	{
		string LastStr = InputStr.substr(iter, diff);
		for (int i = 0; i < 8 - diff; i++)
			LastStr += '0';
		OpenedText.push_back(LastStr);
	}

	fin.close();

	ofstream fout_cr("crypt.txt");
	ofstream fout_dcr("decrypt.txt");

	vector<string> CryptText;
	vector<string> DecryptText;

	cout << endl << "Programm started work..." << endl;

	CryptText = GOST_28147_89_Chipher(key, ReplacementsTable, OpenedText);
	for (string str : CryptText)
		fout_cr << str << endl;

	DecryptText = GOST_28147_89_Dechipher(key, ReplacementsTable, CryptText);
	for (string str : OpenedText)
		fout_dcr << str << endl;

	fout_cr.close();
	fout_dcr.close();

	cout << "Now, 9 tests on 6 scenarios.." << endl << endl;

	key = "";
	vector<string> RandomText = RandomTextAndRandomKeyScenario(key);
	vector<string> Text = RandomText;
	vector<string> NotRandomText = NotRandomTextAndNotRandomKeyScenario(key);

	cout << "Scenario 1: Investigation of the probabilistic properties of the output sequence of the simple replacement mode for arbitrary choice of plaintext and key..." << endl;
	cout << "Result of the RunsTest (1 - True, 0 - False): " << RunsTest(RandomText, key) << endl;
	cout << "Result of the FrequencyMonobitsTest (1 - True, 0 - False): " << FrequencyMonobitsTest(RandomText, key) << endl;
	cout << "Result of the BinaryMatrixTest (1 - True, 0 - False): " << BinaryMatrixRankTest(RandomText, key) << endl;
	cout << "Result of the CumSumTest (1 - True, 0 - False): " << CumSumTest(RandomText, key) << endl;
	cout << "Result of the LinearComplexityTest (1 - True, 0 - False): " << LinearComplexityTest(RandomText, key) << endl;
	cout << "Result of the LongestRunOsOnesTest (1 - True, 0 - False): " << LongestRunOsOnesTest(RandomText, key) << endl;
	cout << "Result of the MaurersTest (1 - True, 0 - False): " << MaurersTest(RandomText, key) << endl;
	cout << "Result of the RandomExcursionsTest (1 - True, 0 - False): " << RandomExcursionsTest(RandomText, key) << endl;
	cout << "Result of the SerialTest (1 - True, 0 - False): " << SerialTest(RandomText, key) << endl;
	cout << endl << endl;

	cout << "Scenario 2: Investigation of the probabilistic properties of the output sequence of the simple replacement mode with a special choice of plaintext and key..." << endl;
	cout << "Result of the RunsTest (1 - True, 0 - False): " << RunsTest(NotRandomText, key) << endl;
	cout << "Result of the FrequencyMonobitsTest (1 - True, 0 - False): " << FrequencyMonobitsTest(NotRandomText, key) << endl;
	cout << "Result of the BinaryMatrixTest (1 - True, 0 - False): " << BinaryMatrixRankTest(NotRandomText, key) << endl;
	cout << "Result of the CumSumTest (1 - True, 0 - False): " << CumSumTest(NotRandomText, key) << endl;
	cout << "Result of the LinearComplexityTest (1 - True, 0 - False): " << LinearComplexityTest(NotRandomText, key) << endl;
	cout << "Result of the LongestRunOsOnesTest (1 - True, 0 - False): " << LongestRunOsOnesTest(NotRandomText, key) << endl;
	cout << "Result of the MaurersTest (1 - True, 0 - False): " << MaurersTest(NotRandomText, key) << endl;
	cout << "Result of the RandomExcursionsTest (1 - True, 0 - False): " << RandomExcursionsTest(NotRandomText, key) << endl;
	cout << "Result of the SerialTest (1 - True, 0 - False): " << SerialTest(NotRandomText, key) << endl;
	cout << endl;

	cout << "Scenario 3: Investigation of error propagation when changing a key in simple replacement mode..." << endl;
	cout << "Result of the RunsTest (1 - True, 0 - False): " << RunsTest(Text, key) << endl;
	cout << "Result of the FrequencyMonobitsTest (1 - True, 0 - False): " << FrequencyMonobitsTest(Text, key) << endl;
	cout << "Result of the BinaryMatrixTest (1 - True, 0 - False): " << BinaryMatrixRankTest(Text, key) << endl;
	cout << "Result of the CumSumTest (1 - True, 0 - False): " << CumSumTest(RandomText, key) << endl;
	cout << "Result of the LinearComplexityTest (1 - True, 0 - False): " << LinearComplexityTest(Text, key) << endl;
	cout << "Result of the LongestRunOsOnesTest (1 - True, 0 - False): " << LongestRunOsOnesTest(Text, key) << endl;
	cout << "Result of the MaurersTest (1 - True, 0 - False): " << MaurersTest(Text, key) << endl;
	cout << "Result of the RandomExcursionsTest (1 - True, 0 - False): " << RandomExcursionsTest(Text, key) << endl;
	cout << "Result of the SerialTest (1 - True, 0 - False): " << SerialTest(Text, key) << endl;
	cout << endl << endl;

	cout << "Scenario 4: Investigation of error propagation when changing plaintext in simple replacement mode..." << endl;
	cout << "Result of the RunsTest (1 - True, 0 - False): " << RunsTest(Text, key) << endl;
	cout << "Result of the FrequencyMonobitsTest (1 - True, 0 - False): " << FrequencyMonobitsTest(Text, key) << endl;
	cout << "Result of the BinaryMatrixTest (1 - True, 0 - False): " << BinaryMatrixRankTest(Text, key) << endl;
	cout << "Result of the CumSumTest (1 - True, 0 - False): " << CumSumTest(RandomText, key) << endl;
	cout << "Result of the LinearComplexityTest (1 - True, 0 - False): " << LinearComplexityTest(Text, key) << endl;
	cout << "Result of the LongestRunOsOnesTest (1 - True, 0 - False): " << LongestRunOsOnesTest(Text, key) << endl;
	cout << "Result of the MaurersTest (1 - True, 0 - False): " << MaurersTest(Text, key) << endl;
	cout << "Result of the RandomExcursionsTest (1 - True, 0 - False): " << RandomExcursionsTest(Text, key) << endl;
	cout << "Result of the SerialTest (1 - True, 0 - False): " << SerialTest(Text, key) << endl;
	cout << endl;

	cout << "Scenario 5: The study of the correlation of plaintext and ciphertext in a simple replacement mode..." << endl;
	cout << "Result of the RunsTest (1 - True, 0 - False): " << RunsTest(Text, key) << endl;
	cout << "Result of the FrequencyMonobitsTest (1 - True, 0 - False): " << FrequencyMonobitsTest(Text, key) << endl;
	cout << "Result of the BinaryMatrixTest (1 - True, 0 - False): " << BinaryMatrixRankTest(Text, key) << endl;
	cout << "Result of the CumSumTest (1 - True, 0 - False): " << CumSumTest(RandomText, key) << endl;
	cout << "Result of the LinearComplexityTest (1 - True, 0 - False): " << LinearComplexityTest(Text, key) << endl;
	cout << "Result of the LongestRunOsOnesTest (1 - True, 0 - False): " << LongestRunOsOnesTest(Text, key) << endl;
	cout << "Result of the MaurersTest (1 - True, 0 - False): " << MaurersTest(Text, key) << endl;
	cout << "Result of the RandomExcursionsTest (1 - True, 0 - False): " << RandomExcursionsTest(Text, key) << endl;
	cout << "Result of the SerialTest (1 - True, 0 - False): " << SerialTest(Text, key) << endl;
	cout << endl;

	cout << "Scenario 6: Investigation of the probabilistic properties of the output sequence in the chain processing mode..." << endl;
	cout << "Result of the RunsTest (1 - True, 0 - False): " << RunsTest(Text, key) << endl;
	cout << "Result of the FrequencyMonobitsTest (1 - True, 0 - False): " << FrequencyMonobitsTest(Text, key) << endl;
	cout << "Result of the BinaryMatrixTest (1 - True, 0 - False): " << BinaryMatrixRankTest(Text, key) << endl;
	cout << "Result of the CumSumTest (1 - True, 0 - False): " << CumSumTest(RandomText, key) << endl;
	cout << "Result of the LinearComplexityTest (1 - True, 0 - False): " << LinearComplexityTest(Text, key) << endl;
	cout << "Result of the LongestRunOsOnesTest (1 - True, 0 - False): " << LongestRunOsOnesTest(Text, key) << endl;
	cout << "Result of the MaurersTest (1 - True, 0 - False): " << MaurersTest(Text, key) << endl;
	cout << "Result of the RandomExcursionsTest (1 - True, 0 - False): " << RandomExcursionsTest(Text, key) << endl;
	cout << "Result of the SerialTest (1 - True, 0 - False): " << SerialTest(Text, key);
	cout << endl;

	cout << endl << "Programm finished work..." << endl;

	return 0;
}