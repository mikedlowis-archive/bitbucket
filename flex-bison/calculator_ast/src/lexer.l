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
"&&"                    { return AND; }
"||"                    { return OR; }
"!"                     { return NOT; }
[\n]                    { return EOL; }
[ \t]                   ;
[0-9]+(\.[0-9][0-9]*)?  { yylval.Float = atof(yytext); return FLOAT; }
.                       { yyerror(yytext); } 

%%
