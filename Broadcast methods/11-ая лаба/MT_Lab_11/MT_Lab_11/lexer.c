#include "global.h"
char	lexbuf[BSIZE];
int		lineno = 1;
int		tokenval = NONE;

int lexan()
{
	char t;
	while (1) {
		t = getchar();
		if (t == ' ' || t == '\t')
			;
		else if (isdigit(t)) {
			ungetc(t, stdin);
			scanf_s("%d", &tokenval);
			return NUM;
		}
		else if (isalpha(t)) {
			int p, b = 0;
			while (isalnum(t)) {
				lexbuf[b++] = t;
				t = getchar();
				if (b >= BSIZE)
					error("compiler error");
			}
			lexbuf[b] = EOS;
			ungetc(t, stdin);	// ������� �������� �� '#', ��� ��� � ��� ���� ����� �������
			p = lookup(lexbuf);
			if (p == -1)	// ����� ��������� �� -1, ��� ��� � lookup() ���������� -1
				p = insert(lexbuf, ID);
			tokenval = p;
			return symtable[p].token;
		}
		else if (t == '#')
			return DONE;
		else {
			tokenval = NONE;
			return t;
		}
	}
}