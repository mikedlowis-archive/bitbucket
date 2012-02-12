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
#include "eval.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

STATIC void Eval_PrintSymbol(Symbol_T* symbol);
STATIC Symbol_T* Eval_EvalExpression(HashTable_T* symbols, Node_T* ast);
STATIC Symbol_T* Eval_EvalSymbol(HashTable_T* symbols, Node_T* ast);
STATIC Symbol_T* Eval_EvalOperation(HashTable_T* symbols, Node_T* ast);
STATIC Symbol_T* Eval_EvalBinaryOperation(HashTable_T* symbols, Node_T* ast);

/******************************************************************************
 * Public Functions
 *****************************************************************************/
void Eval_EvalStmnt(HashTable_T* symbols, Node_T* ast)
{
	Symbol_T* symbol = Eval_EvalExpression(symbols,ast);
	Eval_PrintSymbol(symbol);
}

/******************************************************************************
 * Private Functions
 *****************************************************************************/
STATIC void Eval_PrintSymbol(Symbol_T* symbol)
{
	if (symbol != NULL)
	{
		printf("\t=>\t");
		switch (symbol->type)
		{
			case EVAL_FLOAT:
				printf("%g\n", symbol->value.Float);
				break;

			default:
				break;
		}
	}
}


STATIC Symbol_T* Eval_EvalExpression(HashTable_T* symbols, Node_T* ast)
{
	Symbol_T* symbol = (Symbol_T*)malloc( sizeof(Symbol_T) );
	if (ast->node_type > 250) // Is a value node
	{
		symbol = Eval_EvalSymbol(symbols, ast);	
	}
	else // Is an operation node
	{
		symbol = Eval_EvalOperation(symbols, ast);
	}
	
	return symbol;
}

STATIC Symbol_T* Eval_EvalSymbol(HashTable_T* symbols, Node_T* ast)
{
	Symbol_T* symbol = (Symbol_T*) malloc( sizeof(Symbol_T) );
	switch (ast->node_type)
	{
		case FLOAT:
			symbol->type = EVAL_FLOAT;
			symbol->value.Float = ((ValueNode_T*)ast)->value.Float;
			break;

		default:
			free(symbol);
			symbol = NULL;
			break;
	}	
	return symbol;
}

STATIC Symbol_T* Eval_EvalOperation(HashTable_T* symbols, Node_T* ast)
{
	Symbol_T* symbol = NULL;
	U32 num_children = LL_Length( ast->children );
	if ( num_children == 2 )
	{
		symbol = Eval_EvalBinaryOperation(symbols,ast);
	}
	else
	{
		// Do more complex operations
	}
	return symbol;
}

STATIC Symbol_T* Eval_EvalBinaryOperation(HashTable_T* symbols, Node_T* ast)
{
	Symbol_T* symbol = (Symbol_T*)malloc( sizeof(Symbol_T) );
	LinkedList_T* child1 = LL_Get(ast->children, 0);
	LinkedList_T* child2 = LL_Get(ast->children, 1);
	Symbol_T* param1 = Eval_EvalExpression( symbols, child1->contents );
	Symbol_T* param2 = Eval_EvalExpression( symbols, child2->contents );
	switch ( ast->node_type )
	{
		case ADD:
			symbol->type = EVAL_FLOAT;
			symbol->value.Float = param1->value.Float + param2->value.Float;
			break;
		
		case SUB:
			symbol->type = EVAL_FLOAT;
			symbol->value.Float = param1->value.Float - param2->value.Float;
			break;
		
		case MUL:
			symbol->type = EVAL_FLOAT;
			symbol->value.Float = param1->value.Float * param2->value.Float;
			break;
		
		case DIV:
			symbol->type = EVAL_FLOAT;
			symbol->value.Float = param1->value.Float / param2->value.Float;
			break;
	
		default:
			break;
	}
	return symbol;
}

