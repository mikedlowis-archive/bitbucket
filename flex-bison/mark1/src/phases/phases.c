/******************************************************************************
 *  Copyright (C) 2011 Michael D. Lowis 
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
#include "phases.h"
#include "parse.h"
#include "ast_debug.h"
#include "cl_options.h"

void Phases_Compile(String filename)
{
	// Parsing Phase
	Node_T* tree = Phases_Parse( filename );
	(void)tree;
	// AST_Free( tree );
	
	// Translation Phase
	// Optimization Phase
	// Assembly Phase
}

Node_T* Phases_Parse(String filename)
{
	Node_T* tree = Parse_ParseFile( filename );
	if ( CLO_GetDebugAST() )
	{
		PrintAST(tree);
	}
	return tree;
}

void Phases_Translate(Node_T* ast)
{
	/* code */
}

void Phases_Optimize(void)
{
	/* code */
}

void Phases_Assemble(void)
{
	/* code */
}

void Phases_Link(void)
{
	/* code */
}

