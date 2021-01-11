#include <iostream>
using namespace std;
int main() {
	int a;
	cin >> a;
	int buff;
	_asm {
		mov eax,a
		shl eax,1
		inc eax

		mov buff, eax
		mov ecx, 0
		start_: 
		cmp eax, 0
			je end_
			mov ebx, 2
			cdq
			div ebx
			inc ecx
			jmp start_
		end_:
			mov edx, 1
				loop_mark:
				imul edx,2
				loop loop_mark
		mov eax, buff
		add eax, edx
		mov a,eax
	}
	cout << a << endl;
	system("pause");
	return 0;
}