#include <iostream>
#include "Windows.h"
using namespace std;

int main() {
	BYTE a1[10] = { 0,5,5,5,5,5,7,8,2,3 };
	BYTE a2[10] = { 0,6,7,1,9,0,9,3,1,8 };
	BYTE sum[10]; 

	_asm {
		mov esi, 9
		mov ecx, 10
		xor bl, bl
		_begin_:
		mov al, bl
			add al, a1[esi]
			add al, a2[esi]
			aaa
			jc m_carry1
			xor bl, bl
			jmp m_carry0
			m_carry1 :
		mov bl, 1
			m_carry0 :
			mov sum[esi], al
			dec esi
			loop _begin_
	}
	for (int i = 0; i < 10; i++)
		cout << " " << (int)sum[i];
	system("pause");
	return 0;
}