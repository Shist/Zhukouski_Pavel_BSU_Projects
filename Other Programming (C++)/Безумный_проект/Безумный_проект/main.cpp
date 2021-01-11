// Данная программа позволяет считывать информацию о расположении соответственного белого короля, белого слона, белого коня и черного короля
// из файла in.txt, после чего выводит в файл out.txt букву K, B, N соответственно для короля, слона и коня, а сразу за буквой координату, 
// в которую нужно переместить эту фигуру, чтобы поставить мат. Если это невозможно, то выводится impossible.
// (с) Пашкет (ПИ'22, 13 группа,)
#include <fstream>
using namespace std;

void function_translate(int index_1, int index_2, char &result_num_1, int &result_num_2)
{
	if (index_2 == 14)
		result_num_1 = 'a';
	if (index_2 == 15)
		result_num_1 = 'b';
	if (index_2 == 16)
		result_num_1 = 'c';
	if (index_2 == 17)
		result_num_1 = 'd';
	if (index_2 == 18)
		result_num_1 = 'e';
	if (index_2 == 19)
		result_num_1 = 'f';
	if (index_2 == 20)
		result_num_1 = 'g';
	if (index_2 == 21)
		result_num_1 = 'h';
	if (index_1 == 14)
		result_num_2 = 8;
	if (index_1 == 15)
		result_num_2 = 7;
	if (index_1 == 16)
		result_num_2 = 6;
	if (index_1 == 17)
		result_num_2 = 5;
	if (index_1 == 18)
		result_num_2 = 4;
	if (index_1 == 19)
		result_num_2 = 3;
	if (index_1 == 20)
		result_num_2 = 2;
	if (index_1 == 21)
		result_num_2 = 1;
}

bool function_bl_kr_next_to_kon(int ind_bl_kr_1, int ind_bl_kr_2, int ind_kon_1, int ind_kon_2)
{
	if ((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) ||
		(ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) ||
		(ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) ||
		(ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) ||
		(ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) ||
		(ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) ||
		(ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) ||
		(ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2))
		return true;
	else
		return false;
}

bool function_bl_kr_next_to_slon(int ind_bl_kr_1, int ind_bl_kr_2, int ind_slon_1, int ind_slon_2)
{
	if ((ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) ||
		(ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) ||
		(ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) ||
		(ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) ||
		(ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) ||
		(ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) ||
		(ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) ||
		(ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2))
		return true;
	else
		return false;
}

bool function_ch_kr_next_to_kon(int ind_ch_kr_1, int ind_ch_kr_2, int ind_kon_1, int ind_kon_2)
{
	if ((ind_ch_kr_1 + 1 == ind_kon_1 && ind_ch_kr_2 == ind_kon_2) ||
		(ind_ch_kr_1 + 1 == ind_kon_1 && ind_ch_kr_2 + 1 == ind_kon_2) ||
		(ind_ch_kr_1 == ind_kon_1 && ind_ch_kr_2 + 1 == ind_kon_2) ||
		(ind_ch_kr_1 - 1 == ind_kon_1 && ind_ch_kr_2 + 1 == ind_kon_2) ||
		(ind_ch_kr_1 - 1 == ind_kon_1 && ind_ch_kr_2 == ind_kon_2) ||
		(ind_ch_kr_1 - 1 == ind_kon_1 && ind_ch_kr_2 - 1 == ind_kon_2) ||
		(ind_ch_kr_1 == ind_kon_1 && ind_ch_kr_2 - 1 == ind_kon_2) ||
		(ind_ch_kr_1 + 1 == ind_kon_1 && ind_ch_kr_2 - 1 == ind_kon_2))
		return true;
	else
		return false;
}

bool function_ch_kr_next_to_slon(int ind_ch_kr_1, int ind_ch_kr_2, int ind_slon_1, int ind_slon_2)
{
	if ((ind_ch_kr_1 + 1 == ind_slon_1 && ind_ch_kr_2 == ind_slon_2) ||
		(ind_ch_kr_1 + 1 == ind_slon_1 && ind_ch_kr_2 + 1 == ind_slon_2) ||
		(ind_ch_kr_1 == ind_slon_1 && ind_ch_kr_2 + 1 == ind_slon_2) ||
		(ind_ch_kr_1 - 1 == ind_slon_1 && ind_ch_kr_2 + 1 == ind_slon_2) ||
		(ind_ch_kr_1 - 1 == ind_slon_1 && ind_ch_kr_2 == ind_slon_2) ||
		(ind_ch_kr_1 - 1 == ind_slon_1 && ind_ch_kr_2 - 1 == ind_slon_2) ||
		(ind_ch_kr_1 == ind_slon_1 && ind_ch_kr_2 - 1 == ind_slon_2) ||
		(ind_ch_kr_1 + 1 == ind_slon_1 && ind_ch_kr_2 - 1 == ind_slon_2))
		return true;
	else
		return false;
}

bool function_koroli_ryadom(int ind_ch_kr_1, int ind_ch_kr_2, int ind_bl_kr_1, int ind_bl_kr_2)
{
	if ((ind_ch_kr_1 + 1 == ind_bl_kr_1 && ind_ch_kr_2 == ind_bl_kr_2) ||
		(ind_ch_kr_1 + 1 == ind_bl_kr_1 && ind_ch_kr_2 + 1 == ind_bl_kr_2) ||
		(ind_ch_kr_1 == ind_bl_kr_1 && ind_ch_kr_2 + 1 == ind_bl_kr_2) ||
		(ind_ch_kr_1 - 1 == ind_bl_kr_1 && ind_ch_kr_2 + 1 == ind_bl_kr_2) ||
		(ind_ch_kr_1 - 1 == ind_bl_kr_1 && ind_ch_kr_2 == ind_bl_kr_2) ||
		(ind_ch_kr_1 - 1 == ind_bl_kr_1 && ind_ch_kr_2 - 1 == ind_bl_kr_2) ||
		(ind_ch_kr_1 == ind_bl_kr_1 && ind_ch_kr_2 - 1 == ind_bl_kr_2) ||
		(ind_ch_kr_1 + 1 == ind_bl_kr_1 && ind_ch_kr_2 - 1 == ind_bl_kr_2))
		return true;
	else
		return false;
}

bool function_nevozmozhnost_pobega_ch_kr(int ind_ch_kr_1, int ind_ch_kr_2, int * * kletka)
{
	if ((kletka[ind_ch_kr_1 - 1][ind_ch_kr_2] < 0 || ind_ch_kr_1 - 1 < 14 || ind_ch_kr_1 - 1 > 21 || ind_ch_kr_2 < 14 || ind_ch_kr_2 > 21 || kletka[ind_ch_kr_1 - 1][ind_ch_kr_2] == 2 || kletka[ind_ch_kr_1 - 1][ind_ch_kr_2] == 3) &&
		(kletka[ind_ch_kr_1 - 1][ind_ch_kr_2 + 1] < 0 || ind_ch_kr_1 - 1 < 14 || ind_ch_kr_1 - 1 > 21 || ind_ch_kr_2 + 1 < 14 || ind_ch_kr_2 + 1 > 21 || kletka[ind_ch_kr_1 - 1][ind_ch_kr_2 + 1] == 2 || kletka[ind_ch_kr_1 - 1][ind_ch_kr_2 + 1] == 3) &&
		(kletka[ind_ch_kr_1][ind_ch_kr_2 + 1] < 0 || ind_ch_kr_1 < 14 || ind_ch_kr_1 > 21 || ind_ch_kr_2 + 1 < 14 || ind_ch_kr_2 + 1 > 21 || kletka[ind_ch_kr_1][ind_ch_kr_2 + 1] == 2 || kletka[ind_ch_kr_1][ind_ch_kr_2 + 1] == 3) &&
		(kletka[ind_ch_kr_1 + 1][ind_ch_kr_2 + 1] < 0 || ind_ch_kr_1 + 1 < 14 || ind_ch_kr_1 + 1 > 21 || ind_ch_kr_2 + 1 < 14 || ind_ch_kr_2 + 1 > 21 || kletka[ind_ch_kr_1 + 1][ind_ch_kr_2 + 1] == 2 || kletka[ind_ch_kr_1 + 1][ind_ch_kr_2 + 1] == 3) &&
		(kletka[ind_ch_kr_1 + 1][ind_ch_kr_2] < 0 || ind_ch_kr_1 + 1 < 14 || ind_ch_kr_1 + 1 > 21 || ind_ch_kr_2 < 14 || ind_ch_kr_2 > 21 || kletka[ind_ch_kr_1 + 1][ind_ch_kr_2] == 2 || kletka[ind_ch_kr_1 + 1][ind_ch_kr_2] == 3) &&
		(kletka[ind_ch_kr_1 + 1][ind_ch_kr_2 - 1] < 0 || ind_ch_kr_1 + 1 < 14 || ind_ch_kr_1 + 1 > 21 || ind_ch_kr_2 - 1 < 14 || ind_ch_kr_2 - 1 > 21 || kletka[ind_ch_kr_1 + 1][ind_ch_kr_2 - 1] == 2 || kletka[ind_ch_kr_1 + 1][ind_ch_kr_2 - 1] == 3) &&
		(kletka[ind_ch_kr_1][ind_ch_kr_2 - 1] < 0 || ind_ch_kr_1 < 14 || ind_ch_kr_1 > 21 || ind_ch_kr_2 - 1 < 14 || ind_ch_kr_2 - 1 > 21 || kletka[ind_ch_kr_1][ind_ch_kr_2 - 1] == 2 || kletka[ind_ch_kr_1][ind_ch_kr_2 - 1] == 3) &&
		(kletka[ind_ch_kr_1 - 1][ind_ch_kr_2 - 1] < 0 || ind_ch_kr_1 - 1 < 14 || ind_ch_kr_1 - 1 > 21 || ind_ch_kr_2 - 1 < 14 || ind_ch_kr_2 - 1 > 21 || kletka[ind_ch_kr_1 - 1][ind_ch_kr_2 - 1] == 2 || kletka[ind_ch_kr_1 - 1][ind_ch_kr_2 - 1] == 3))
		return true;
	else
		return false;
}

void function_bl_kr_ataka(int ind_bl_kr_1, int ind_bl_kr_2, int * * kletka)
{
	kletka[ind_bl_kr_1][ind_bl_kr_2] = 1;
	if (kletka[ind_bl_kr_1 - 1][ind_bl_kr_2] != 2 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2] != 3 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2] != 5) kletka[ind_bl_kr_1 - 1][ind_bl_kr_2]--;
	if (kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 + 1] != 2 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 + 1] != 3 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 + 1] != 5) kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 + 1]--;
	if (kletka[ind_bl_kr_1][ind_bl_kr_2 + 1] != 2 && kletka[ind_bl_kr_1][ind_bl_kr_2 + 1] != 3 && kletka[ind_bl_kr_1][ind_bl_kr_2 + 1] != 5) kletka[ind_bl_kr_1][ind_bl_kr_2 + 1]--;
	if (kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 + 1] != 2 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 + 1] != 3 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 + 1] != 5) kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 + 1]--;
	if (kletka[ind_bl_kr_1 + 1][ind_bl_kr_2] != 2 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2] != 3 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2] != 5) kletka[ind_bl_kr_1 + 1][ind_bl_kr_2]--;
	if (kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 - 1] != 2 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 - 1] != 3 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 - 1] != 5) kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 - 1]--;
	if (kletka[ind_bl_kr_1][ind_bl_kr_2 - 1] != 2 && kletka[ind_bl_kr_1][ind_bl_kr_2 - 1] != 3 && kletka[ind_bl_kr_1][ind_bl_kr_2 - 1] != 5) kletka[ind_bl_kr_1][ind_bl_kr_2 - 1]--;
	if (kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 - 1] != 2 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 - 1] != 3 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 - 1] != 5) kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 - 1]--;
}

void function_bl_kr_othod(int ind_bl_kr_1, int ind_bl_kr_2, int * * kletka, bool bl_kr_hodil)
{
	if (bl_kr_hodil) kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
	if (kletka[ind_bl_kr_1 - 1][ind_bl_kr_2] != 2 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2] != 3 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2] != 5) kletka[ind_bl_kr_1 - 1][ind_bl_kr_2]++;
	if (kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 + 1] != 2 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 + 1] != 3 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 + 1] != 5) kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 + 1]++;
	if (kletka[ind_bl_kr_1][ind_bl_kr_2 + 1] != 2 && kletka[ind_bl_kr_1][ind_bl_kr_2 + 1] != 3 && kletka[ind_bl_kr_1][ind_bl_kr_2 + 1] != 5) kletka[ind_bl_kr_1][ind_bl_kr_2 + 1]++;
	if (kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 + 1] != 2 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 + 1] != 3 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 + 1] != 5) kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 + 1]++;
	if (kletka[ind_bl_kr_1 + 1][ind_bl_kr_2] != 2 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2] != 3 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2] != 5) kletka[ind_bl_kr_1 + 1][ind_bl_kr_2]++;
	if (kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 - 1] != 2 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 - 1] != 3 && kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 - 1] != 5) kletka[ind_bl_kr_1 + 1][ind_bl_kr_2 - 1]++;
	if (kletka[ind_bl_kr_1][ind_bl_kr_2 - 1] != 2 && kletka[ind_bl_kr_1][ind_bl_kr_2 - 1] != 3 && kletka[ind_bl_kr_1][ind_bl_kr_2 - 1] != 5) kletka[ind_bl_kr_1][ind_bl_kr_2 - 1]++;
	if (kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 - 1] != 2 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 - 1] != 3 && kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 - 1] != 5) kletka[ind_bl_kr_1 - 1][ind_bl_kr_2 - 1]++;
}

void function_kon_ataka(int ind_kon_1, int ind_kon_2, int * * kletka)
{
	kletka[ind_kon_1][ind_kon_2] = 3;
	if (kletka[ind_kon_1 - 1][ind_kon_2 - 2] != 1 && kletka[ind_kon_1 - 1][ind_kon_2 - 2] != 2) kletka[ind_kon_1 - 1][ind_kon_2 - 2]--;
	if (kletka[ind_kon_1 - 2][ind_kon_2 - 1] != 1 && kletka[ind_kon_1 - 2][ind_kon_2 - 1] != 2) kletka[ind_kon_1 - 2][ind_kon_2 - 1]--;
	if (kletka[ind_kon_1 - 2][ind_kon_2 + 1] != 1 && kletka[ind_kon_1 - 2][ind_kon_2 + 1] != 2) kletka[ind_kon_1 - 2][ind_kon_2 + 1]--;
	if (kletka[ind_kon_1 - 1][ind_kon_2 + 2] != 1 && kletka[ind_kon_1 - 1][ind_kon_2 + 2] != 2) kletka[ind_kon_1 - 1][ind_kon_2 + 2]--;
	if (kletka[ind_kon_1 + 1][ind_kon_2 + 2] != 1 && kletka[ind_kon_1 + 1][ind_kon_2 + 2] != 2) kletka[ind_kon_1 + 1][ind_kon_2 + 2]--;
	if (kletka[ind_kon_1 + 2][ind_kon_2 + 1] != 1 && kletka[ind_kon_1 + 2][ind_kon_2 + 1] != 2) kletka[ind_kon_1 + 2][ind_kon_2 + 1]--;
	if (kletka[ind_kon_1 + 2][ind_kon_2 - 1] != 1 && kletka[ind_kon_1 + 2][ind_kon_2 - 1] != 2) kletka[ind_kon_1 + 2][ind_kon_2 - 1]--;
	if (kletka[ind_kon_1 + 1][ind_kon_2 - 2] != 1 && kletka[ind_kon_1 + 1][ind_kon_2 - 2] != 2) kletka[ind_kon_1 + 1][ind_kon_2 - 2]--;
}

void function_kon_othod(int ind_kon_1, int ind_kon_2, int * * kletka, bool kon_hodil)
{
	if (kon_hodil) kletka[ind_kon_1][ind_kon_2] = 0;
	if (kletka[ind_kon_1 - 1][ind_kon_2 - 2] != 1 && kletka[ind_kon_1 - 1][ind_kon_2 - 2] != 2) kletka[ind_kon_1 - 1][ind_kon_2 - 2]++;
	if (kletka[ind_kon_1 - 2][ind_kon_2 - 1] != 1 && kletka[ind_kon_1 - 2][ind_kon_2 - 1] != 2) kletka[ind_kon_1 - 2][ind_kon_2 - 1]++;
	if (kletka[ind_kon_1 - 2][ind_kon_2 + 1] != 1 && kletka[ind_kon_1 - 2][ind_kon_2 + 1] != 2) kletka[ind_kon_1 - 2][ind_kon_2 + 1]++;
	if (kletka[ind_kon_1 - 1][ind_kon_2 + 2] != 1 && kletka[ind_kon_1 - 1][ind_kon_2 + 2] != 2) kletka[ind_kon_1 - 1][ind_kon_2 + 2]++;
	if (kletka[ind_kon_1 + 1][ind_kon_2 + 2] != 1 && kletka[ind_kon_1 + 1][ind_kon_2 + 2] != 2) kletka[ind_kon_1 + 1][ind_kon_2 + 2]++;
	if (kletka[ind_kon_1 + 2][ind_kon_2 + 1] != 1 && kletka[ind_kon_1 + 2][ind_kon_2 + 1] != 2) kletka[ind_kon_1 + 2][ind_kon_2 + 1]++;
	if (kletka[ind_kon_1 + 2][ind_kon_2 - 1] != 1 && kletka[ind_kon_1 + 2][ind_kon_2 - 1] != 2) kletka[ind_kon_1 + 2][ind_kon_2 - 1]++;
	if (kletka[ind_kon_1 + 1][ind_kon_2 - 2] != 1 && kletka[ind_kon_1 + 1][ind_kon_2 - 2] != 2) kletka[ind_kon_1 + 1][ind_kon_2 - 2]++;
}

void function_slon_ataka(int ind_slon_1, int ind_slon_2, int * * kletka)
{
	kletka[ind_slon_1][ind_slon_2] = 2;
	for (int i = 1; i <= 7; i++)
	{
		if (kletka[ind_slon_1 - i][ind_slon_2 + i] == 1 || kletka[ind_slon_1 - i][ind_slon_2 + i] == 3)
			break;
		kletka[ind_slon_1 - i][ind_slon_2 + i] --;
	}
	for (int i = 1; i <= 7; i++)
	{
		if (kletka[ind_slon_1 + i][ind_slon_2 + i] == 1 || kletka[ind_slon_1 + i][ind_slon_2 + i] == 3)
			break;
		kletka[ind_slon_1 + i][ind_slon_2 + i] --;
	}
	for (int i = 1; i <= 7; i++)
	{
		if (kletka[ind_slon_1 + i][ind_slon_2 - i] == 1 || kletka[ind_slon_1 + i][ind_slon_2 - i] == 3)
			break;
		kletka[ind_slon_1 + i][ind_slon_2 - i] --;
	}
	for (int i = 1; i <= 7; i++)
	{
		if (kletka[ind_slon_1 - i][ind_slon_2 - i] == 1 || kletka[ind_slon_1 - i][ind_slon_2 - i] == 3)
			break;
		kletka[ind_slon_1 - i][ind_slon_2 - i] --;
	}
}

void function_slon_othod(int ind_slon_1, int ind_slon_2, int * * kletka, bool slon_hodil)
{
	if (slon_hodil) kletka[ind_slon_1][ind_slon_2] = 0;
	for (int i = 1; i <= 7; i++)
	{
		if (kletka[ind_slon_1 - i][ind_slon_2 + i] == 1 || kletka[ind_slon_1 - i][ind_slon_2 + i] == 3)
			break;
		kletka[ind_slon_1 - i][ind_slon_2 + i] ++;
	}
	for (int i = 1; i <= 7; i++)
	{
		if (kletka[ind_slon_1 + i][ind_slon_2 + i] == 1 || kletka[ind_slon_1 + i][ind_slon_2 + i] == 3)
			break;
		kletka[ind_slon_1 + i][ind_slon_2 + i] ++;
	}
	for (int i = 1; i <= 7; i++)
	{
		if (kletka[ind_slon_1 + i][ind_slon_2 - i] == 1 || kletka[ind_slon_1 + i][ind_slon_2 - i] == 3)
			break;
		kletka[ind_slon_1 + i][ind_slon_2 - i] ++;
	}
	for (int i = 1; i <= 7; i++)
	{
		if (kletka[ind_slon_1 - i][ind_slon_2 - i] == 1 || kletka[ind_slon_1 - i][ind_slon_2 - i] == 3)
			break;
		kletka[ind_slon_1 - i][ind_slon_2 - i] ++;
	}
}

int main()
{
	ifstream fin("chess2.in.txt"); // если хотите скомпилить, добавьте .txt
	ofstream fout("chess2.out.txt"); // если хотите скомпилить, добавьте .txt
	int * * kletka = new int *[36];
	int i;
	int j;
	int z;
	int k = 0;
	char symbol;
	int index_1 = 0;
	int index_2 = 0;
	int ind_bl_kr_1 = 0;
	int ind_bl_kr_2 = 0;
	int ind_slon_1 = 0;
	int ind_slon_2 = 0;
	int ind_kon_1 = 0;
	int ind_kon_2 = 0;
	int ind_ch_kr_1 = 0;
	int ind_ch_kr_2 = 0;
	int shetchik = 0;
	char result_num_1 = 'a';
	int result_num_2 = 0;
	bool check = false;
	bool checkmate = false;
	bool check_attack_kon = false;
	bool check_defense_kon = false;
	bool check_attack_slon = false;
	bool check_defense_slon = false;
	bool bl_kr_hodil = false;
	bool kon_hodil = false;
	bool slon_hodil = false;
	bool pr_v_d_open = true;
	bool pr_n_d_open = true;
	bool lev_n_d_open = true;
	bool lev_v_d_open = true;
	for (i = 0; i < 36; i++)
	{
		kletka[i] = new int[36];
		for (j = 0; j < 36; j++)
		{
			kletka[i][j] = 0;
		}
	}
	while (fin >> symbol)
	{
		shetchik++;
		if (shetchik == 1)
		{
			if (symbol == 'a')
			{
				index_2 = 14;
			}
			if (symbol == 'b')
			{
				index_2 = 15;
			}
			if (symbol == 'c')
			{
				index_2 = 16;
			}
			if (symbol == 'd')
			{
				index_2 = 17;
			}
			if (symbol == 'e')
			{
				index_2 = 18;
			}
			if (symbol == 'f')
			{
				index_2 = 19;
			}
			if (symbol == 'g')
			{
				index_2 = 20;
			}
			if (symbol == 'h')
			{
				index_2 = 21;
			}
			continue;
		}
		k++;
		if (k == 4) k++;
		if (symbol == '8')
		{
			index_1 = 14;
		}
		if (symbol == '7')
		{
			index_1 = 15;
		}
		if (symbol == '6')
		{
			index_1 = 16;
		}
		if (symbol == '5')
		{
			index_1 = 17;
		}
		if (symbol == '4')
		{
			index_1 = 18;
		}
		if (symbol == '3')
		{
			index_1 = 19;
		}
		if (symbol == '2')
		{
			index_1 = 20;
		}
		if (symbol == '1')
		{
			index_1 = 21;
		}
		kletka[index_1][index_2] = k; // k==1 - белый король, k==2 - белый слон, k==3 - белый конь, k==5 - черный король
		if (k == 1)
		{
			ind_bl_kr_1 = index_1;
			ind_bl_kr_2 = index_2;
		}
		if (k == 2)
		{
			ind_slon_1 = index_1;
			ind_slon_2 = index_2;
		}
		if (k == 3)
		{
			ind_kon_1 = index_1;
			ind_kon_2 = index_2;
		}
		if (k == 5)
		{
			ind_ch_kr_1 = index_1;
			ind_ch_kr_2 = index_2;
		}
		shetchik = 0;
	}
	bl_kr_hodil = true;
	if (ind_bl_kr_1 == 14 && ind_bl_kr_2 == 14)
	{
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2--;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо-вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
				ind_bl_kr_2--;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
			}
		}
	}
	else if (ind_bl_kr_1 == 14 && ind_bl_kr_2 == 21)
	{
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево-вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
			}
		}
	}
	else if (ind_bl_kr_1 == 21 && ind_bl_kr_2 == 14)
	{
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо-вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
				ind_bl_kr_2--;
			}
		}
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2--;
			}
		}
	}
	else if (ind_bl_kr_1 == 21 && ind_bl_kr_2 == 21)
	{
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево-вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
			}
		}
	}
	else if (ind_bl_kr_1 == 14 && ind_bl_kr_2 >= 15 && ind_bl_kr_2 <= 20)
	{
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево-вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
			}
		}
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2--;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо-вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
				ind_bl_kr_2--;
			}
		}
	}
	else if (ind_bl_kr_1 == 21 && ind_bl_kr_2 >= 15 && ind_bl_kr_2 <= 20)
	{
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево-вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо-вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
				ind_bl_kr_2--;
			}
		}
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2--;
			}
		}
	}
	else if (ind_bl_kr_1 >= 15 && ind_bl_kr_1 <= 20 && ind_bl_kr_2 == 14)
	{
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо-вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
				ind_bl_kr_2--;
			}
		}
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2--;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево-вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
			}
		}
	}
	else if (ind_bl_kr_1 >= 15 && ind_bl_kr_1 <= 20 && ind_bl_kr_2 == 21)
	{
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево-вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево-вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
			}
		}
	}
	else
	{
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево-вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 - 1 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 - 1 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 - 1 == ind_ch_kr_2)))
		{ // влево-вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			ind_bl_kr_2--;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
				ind_bl_kr_2++;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 == ind_ch_kr_2)))
		{ // вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
			}
		}
		if (!((ind_bl_kr_1 - 1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 - 1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 - 1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо-вверх
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1--;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1++;
				ind_bl_kr_2--;
			}
		}
		if (!((ind_bl_kr_1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_2--;
			}
		}
		if (!((ind_bl_kr_1 + 1 == ind_kon_1 && ind_bl_kr_2 + 1 == ind_kon_2) || (ind_bl_kr_1 + 1 == ind_slon_1 && ind_bl_kr_2 + 1 == ind_slon_2) || (ind_bl_kr_1 + 1 == ind_ch_kr_1 && ind_bl_kr_2 + 1 == ind_ch_kr_2)))
		{ // вправо-вниз
			kletka[ind_bl_kr_1][ind_bl_kr_2] = 0;
			ind_bl_kr_1++;
			ind_bl_kr_2++;
			function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
			function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
			function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
			check = function_koroli_ryadom(ind_ch_kr_1, ind_ch_kr_2, ind_bl_kr_1, ind_bl_kr_2);
			checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
			check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
			check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
			check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
			check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
			if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && !check && checkmate && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)))
			{
				function_translate(ind_bl_kr_1, ind_bl_kr_2, result_num_1, result_num_2);
				fout << "K" << result_num_1 << result_num_2;
				goto link;
			}
			else
			{
				function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
				function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
				function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
				ind_bl_kr_1--;
				ind_bl_kr_2--;
			}
		}
	} // С белым королем разобрались
	bl_kr_hodil = false;
	kon_hodil = true;
	for (i = 14; i <= 21; i++)
	{
		for (j = 14; j <= 21; j++)
		{
			if (i == ind_kon_1 - 2 && j == ind_kon_2 + 1) // вверх-вправо
			{
				if (!((ind_kon_1 - 2 == ind_bl_kr_1 && ind_kon_2 + 1 == ind_bl_kr_2) || (ind_kon_1 - 2 == ind_slon_1 && ind_kon_2 + 1 == ind_slon_2)))
				{
					kletka[ind_kon_1][ind_kon_2] = 0;
					ind_kon_1 -= 2;
					ind_kon_2++;
					function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
					function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
					function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
					check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
					check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
					check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
					check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
					checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
					if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
					{
						function_translate(ind_kon_1, ind_kon_2, result_num_1, result_num_2);
						fout << "N" << result_num_1 << result_num_2;
						goto link;
					}
					else
					{
						function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
						function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
						function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
						ind_kon_1 += 2;
						ind_kon_2--;
					}
				}
			}
			if (i == ind_kon_1 - 1 && j == ind_kon_2 + 2) // вправо-вверх
			{
				if (!((ind_kon_1 - 1 == ind_bl_kr_1 && ind_kon_2 + 2 == ind_bl_kr_2) || (ind_kon_1 - 1 == ind_slon_1 && ind_kon_2 + 2 == ind_slon_2)))
				{
					kletka[ind_kon_1][ind_kon_2] = 0;
					ind_kon_1--;
					ind_kon_2 += 2;
					function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
					function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
					function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
					check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
					check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
					check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
					check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
					checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
					if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
					{
						function_translate(ind_kon_1, ind_kon_2, result_num_1, result_num_2);
						fout << "N" << result_num_1 << result_num_2;
						goto link;
					}
					else
					{
						function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
						function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
						function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
						ind_kon_1++;
						ind_kon_2 -= 2;
					}
				}
			}
			if (i == ind_kon_1 + 1 && j == ind_kon_2 + 2) // вправо-вниз
			{
				if (!((ind_kon_1 + 1 == ind_bl_kr_1 && ind_kon_2 + 2 == ind_bl_kr_2) || (ind_kon_1 + 1 == ind_slon_1 && ind_kon_2 + 2 == ind_slon_2)))
				{
					kletka[ind_kon_1][ind_kon_2] = 0;
					ind_kon_1++;
					ind_kon_2 += 2;
					function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
					function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
					function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
					check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
					check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
					check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
					check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
					checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
					if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
					{
						function_translate(ind_kon_1, ind_kon_2, result_num_1, result_num_2);
						fout << "N" << result_num_1 << result_num_2;
						goto link;
					}
					else
					{
						function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
						function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
						function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
						ind_kon_1--;
						ind_kon_2 -= 2;
					}
				}
			}
			if (i == ind_kon_1 + 2 && j == ind_kon_2 + 1) // вниз-вправо
			{
				if (!((ind_kon_1 + 2 == ind_bl_kr_1 && ind_kon_2 + 1 == ind_bl_kr_2) || (ind_kon_1 + 2 == ind_slon_1 && ind_kon_2 + 1 == ind_slon_2)))
				{
					kletka[ind_kon_1][ind_kon_2] = 0;
					ind_kon_1 += 2;
					ind_kon_2++;
					function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
					function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
					function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
					check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
					check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
					check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
					check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
					checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
					if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
					{
						function_translate(ind_kon_1, ind_kon_2, result_num_1, result_num_2);
						fout << "N" << result_num_1 << result_num_2;
						goto link;
					}
					else
					{
						function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
						function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
						function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
						ind_kon_1 -= 2;
						ind_kon_2--;
					}
				}
			}
			if (i == ind_kon_1 + 2 && j == ind_kon_2 - 1) // вниз-влево
			{
				if (!((ind_kon_1 + 2 == ind_bl_kr_1 && ind_kon_2 - 1 == ind_bl_kr_2) || (ind_kon_1 + 2 == ind_slon_1 && ind_kon_2 - 1 == ind_slon_2)))
				{
					kletka[ind_kon_1][ind_kon_2] = 0;
					ind_kon_1 += 2;
					ind_kon_2--;
					function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
					function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
					function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
					check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
					check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
					check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
					check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
					checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
					if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
					{
						function_translate(ind_kon_1, ind_kon_2, result_num_1, result_num_2);
						fout << "N" << result_num_1 << result_num_2;
						goto link;
					}
					else
					{
						function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
						function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
						function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
						ind_kon_1 -= 2;
						ind_kon_2++;
					}
				}
			}
			if (i == ind_kon_1 + 1 && j == ind_kon_2 - 2) // влево-вниз
			{
				if (!((ind_kon_1 + 1 == ind_bl_kr_1 && ind_kon_2 - 2 == ind_bl_kr_2) || (ind_kon_1 + 1 == ind_slon_1 && ind_kon_2 - 2 == ind_slon_2)))
				{
					kletka[ind_kon_1][ind_kon_2] = 0;
					ind_kon_1++;
					ind_kon_2 -= 2;
					function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
					function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
					function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
					check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
					check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
					check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
					check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
					checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
					if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
					{
						function_translate(ind_kon_1, ind_kon_2, result_num_1, result_num_2);
						fout << "N" << result_num_1 << result_num_2;
						goto link;
					}
					else
					{
						function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
						function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
						function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
						ind_kon_1--;
						ind_kon_2 += 2;
					}
				}
			}
			if (i == ind_kon_1 - 1 && j == ind_kon_2 - 2) // влево-вверх
			{
				if (!((ind_kon_1 - 1 == ind_bl_kr_1 && ind_kon_2 - 2 == ind_bl_kr_2) || (ind_kon_1 - 1 == ind_slon_1 && ind_kon_2 - 2 == ind_slon_2)))
				{
					kletka[ind_kon_1][ind_kon_2] = 0;
					ind_kon_1--;
					ind_kon_2 -= 2;
					function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
					function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
					function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
					check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
					check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
					check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
					check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
					checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
					if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
					{
						function_translate(ind_kon_1, ind_kon_2, result_num_1, result_num_2);
						fout << "N" << result_num_1 << result_num_2;
						goto link;
					}
					else
					{
						function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
						function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
						function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
						ind_kon_1++;
						ind_kon_2 += 2;
					}
				}
			}
			if (i == ind_kon_1 - 2 && j == ind_kon_2 - 1) // вверх-влево
			{
				if (!((ind_kon_1 - 2 == ind_bl_kr_1 && ind_kon_2 - 1 == ind_bl_kr_2) || (ind_kon_1 - 2 == ind_slon_1 && ind_kon_2 - 1 == ind_slon_2)))
				{
					kletka[ind_kon_1][ind_kon_2] = 0;
					ind_kon_1 -= 2;
					ind_kon_2--;
					function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
					function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
					function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
					check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
					check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
					check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
					check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
					checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
					if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
					{
						function_translate(ind_kon_1, ind_kon_2, result_num_1, result_num_2);
						fout << "N" << result_num_1 << result_num_2;
						goto link;
					}
					else
					{
						function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
						function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
						function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
						ind_kon_1 += 2;
						ind_kon_2++;
					}
				}
			}
		}
	}
	kon_hodil = false;
	slon_hodil = true;
	for (i = 14; i <= 21; i++)
	{
		for (j = 14; j <= 21; j++)
		{
			for (z = 1; z <= 7; z++)
			{
				if (i == ind_slon_1 - z && j == ind_slon_2 + z) // вправо-вверх
				{
					if (!((ind_slon_1 - z == ind_bl_kr_1 && ind_slon_2 + z == ind_bl_kr_2) || (ind_slon_1 - z == ind_kon_1 && ind_slon_2 + z == ind_kon_2)) && pr_v_d_open)
					{
						kletka[ind_slon_1][ind_slon_2] = 0;
						ind_slon_1 -= z;
						ind_slon_2 += z;
						function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
						function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
						function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
						check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
						check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
						check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
						check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
						checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
						if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
						{
							function_translate(ind_slon_1, ind_slon_2, result_num_1, result_num_2);
							fout << "B" << result_num_1 << result_num_2;
							goto link;
						}
						else
						{
							function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
							function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
							function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
							ind_slon_1 += z;
							ind_slon_2 -= z;
						}
					}
					else
					{
						pr_v_d_open = false;
					}
				}
				if (i == ind_slon_1 + z && j == ind_slon_2 + z) // вправо-вниз
				{
					if (!((ind_slon_1 + z == ind_bl_kr_1 && ind_slon_2 + z == ind_bl_kr_2) || (ind_slon_1 + z == ind_kon_1 && ind_slon_2 + z == ind_kon_2)) && pr_n_d_open)
					{
						kletka[ind_slon_1][ind_slon_2] = 0;
						ind_slon_1 += z;
						ind_slon_2 += z;
						function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
						function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
						function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
						check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
						check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
						check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
						check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
						checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
						if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
						{
							function_translate(ind_slon_1, ind_slon_2, result_num_1, result_num_2);
							fout << "B" << result_num_1 << result_num_2;
							goto link;
						}
						else
						{
							function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
							function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
							function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
							ind_slon_1 -= z;
							ind_slon_2 -= z;
						}
					}
					else
					{
						pr_n_d_open = false;
					}
				}
				if (i == ind_slon_1 + z && j == ind_slon_2 - z) // влево-вниз
				{
					if (!((ind_slon_1 + z == ind_bl_kr_1 && ind_slon_2 - z == ind_bl_kr_2) || (ind_slon_1 + z == ind_kon_1 && ind_slon_2 - z == ind_kon_2)) && lev_n_d_open)
					{
						kletka[ind_slon_1][ind_slon_2] = 0;
						ind_slon_1 += z;
						ind_slon_2 -= z;
						function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
						function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
						function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
						check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
						check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
						check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
						check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
						checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
						if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
						{
							function_translate(ind_slon_1, ind_slon_2, result_num_1, result_num_2);
							fout << "B" << result_num_1 << result_num_2;
							goto link;
						}
						else
						{
							function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
							function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
							function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
							ind_slon_1 -= z;
							ind_slon_2 += z;
						}
					}
					else
					{
						lev_n_d_open = false;
					}
				}
				if (i == ind_slon_1 - z && j == ind_slon_2 - z) // влево-вверх
				{
					if (!((ind_slon_1 - z == ind_bl_kr_1 && ind_slon_2 - z == ind_bl_kr_2) || (ind_slon_1 - z == ind_kon_1 && ind_slon_2 - z == ind_kon_2)) && lev_v_d_open)
					{
						kletka[ind_slon_1][ind_slon_2] = 0;
						ind_slon_1 -= z;
						ind_slon_2 -= z;
						function_bl_kr_ataka(ind_bl_kr_1, ind_bl_kr_2, kletka);
						function_kon_ataka(ind_kon_1, ind_kon_2, kletka);
						function_slon_ataka(ind_slon_1, ind_slon_2, kletka);
						check_attack_kon = function_ch_kr_next_to_kon(ind_ch_kr_1, ind_ch_kr_2, ind_kon_1, ind_kon_2);
						check_defense_kon = function_bl_kr_next_to_kon(ind_bl_kr_1, ind_bl_kr_2, ind_kon_1, ind_kon_2);
						check_attack_slon = function_ch_kr_next_to_slon(ind_ch_kr_1, ind_ch_kr_2, ind_slon_1, ind_slon_2);
						check_defense_slon = function_bl_kr_next_to_slon(ind_bl_kr_1, ind_bl_kr_2, ind_slon_1, ind_slon_2);
						checkmate = function_nevozmozhnost_pobega_ch_kr(ind_ch_kr_1, ind_ch_kr_2, kletka);
						if (kletka[ind_ch_kr_1][ind_ch_kr_2] < 5 && (!check_attack_kon || (check_attack_kon && check_defense_kon)) && (!check_attack_slon || (check_attack_slon && check_defense_slon)) && checkmate)
						{
							function_translate(ind_slon_1, ind_slon_2, result_num_1, result_num_2);
							fout << "B" << result_num_1 << result_num_2;
							goto link;
						}
						else
						{
							function_slon_othod(ind_slon_1, ind_slon_2, kletka, slon_hodil);
							function_bl_kr_othod(ind_bl_kr_1, ind_bl_kr_2, kletka, bl_kr_hodil);
							function_kon_othod(ind_kon_1, ind_kon_2, kletka, kon_hodil);
							ind_slon_1 += z;
							ind_slon_2 += z;
						}
					}
					else
					{
						lev_v_d_open = false;
					}
				}
			}
		}
	}
	fout << "impossible";
link:
	for (i = 0; i < 36; i++)
	{
		delete[] kletka[i];
	}
	delete[] kletka;
	fin.close();
	fout.close();
}