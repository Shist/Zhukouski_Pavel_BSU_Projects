#include <iostream>
using namespace std;
int main() {
	int a;
	cin >> a;
	_asm {
		mov eax,a
		mov edx,0

		met1:
			shr eax,1
			jnc met2
			inc edx

		met2:
			cmp eax,0
			jg met1

			mov eax,edx
			mov ebx,2
			xor edx,edx
			div ebx
			mov a,edx


	}
	if (a == 1)
		cout << "Nechetnoe" << endl;
	else
		cout << "Chetnoe" << endl;
	system("pause");
	return 0;
}