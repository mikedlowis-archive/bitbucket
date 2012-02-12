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

Node_T* Parse_ParseInput(FILE* in_file);

/******************************************************************************
 * Private Functions
 *****************************************************************************/
Node_T* Parse_ParseInput(FILE* in_file)
{
	Node_T* ast = (Node_T*)malloc(sizeof(Node_T));
	ast->node_type = ROOT;
	ast->children = NULL;

	if ( in_file != NULL )
	{
		ParseContext_T context = { NULL, ast};
		yylex_init( &(context.lexinfo) );
		yyset_in( in_file, context.lexinfo );
		yyparse( &context );
	}

	return ast;
}

/******************************************************************************
 * Public Functions
 *****************************************************************************/
Node_T* Parse_ParseFile(String in_file)
{
	FILE* input_file = fopen( in_file ,"r");
	return Parse_ParseInput( input_file );
}

void yyerror(ParseContext_T* context, String s)
{
	fprintf(stderr,"Error: %s\n",s);
}

//-----------------------------------------------------------------------------

