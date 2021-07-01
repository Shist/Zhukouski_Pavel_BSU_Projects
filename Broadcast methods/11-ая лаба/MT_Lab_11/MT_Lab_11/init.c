#include "global.h"

struct entry keywords[] = {
	"div", DIV,
	"mod", MOD,
	0, 0
};

void init()
{
	struct entry* p;
	for (p = keywords; p->token; p++)
		insert(p->lexptr, p->token);
}

void error(char* message)
{
	printf("%s\n", message);
	exit(-1);
}