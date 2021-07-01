#include "global.h"

#define STRMAX 999
#define SYMMAX 100

char lexemes[STRMAX] = { '0' };
int  lastchar = -1;

struct entry symtable[SYMMAX];
//int lastentry = 0;
int lastentry = -1;

int lookup(char s[])
{
	int p;
	for (p = lastentry; p >= 0; p--)	// ����� ����������� p >= 0, ����� ������������� � 0-�� ������ �������
		if (strcmp(symtable[p].lexptr, s) == 0)
			return p;
	return -1;	// ���������� -1, � �� 0, ����� �� ���� ���������� � p
}

int insert(char s[], int tok)
{
	int len;
	len = strlen(s);
	if (lastentry + 1 >= SYMMAX)
		error("symbol table full");
	if (lastchar + len + 1 >= STRMAX)
		error("lexemes array full");
	lastentry++;
	symtable[lastentry].token = tok;
	symtable[lastentry].lexptr = &lexemes[lastchar + 1];
	lastchar += len + 1;
	strcpy_s(symtable[lastentry].lexptr, strlen(s)+1, s);

	return lastentry;


}