#include <iostream>
using namespace std;
int main() {
	char str[100];
	cin.get(str,100);
	cout << str << endl;
	int n;
	_asm {
		mov esi,0
		mov ecx,0
		start_:
			cmp str[esi], 0
			je end_
				inc ecx
				inc esi
				jmp start_
			end_:
				mov n, ecx
	}
	cout << n;
	system("pause");
	return 0;
}