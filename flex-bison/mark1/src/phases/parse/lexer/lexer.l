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
"%" |
 /* Statement Operators */
"=" | 
"," | 
";" | 
":" | 
"?" |
 /* Braces and Parens */
"(" | 
")" |
"{" | 
"}" |
"[" | 
"]"                     { return yytext[0]; }

 /* Logical Operators */
"&&" |
"and"                   { return tAND; }
"||" |
"or"                    { return tOR; }
"!" |
"not"                   { return tNOT; }

 /* Comparison Operators */
"=="                    { return tEQ; }
"!="                    { return tNE; }
">"                     { return tGT; }
"<"                     { return tLT; }
">="                    { return tGTE; }
"<="                    { return tLTE; }

"true" |
"false"                 { yylval->Node = VAL_BOOL( yytext ); return tBOOL; }
{NUM}+(\.{NUM}{NUM}*)?  { yylval->Node = VAL_FLOAT( yytext ); return tFLOAT; }
\"[^\n\r"]*\"           { yylval->Node = VAL_STRING( yytext ); return tSTRING; }
{AL}{ALNUM}*            { yylval->Node = VAL_STRING( yytext ); return tID; }

\/{2}.*\n               ;/* Ignore Comments */
{S}                     ;/* Ignore Whitespace */
.                       { yyerror(yyscanner, yytext); }

%%



