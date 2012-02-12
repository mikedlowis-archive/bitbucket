/* Pattern Macros */
NUM      [0-9]
AL       [a-zA-Z]
HEX      [a-fA-F0-9]
ALNUM    [a-zA-Z0-9]
S        [ \n\t]

%{

/* Includes */
#include "ast.h"
#include "parse.h"
#include <string.h>

%}

%option reentrant
%option bison-bridge
%option noyywrap
%option nounput
%option noinput

%%

 /* Math Operators*/
"+" | 
"-" | 
"*" | 
"/" | 
";" | 
 /* Braces and Parens */
"(" | 
")"                     { return yytext[0]; }

{NUM}+(\.{NUM}{NUM}*)?  { yylval->Node = VAL_FLOAT( yytext ); return tFLOAT; }

\/{2}.*\n               ;/* Ignore Comments */
{S}                     ;/* Ignore Whitespace */
.                       { yyerror(yyscanner, yytext); }

%%



