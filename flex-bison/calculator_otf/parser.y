%{

/* Includes */
#include <stdio.h>

%}

%union
{
	double num;
}

/* Tokens */
%token <num> NUM
%token ADD SUB MUL DIV MOD
%token OUBIN OUHEX OUDEC OUOCT /* Output modes */
%token EOL

%type <num> exp
%type <num> factor
%type <num> term

%start calclist 

%%

calclist:
	  /* Nothing */
	| calclist exp EOL       { printf("=> %f\n> ", $2); }
	| calclist EOL           { printf("> "); }
	;

exp:  
	  factor                 { $$ = $1; } 
	| exp ADD factor         { $$ = $1 + $3; }
	| exp SUB factor         { $$ = $1 - $3; }
	;

factor:
	  term                   { $$ = $1; }
	| factor MUL term        { $$ = $1 * $3; }
	| factor DIV term        { $$ = $1 / $3; }
	| factor MOD term        { $$ = ((int) $1) % ((int) $3); }
	;

term:
	  NUM                    { $$ = $1; }
	;

%%

main(int argc, char** argv)
{
	printf("> ");
	yyparse();
}

yyerror(char *s)
{
	fprintf(stderr,"Error: %s\n",s);
}
