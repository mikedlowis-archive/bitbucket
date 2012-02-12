#include <stdio.h>

int main(int argc, char** argv)
{
	yyparse();
}

void yyerror(char *s)
{
	fprintf(stderr,"Error: %s\n",s);
}
