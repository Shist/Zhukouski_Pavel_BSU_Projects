#include "global.h"

int lookahead;

void parse()
{
	lookahead = lexan();
	if (lookahead != DONE) {	// ������ while �� if, ����� ��������� ���� ���� ���������
		expr();
		//match(';');
	}
	if (lookahead != DONE) {	// ���������, ��� ������ ��������� ������ ����
		error("syntax error: more than one expression");
	}
}

void expr()
{
	int t;
	term();
	while (1) {
		switch (lookahead) {
		case '+': case '-':
			t = lookahead;
			match(lookahead);
			term();
			emit(t, NONE);
			continue;
		default:
			return;
		}
	}
}

void term()
{
	int t;
	factor();
	while (1) {
		switch (lookahead) {
		case '*': case '/': case DIV: case MOD:
			t = lookahead;
			match(lookahead);
			factor();
			emit(t, NONE);
			continue;
		default:
			return;
		}
	}
}

void factor()
{
	switch (lookahead) {
	case '(': 
		match('('); 
		expr(); 
		match(')'); 
		break;
	case NUM: 
		emit(NUM, tokenval); 
		match(NUM); 
		break;
	case ID: 
		emit(ID, tokenval); 
		match(ID); 
		break;
	default:
		error("factor: syntax error");
	}
}

void match(int t)
{
	if (lookahead == t)
		lookahead = lexan();
	else
		error("match: syntax error");
}