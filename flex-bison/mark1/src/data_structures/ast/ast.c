/******************************************************************************
 *  Copyright (C) 2011  Michael D. Lowis
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
 ******************************************************************************/

#include "ast.h"
#include <stdlib.h>
#include <string.h>

static Node_T* New_ASTValNode(NodeType_T type, Value_T value);

/******************************************************************************
 * Private Functions
 ******************************************************************************/
static Node_T* New_ASTValNode(NodeType_T type, Value_T value)
{
	ValueNode_T* node = (ValueNode_T*) malloc( sizeof(ValueNode_T) );
	node->node_type = type;
	node->value = value;
	return (Node_T *) node;
}

/******************************************************************************
 * Public Functions
 ******************************************************************************/
Node_T* NODE(NodeType_T type, int child_count, ...)
{
	va_list arg_list;
	int i = 0;
	Node_T* node = (Node_T*) malloc( sizeof(Node_T) );
	node->node_type = type;
	node->children = NULL;
	
	va_start (arg_list, child_count); 
	for (i = 0; i < child_count ; i++)
	{
		if (node->children == NULL)
		{
			node->children = LL_New( va_arg(arg_list, Node_T*) );
		}
		else
		{
			LL_Add(node->children, va_arg(arg_list, Node_T*));
		}
	}
	va_end(arg_list);
	
	return (Node_T*) node;
}

Node_T* NODE_APPEND(Node_T* node, Node_T* child)
{
	if (node->children == NULL)
	{
		node->children = LL_New( child );
	}
	else
	{
		LL_Add(node->children, child);
	}
	return node;
}

Node_T* VAL_BOOL(char* value)
{
	Value_T val;
	val.Boolean = (strcmp(value,"true") == 0) ? TRUE : FALSE;
	return New_ASTValNode(FLOAT, val);
}

Node_T* VAL_INT(char* value)
{
	Value_T val;
	val.Integer = atoi(value);
	return New_ASTValNode(INT, val);
}

Node_T* VAL_FLOAT(char* value)
{
	Value_T val;
	val.Float = atof(value);
	return New_ASTValNode(FLOAT, val);
}

Node_T* VAL_STRING(char* value)
{
	Value_T val;
	val.String = strdup( value );
	return New_ASTValNode(STRING, val);
}

