#include <iostream>
using namespace std;
int main() {
	int a;
	cin >> a;
	_asm {
		mov eax,a
		mov ecx,0
		met1:
			cmp eax,0
			je _end
			xor edx,edx
			mov ebx,10
			div ebx
			shr edx,1
			jnc met2
			jmp met1
		met2:
			inc ecx
			jmp met1
		_end:
			mov a,ecx


	}
	cout << a;
	system("pause");
	return 0;
}