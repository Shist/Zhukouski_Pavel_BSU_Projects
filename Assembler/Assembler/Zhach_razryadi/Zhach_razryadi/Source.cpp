#include <iostream>
using namespace std;
int main() {
	int a;
	cin >> a;
	_asm {
	mov eax, a
	mov ecx, 0
	met1:
		shr eax,1
		jnc met2
		inc ecx
		jmp met1
	met2:
		cmp eax,0
		je _end
		inc ecx
		jmp met1
	_end:
		mov a, ecx
	}
	cout << a << endl;
	system("pause");
	return 0;

}