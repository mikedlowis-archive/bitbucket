/* Pattern Macros */
NUM      [0-9]
AL       [a-zA-Z]
HEX      [a-fA-F0-9]
ALNUM    [a-zA-Z0-9]
S        [ \n\t]

%{

/* Includes */
#include <string>
#include "ast.h"
#include "parser.h"
#include "grammar.tab.h"

extern void yyerror(ParseContext_T* context, const char * s);

#ifdef DEBUG_LEXER
	#define RET_ENUM(retval) \
		printf("%s\n",#retval); \
		return retval;
	#define RET_CHAR() \
		printf("%c\n", yytext[0]); \
		return yytext[0];
	#define RET_AST(type,retval) \
		printf("%s\n",#type); \
		yylval->Node = new AST( type, yytext ); \
		return type;
#else
	#define RET_ENUM(retval) return retval;
	#define RET_CHAR() return yytext[0];
	#define RET_AST(type) \
		yylval->Node = new AST( type, yytext ); \
		return type;
#endif

%}

%option reentrant
%option bison-bridge
%option noyywrap
%option nounput
%option noinput

%%
 /* Keywords */
"const"                 { RET_ENUM(tCONST); }
"var"                   { RET_ENUM(tVAR); }
"func"                  { RET_ENUM(tFUNC); }
"while"                 { RET_ENUM(tWHILE); }
"if"                    { RET_ENUM(tIF); }
"else"                  { RET_ENUM(tELSE); }
"end"                   { RET_ENUM(tEND); }
"return"                { RET_ENUM(tRET); }

 /* Math Operators*/
"+" | 
"-" | 
"*" | 
"/" | 
"%" |

"(" |
")" |
"," |

"="                         { RET_CHAR(); }
"**"                        { RET_ENUM(tPOW); }

"!="                        { RET_ENUM( tNE ); }
"=="                        { RET_ENUM( tEQ ); }
">"                         { RET_ENUM( tGT ); }
"<"                         { RET_ENUM( tLT ); }
">="                        { RET_ENUM( tGTE ); }
"<="                        { RET_ENUM( tLTE ); }

"&&" |
"and"                       { RET_ENUM( tAND ); }
"||" |
"or"                        { RET_ENUM( tOR ); }
"!" |
"not"                       { RET_ENUM( tNOT ); }

-?{NUM}+                    { RET_AST(tINT); }
-?{NUM}+\.{NUM}{NUM}*       { RET_AST(tFLOAT); }
{AL}{ALNUM}*                { RET_AST(tID); }
[a-zA-Z_]?\"(\\.|[^\\"])*\" { RET_AST(tSTRING); }

#.*\n                       ;/* Ignore Comments */
{S}                         ;/* Ignore Whitespace */
.                           { yyerror((ParseContext_T*)yyscanner, yytext); }

%%



