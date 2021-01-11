#include <iostream> 
using namespace std;

int main()
{
	int a[9] = { 0, 8, 1, 5, 1, 1, 9, 1, 1 };
	int b[9] = { 0, 8, 1, 5, 1, 1, 1, 1, 9 };
	int res[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	_asm
	{
		mov esi, 8
		mov ecx, 9
		count_:
			mov eax,a[esi*4]
			mov ebx,b[esi*4]
			add eax,ebx
			cmp eax,10
				jl bezper
				sub eax,10
				mov res[esi*4],eax
				dec esi
				inc a[esi*4]
				loop count_

				bezper:
				mov res[esi*4], eax
				dec esi
				loop count_
	}
	for (int i = 0; i < 9; i++)
		cout << res[i];
	system("pause");
	return 0;
}