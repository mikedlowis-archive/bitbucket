%{

#include <stdio.h>
#include "ast.h"
#include "ast_debug.h"
#include "parse.h"
#include "lex.yy.h"

#define YYLEX_PARAM context->lexinfo

%}

/******************************************************************************
* Parser Options
******************************************************************************/
%define api.pure
%parse-param { ParseContext_T* context }

/******************************************************************************
* Syntax Tree Values
******************************************************************************/
%union
{
	void * Node;
}

/******************************************************************************
* Tokens
******************************************************************************/
/* Literal Types */
%token <Node>   tBOOL
%token <Node>   tFLOAT
%token <Node>   tSTRING
%token <Node>   tID

/* Math Operators */
%token '+' '-' '*' '/' '%'

/* Logical Operators */
%token tAND tOR tNOT

/* Comparison Operators */
%token tEQ tNE tGT tLT tGTE tLTE

/* Statement Operators */
%token '=' ',' ';' ':' '?'

/* Braces and Parens */
%token '(' ')' '[' ']' '{' '}'

/******************************************************************************
* Rule Return Types
******************************************************************************/
%type <Node>    stmnt
%type <Node>    exp
%type <Node>    literal

/******************************************************************************
* Operator Precedence
******************************************************************************/
%nonassoc tEQ tNE tGT tLT tGTE tLTE
%left '+' '-'
%left '*' '/' '%'
%nonassoc tNOT
%left tAND tOR
%left '?' ':'

/******************************************************************************
* Starting Rule
******************************************************************************/
%start program 

%%

program:
	  /* Nothing */
	| program stmnt                           { NODE_APPEND(context->ast, $2); }
	;

stmnt:
	  tID '=' exp ';'                         { $$ = NODE(ASSIGN, 2, $1, $3 ); }
	| exp ';'                                 { $$ = $1; }
	;
exp:
	/* Mathematical Operators */
	  exp '+' exp                             { $$ = NODE(ADD, 2, $1, $3); }
	| exp '-' exp                             { $$ = NODE(SUB, 2, $1, $3); }
	| exp '*' exp                             { $$ = NODE(MUL, 2, $1, $3); }
	| exp '/' exp                             { $$ = NODE(DIV, 2, $1, $3); }
	| exp '%' exp                             { $$ = NODE(MOD, 2, $1, $3); }

	/* Logical Operators */
	| exp tAND exp                            { $$ = NODE(AND, 2, $1, $3); }
	| exp tOR exp                             { $$ = NODE(OR, 2, $1, $3); }
	| tNOT exp                                { $$ = NODE(NOT, 1, $2); }

	/* Comparison Operators */
	| exp tEQ exp                             { $$ = NODE(EQ, 2, $1, $3); }
	| exp tNE exp                             { $$ = NODE(NE, 2, $1, $3); }
	| exp tLT exp                             { $$ = NODE(LT, 2, $1, $3); }
	| exp tGT exp                             { $$ = NODE(GT, 2, $1, $3); }
	| exp tLTE exp                            { $$ = NODE(LTE, 2, $1, $3); }
	| exp tGTE exp                            { $$ = NODE(GTE, 2, $1, $3); }

	/* Misc */
	| '(' exp ')'                             { $$ = $2; }
	| tID                                     { $$ = $1; }
	| exp '?' exp ':' exp                     { $$ = NODE(TERN, 3, $1, $3, $5); }
	| literal                                 { $$ = $1; }
	;

literal:
	  tBOOL                                   { $$ = $1; }
	| tFLOAT                                  { $$ = $1; }
	;

%%

