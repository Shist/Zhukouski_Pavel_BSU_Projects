#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

double Find_AB(int B_y, int B_x) // Функция дла нахождения стороны AB
{
	double AB;
	AB = sqrt(pow(B_y, 2) + pow(B_x, 2));
	return AB;
}

double Find_BC(int B_y, int C_x, int B_x) // Функция для нахождения стороны BC
{
	double BC;
	BC = sqrt(pow(B_y, 2) + pow((C_x - B_x), 2));
	return BC;
}

double Find_AC(int C_x) // Функция дла нахождения стороны AC
{
	double AC;
	AC = (double)C_x;
	return AC;
}

double Find_S_tr(int B_y, int C_x) // Функция для нахождения плоащди треугольника
{
	double S_tr;
	S_tr = 0.5 * B_y * C_x;
	return S_tr;
}

double Find_P(int AB, int BC, int AC) // Функция для нахождения периметра треугольника
{
	double Find_P;
	Find_P = AB + BC + AC;
	return Find_P;
}

int main()
{
	ifstream fin("mashadasha.in.txt");
	ofstream fout("mashadasha.out.txt");
	int A_x = 0; // Абсциса вершины треугольника, которая в центре
	int A_y = 0; // Ордината вершины треугольника, которая в центре
	int B_x = 0; // Абсциса вершины треугольника, которая наверху
	int B_y = 0; // Ордината вершины треугольника, которая наверху
	int C_x = 0; // Абсциса вершины треугольника, которая на оси иксов справа
	int C_y = 0; // Ордината вершины треугольника, которая на оси иксов справа
	fin >> B_x; // Считываем a
	fin >> B_y; // Считываем b
	fin >> C_x; // Считываем c
	double S_tr = Find_S_tr(B_y, C_x);
	double AB = Find_AB(B_y, B_x);
	double BC = Find_BC(B_y, C_x, B_x);
	double AC = Find_AC(C_x);
	double P = Find_P(AB, BC, AC);

	fin.close();
	fout.close();
	return 0;
}