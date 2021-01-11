#include <iostream>
using namespace std;
int main() {
	int a, b;
	cin >> a >> b;
	_asm {
		mov ecx,-1
		mov eax,a
		mov ebx,b
	    cmp eax,0
		jl _less
		jg _beg
		_less: 
			imul ecx
		_beg:
			cmp eax,ebx
				je _stop
				jg gr
				sub ebx,eax
				jmp _beg
			gr:
				sub eax,ebx
				jmp _beg
			_stop:
				mov ecx,eax
				mov eax, a
				cdq 
				idiv ecx
				mov a, eax
				mov eax,b
				cdq
				idiv ecx
				mov b,eax
	}
	cout << a << "/" << b << endl;
	return 0;
}