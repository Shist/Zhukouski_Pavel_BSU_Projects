#include <iostream>
using namespace std;
int main() {

	int a, b, c, x;
	cin >> a >> b >> c >> x;
	int en_buff,den;
	int answer, ost;
	bool flag = false;
	_asm {
		mov ecx, x
		cmp ecx,0
		je DivByZero
		mov eax,a
		mov ebx,-1
		imul ebx
		cdq
		idiv c

		cmp eax,ecx
		je DivByZero
			mov eax,a
			mov ebx,2
			imul c
			imul ecx
			imul ebx

			sub eax,b

			mov ecx,eax
			mov eax,12
			imul x
			sub ecx,eax
			mov en_buff,ecx

			mov eax,x
			imul c
			add eax,a
			imul x
			mov ebx, eax
			mov den,ebx

			mov eax, en_buff
			cdq
			idiv ebx

			mov ost,edx
			mov answer, eax
			mov flag,1
		DivByZero: 
	}
	
	cout << en_buff <<" "<<den<< endl;
	if (!flag) {
		cout << "DBZ" << endl;
	}
	else {
		if (ost < 0 && den < 0)
			den = -den;
		cout << answer << " ost " << ost << "/" << den << " ***** " << (2 * a*c - b / x - 12) / (x*c*x + a*x) << endl;
	}
	system("pause");
	return 0;
}