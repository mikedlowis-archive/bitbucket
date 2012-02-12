/******************************************************************************
 *  Copyright (C) 2001  Michael D. Lowis
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
/******************************************************************************
 * Includes and Prototypes
 *****************************************************************************/
#include <stdio.h>
#include "parse.h"
#include "lex.yy.h"

/******************************************************************************
 * Public Functions
 *****************************************************************************/
void Parse_ParseInput(HashTable_T* symbols, FILE* in_file)
{
	if ( in_file != NULL )
	{
		ParseContext_T context = { NULL, symbols};
		context.symbols = symbols;
		yylex_init( &(context.lexinfo) );
		yyset_in( in_file, context.lexinfo );
		yyparse( &context );
	}
}

void Parse_ParseFile(HashTable_T* symbols, String in_file)
{
	FILE* input_file = fopen( in_file ,"r");
	Parse_ParseInput( symbols, input_file );
}

void yyerror(ParseContext_T* context, String s)
{
	fprintf(stderr,"Error: %s\n",s);
}

