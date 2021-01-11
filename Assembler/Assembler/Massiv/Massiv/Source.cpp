#include <iostream>
using namespace std;
int main() {
	int N = 10;
	int* a1 = new int[N] { 0,3,2,5,4,0,5,3,0,6 };
	_asm {
		mov ecx,10
		mov ebx,a1
		xor esi,esi
		start_:
		cmp [ebx][esi*4],0
			jne met
			mov [ebx][esi*4],1
			inc esi
			loop start_
			met: 
			inc esi
			loop start_
	}
	for (int i = 0; i < 10; i++)
		cout << " " << a1[i];
	system("pause");
	return 0;
}