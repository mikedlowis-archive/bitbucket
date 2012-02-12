%{

#include <stdio.h>
#include "ast.h"

%}

/* Values Union */
%union
{
	char             Char;
	int              Int;
	long int         Long;
	double           Float;
	char*            String;
	struct ASTNode * Node;
}

/* Tokens */
%token <Char>   CHAR
%token <Int>    INT
%token <Long>   LONG
%token <Float>  FLOAT
%token <String> STRING
%token <Node>   ADD SUB MUL DIV MOD AND OR NOT
%token <Node>   IF WHILE
%token          EOL END

/* Rule Return Types */
%type <Node>    exp
%type <Node>    bool_exp

/* Order of Precedence for Operators */
%left           ADD SUB
%left           MUL DIV MOD
%left           AND OR
%nonassoc       NOT


/* Starting Rule */
%start program 

%%

program:
	| program exp EOL                          { PrintAST($2); }
	;

exp:
	  exp ADD exp                              { $$ = NODE( ADD, 2, $1, $3 ); }
	| exp SUB exp                              { $$ = NODE( SUB, 2, $1, $3 ); }
	| exp MUL exp                              { $$ = NODE( MUL, 2, $1, $3 ); }
	| exp DIV exp                              { $$ = NODE( DIV, 2, $1, $3 ); }
	| exp MOD exp                              { $$ = NODE( MOD, 2, $1, $3 ); } 
	| bool_exp
	| FLOAT                                    { $$ = VAL_FLOAT( $1 ); }
	;

bool_exp:
	  exp AND exp                              { $$ = NODE( AND, 2, $1, $3 ); }
	| exp OR exp                               { $$ = NODE( OR,  2, $1, $3 ); }
	| NOT exp                                  { $$ = NODE( NOT, 1, $2); }
	;

%%

