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
#include "control.h"
#include "parse.h"
#include "ast_debug.h"
#include "cl_options.h"
#include "eval.h"

/******************************************************************************
 * Public Functions
 *****************************************************************************/
void Control_StartInterpreter(HashTable_T* symbols, FILE* input)
{
	Control_DisplayPrompt();
	Parse_ParseInput(symbols, input);
}

void Control_EvalStmnt(HashTable_T* symbols, Node_T* ast)
{
	if( CLO_GetDebugAST() )
	{
	PrintAST(ast);
	}

	Eval_EvalStmnt(symbols,ast);
	// Free AST
	Control_DisplayPrompt();
}

void Control_DisplayPrompt(void)
{
	printf(">> ");
}

void Control_InterpretFile(HashTable_T* symbols, String filename)
{
	Parse_ParseFile(symbols, filename);
}

