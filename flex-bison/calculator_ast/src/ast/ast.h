#ifndef AST_H
#define AST_H

#include "stdarg.h"
#include "parser.tab.h"
#include "linked_list.h"

// Possible Node Values
union NodeValue
{
	char     Char;
	int      Int;
	long int Long;
	double   Float;
	char*    String;
};

// Structure of Non-Value Node
struct ASTNode 
{
	int node_type;
	LinkedList_T* children;
};

// Structure of Value Node
struct ASTValNode 
{
	int node_type;
	union NodeValue value;
};

// Convenience Types
typedef struct ASTNode    Node_T;
typedef struct ASTValNode ValueNode_T;
typedef union NodeValue   Value_T;

// AST Creating Functions
Node_T* NODE(int type, int child_count, ...);
Node_T* VAL_CHAR(char value);
Node_T* VAL_INT(int value);
Node_T* VAL_LONG(long int value);
Node_T* VAL_FLOAT(double value);
Node_T* VAL_STRING(char* value);

#endif
