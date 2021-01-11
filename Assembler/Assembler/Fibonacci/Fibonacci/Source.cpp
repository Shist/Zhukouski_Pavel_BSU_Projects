#include <iostream>
using namespace std;
int main() {

	int n;
	cin >> n;
	int buff;
	_asm
	{
		mov edx, n
		mov ebx, 0
		mov ecx, 1
		start:
			cmp edx,0
			je _end
			dec edx

			mov eax, ecx
			add ecx, ebx
			mov ebx, eax

			jmp start
		_end:
			dec ecx
			mov n, ecx 
	}
	cout << n << endl;
	system("pause");
	return 0;
}