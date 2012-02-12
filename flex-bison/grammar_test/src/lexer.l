NUM      [0-9]
AL       [a-zA-Z]
HEX      [a-fA-F0-9]
ALNUM    [a-zA-Z0-9]
S        [ \n\t]

%{

#include <stdio.h>
#include "grammar.tab.h"
#include "ast.h"
#if DEBUG_LEXER
	#define RET_ENUM(retval) printf("%s",#retval); return retval;
	#define RET_CHAR() printf("%c",yytext[0]); return yytext[0];
	#define RET_AST(retval) \
		yylval.Node = (void*)new AST(retval, yytext); \
		printf("%s",#retval); return retval;
#else
	#define RET_ENUM(retval) return retval;
	#define RET_CHAR() return yytext[0];
	#define RET_AST(retval) \
		yylval.Node = (void*)new AST(retval, yytext); \
		return retval;
#endif
%}

%option noyywrap
%option nounput
%option noinput

%%

\.                          { RET_CHAR(); }
:                           { RET_CHAR(); }
;                           { RET_CHAR(); }
[\[\]\{\}\(\)]              { RET_CHAR(); }

'.'                         { RET_AST( CHAR ); }
:{AL}{ALNUM}*               { RET_AST( ATOM ); }
-?{NUM}+(\.{NUM}{NUM}*)?    { RET_AST( NUM ); }
{AL}{ALNUM}*                { RET_AST( ID ); }

#.*\n                       ;
{S}                         ; //{ printf("%s", yytext); }
.                           ;

%%

