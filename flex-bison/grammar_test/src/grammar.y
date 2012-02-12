%{

#include <stdio.h>
#include "ast.h"

// Text from the lexer
extern char yytext[];

// Function Prototypes
int yylex();
void yyerror(char* s);
void type_to_string(int type);
void print_ast(AST* ast, int depth);

list<AST*> Expressions;

%}

%union
{
	void* Node;
}

/******************************************************************************
* Tokens
******************************************************************************/
/* Literal Types */
%token <Node> CHAR 
%token <Node> NUM
%token <Node> ID
%token <Node> ATOM

/* Virtual Tokens */
%token APPLY FUNC BLOCK ADD LIST VECTOR ELIST EBLOCK

/******************************************************************************
* Rule Return Types
******************************************************************************/
%type <Node>  expression
%type <Node>  literal

/******************************************************************************
* Operator Precedence
******************************************************************************/
%left '+'
%left '.' ':'

/******************************************************************************
* Starting Rule
******************************************************************************/
%start program 

%%

program
	:
	| program expression                                    { Expressions.push_back((AST*)$2); }
	;

expression
	: literal '+' literal                                   { $$ = new AST(ADD, 2, $1, $3); }
	| literal                                               { $$ = $1; } 
	;

literal
	: ID                                                    { $$ = $1; } 
	| NUM                                                   { $$ = $1; } 
	| CHAR                                                  { $$ = $1; } 
	| ATOM                                                  { $$ = $1; } 
	;

%%

void print_ast(AST* ast, int depth)
{
	list<AST*>* children;
	list<AST*>::iterator it;
	
	// Setup our locals
	children = ast->children();
	it = children->begin();

	printf("(");
	type_to_string(ast->type());
	depth++;
	for(; it != children->end(); it++)
	{
		printf(" ");
		print_ast( *it, depth );
	}
	printf(")\n");
}

void type_to_string(int type)
{
	#define CASE(val) \
		case val: \
			printf("%s", #val); \
			break;
	switch( type )
	{
		CASE(CHAR);	
		CASE(NUM);	
		CASE(ID);	
		CASE(ATOM);	
		CASE(APPLY);	
		CASE(FUNC);	
		CASE(BLOCK);	
		CASE(ADD);	
		CASE(LIST);	
		CASE(VECTOR);	
		CASE(ELIST);	
		CASE(EBLOCK);	
		default:
			printf("%d", type);
			break;
	}
}

void yyerror(char* s)
{ 
	fflush(stdout);
	printf("\n%s\n%s\n", "^", s);
}

int main(int argc, char** argv)
{
	yyparse();
	list<AST*>::iterator it;
	it = Expressions.begin();
	for(; it != Expressions.end(); it++)
	{
		print_ast(*it,0);
	}
	return 0;
}
