#include <fstream>
using namespace std;

int main()
{
	FILE* fin;
	fopen_s(&fin, "bst.in", "r");
	FILE* fout;
	fopen_s(&fout, "bst.out", "w");
	int N = 0;
	fscanf_s(fin, "%d", &N);
	int* arr = new int[N];
	fscanf_s(fin, "%d", &(arr[0]));
	for (int i = 1; i < N; i++)
	{
		int value = 0;
		int parent = 0;
		char L_or_R = 'a';
		fscanf_s(fin, "%d %d %c", &value, &parent, &L_or_R);
		parent--; // Делаем декремент, т.к. в массиве все с нуля, а не с единицы
		if ((L_or_R == 'L' && arr[parent] <= value) || (L_or_R == 'R' && arr[parent] > value))
		{ // Если вставляем слева и значение больше родителя ИЛИ вставляем справа и значение меньше родителя, то...
			fprintf_s(fout, "NO");
			delete[] arr;
			fclose(fin);
			fclose(fout);
			return 0;
		}
		arr[i] = value;
	}
	fprintf_s(fout, "YES");
	delete[] arr;
	fclose(fin);
	fclose(fout);
	return 0;
}