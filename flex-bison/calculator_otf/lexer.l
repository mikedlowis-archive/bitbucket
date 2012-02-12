%{

/* Includes */
#include "parser.tab.h"

%}

%option noyywrap

%%

"+"                     { return ADD; }
"-"                     { return SUB; }
"*"                     { return MUL; }
"/"                     { return DIV; }
"%"                     { return MOD; }
[\n]                    { return EOL; }
[ \t]                   ;
[0-9]+(\.[0-9])?        { yylval.num = atof(yytext); return NUM; }
.                       { yyerror(yytext); } 

%%
