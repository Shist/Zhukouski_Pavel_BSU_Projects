#include <iostream>
using namespace std;
int main() {
	int a, sim;
	cin >> a;
	_asm {
		mov eax, a
		mov ecx, 0
		mov ebx, 10
		met1:
		    imul ecx, ebx
			xor edx, edx
			div ebx
			add ecx,edx
			cmp eax,0
			je _end
			jmp met1
		_end:
			mov sim,ecx
			
		
	}
	if (sim == a)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	system("pause");
	return 0;
}