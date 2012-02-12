#include "ast.h"
#include <stdlib.h>

static Node_T* New_ASTValNode(int type, Value_T value);

// Private --------------------------------------------------------------------
static Node_T* New_ASTValNode(int type, Value_T value)
{
	ValueNode_T* node = (ValueNode_T*) malloc( sizeof(ValueNode_T) );
	node->node_type = type;
	node->value = value;
	return (Node_T *) node;
}

// Public ---------------------------------------------------------------------
Node_T* NODE(int type, int child_count, ...)
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

Node_T* VAL_CHAR(char value)
{
	Value_T val;
	val.Char = value;
	return New_ASTValNode(CHAR, val);
}

Node_T* VAL_INT(int value)
{
	Value_T val;
	val.Int = value;
	return New_ASTValNode(INT, val);
}

Node_T* VAL_LONG(long int value)
{
	Value_T val;
	val.Long = value;
	return New_ASTValNode(LONG, val);
}

Node_T* VAL_FLOAT(double value)
{
	Value_T val;
	val.Float = value;
	return New_ASTValNode(FLOAT, val);
}

Node_T* VAL_STRING(char* value)
{
	Value_T val;
	val.String = value;
	return New_ASTValNode(STRING, val);
}

