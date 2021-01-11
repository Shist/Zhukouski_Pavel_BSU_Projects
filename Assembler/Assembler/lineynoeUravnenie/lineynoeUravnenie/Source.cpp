#include <iostream>
using namespace std;
int main() {
	int a, b, x, ost;
	cin >> a >> b;
	_asm {
		mov eax,b
		mov ecx,-1
		imul ecx

		cdq
		idiv a

		mov x, eax
		mov ost,edx
	}
	cout << "x = " << x << " " << ost <<"/"<<a<<endl;
	system("pause");
	return 0;
}