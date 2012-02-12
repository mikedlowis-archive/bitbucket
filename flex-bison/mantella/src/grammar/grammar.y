%{

#include <stdio.h>
#include <string>
#include <sstream>
#include "parser.h"
#include "common.h"

typedef void* yyscan_t;
#define YYLEX_PARAM context->lexinfo
void yyerror(ParseContext_T* context, const char * s);
%}

%code requires {
#include <string>
#include "ast.h"

string typeToString(unsigned int type);
}

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
	void* Node;
}

%code{
extern int yylex(YYSTYPE * yylval_param ,yyscan_t yyscanner);
}

/******************************************************************************
* Tokens
******************************************************************************/
/* Keywords */
%token tCONST tVAR tFUNC tWHILE tIF tELSE tEND tRET

/* Literal Types */
%token <Node>   tINT
%token <Node>   tFLOAT
%token <Node>   tID
%token <Node>   tSTRING

/* Math Operators */
%token tADD tSUB tMUL tDIV tMOD
%token '+'  '-'  '*'  '/'  '%'
%token tPOW

/* Logical Operators */
%token tAND tOR tNOT

/* Comparison Operators */
%token tEQ tNE tGT tLT tGTE tLTE

/* Statement Operators */
%token tASSIGN
%token '='

/* Braces and Parens */
%token '(' ')' ','

/* Imaginary Node Types */
%token tROOT tDECL tBLOCK tPARMLST tEXPLST tCALL

/******************************************************************************
* Rule Return Types
******************************************************************************/
%type <Node>    block
%type <Node>    stmnt
%type <Node>    if_stmnt
%type <Node>    param_list
%type <Node>    exp_list
%type <Node>    function
%type <Node>    exp
%type <Node>    literal

/******************************************************************************
* Operator Precedence
******************************************************************************/
%nonassoc tEQ tNE tGT tLT tGTE tLTE
%left '+' '-'
%left '*' '/' '%' 
%left tPOW
%nonassoc tNOT
%left tAND tOR

/******************************************************************************
* Starting Rule
******************************************************************************/
%start program 

%%

program
	: /* Nothing */
	| program stmnt                           { context->parser->processAST((AST*)$2); }
	;

block
	: stmnt                                   { $$ = _new AST(tBLOCK, 1, $1); }
	| block stmnt                             { $$ = $1; ((AST*)$$)->addChild((AST*)$2); }

param_list
	: tID                                     { $$ = _new AST(tPARMLST, 1, $1); }
	| param_list ',' tID                      { $$ = $1; ((AST*)$$)->addChild((AST*)$3); }
	;

exp_list
	: exp                                     { $$ = _new AST(tEXPLST, 1, $1); }
	| exp_list ',' exp                        { $$ = $1; ((AST*)$$)->addChild((AST*)$3); }
	;

stmnt
	: tID '=' exp                             { $$ = _new AST(tASSIGN, 2, $1, $3); }
	| if_stmnt                                { $$ = $1; }
	| function                                { $$ = $1; }
	| exp                                     { $$ = $1; }
	;

if_stmnt
	: tIF exp block tEND                      { $$ = _new AST(tIF, 2, $2, $3); }
	| tIF exp block tELSE block tEND          { $$ = _new AST(tIF, 3, $2, $3, $5); }
	;

function
	: tFUNC tID '(' param_list ')' block tEND { $$ = _new AST(tASSIGN, 2, $2, _new AST(tFUNC, 2, $4, $6)); }
	;

exp
	/* Mathematical Operators */
	: exp '+' exp                             { $$ = _new AST(tADD, 2, $1, $3); }
	| exp '-' exp                             { $$ = _new AST(tSUB, 2, $1, $3); }
	| exp '*' exp                             { $$ = _new AST(tMUL, 2, $1, $3); }
	| exp '/' exp                             { $$ = _new AST(tDIV, 2, $1, $3); }
	| exp '%' exp                             { $$ = _new AST(tMOD, 2, $1, $3); }
	| exp tPOW exp                            { $$ = _new AST(tPOW, 2, $1, $3); }

	| exp tEQ exp                             { $$ = _new AST(tEQ, 2, $1, $3); }
	| exp tNE exp                             { $$ = _new AST(tNE, 2, $1, $3); }
	| exp tLT exp                             { $$ = _new AST(tLT, 2, $1, $3); }
	| exp tGT exp                             { $$ = _new AST(tGT, 2, $1, $3); }
	| exp tLTE exp                            { $$ = _new AST(tLTE, 2, $1, $3); }
	| exp tGTE exp                            { $$ = _new AST(tGTE, 2, $1, $3); }

	| exp tAND exp                            { $$ = _new AST(tAND, 2, $1, $3); }
	| exp tOR exp                             { $$ = _new AST(tOR, 2, $1, $3); }
	| tNOT exp                                { $$ = _new AST(tNOT, 1, $2); }

	| tID '(' exp_list ')'                    { $$ = _new AST(tCALL, 2, $1, $3); }
	| '(' exp ')'                             { $$ = $2; }

	/* Literal Values */
	| literal                                 { $$ = $1; }
	;

literal
	: tINT                                    { $$ = $1; }
	| tFLOAT                                  { $$ = $1; }
	| tID                                     { $$ = $1; }
	| tSTRING                                 { $$ = $1; }
	;

%%

void yyerror(ParseContext_T* context, const char * s)
{
	fprintf(stderr,"Error: %s\n", s);
}

std::string typeToString(unsigned int type)
{
	ostringstream oss;
	switch(type)
	{
		case tBLOCK:   oss << "BLOCK"  ; break;
		case tVAR:     oss << "VAR"    ; break;
		case tCONST:   oss << "CONST"  ; break;
		case tADD:     oss << "ADD"    ; break;
		case tSUB:     oss << "SUB"    ; break;
		case tMUL:     oss << "MUL"    ; break;
		case tDIV:     oss << "DIV"    ; break;
		case tMOD:     oss << "MOD"    ; break;
		case tPOW:     oss << "POW"    ; break;
		case tASSIGN:  oss << "ASSIGN" ; break;
		case tDECL:    oss << "DECL"   ; break;
		case tINT:     oss << "INTEGER"; break;
		case tFLOAT:   oss << "FLOAT"  ; break;
		case tID:      oss << "ID"     ; break;
		case tSTRING:  oss << "STRING" ; break;
		case tIF:      oss << "IF"     ; break;
		case tWHILE:   oss << "WHILE"  ; break;
		default:       oss << type     ; break;
	}
	return oss.str();
}

