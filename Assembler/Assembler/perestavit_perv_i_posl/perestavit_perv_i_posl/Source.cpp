#include <iostream>
using namespace std;

int main() {

	int a;
	cin >> a;
	int first, mid, last;
	_asm {
		mov eax, a
		mov ebx, 10
		cdq
		div ebx
		mov first, edx

		mov ecx, 0
		met1:
			cmp eax,0
			je met2
			cdq
			div ebx
			imul ecx,ebx
			add ecx,edx
			jmp met1



			met2:
			mov mid, ecx
			mov eax,ecx
			mov ecx, 0
			cdq
			div ebx
			mov last, edx
			met3:
				cmp eax,0
				je end_
				imul ecx, ebx
				cdq
				div ebx
				add ecx,edx
				jmp met3

		end_:
			mov mid, ecx
	}
	cout << first<<mid<<last;
	return 0;
}