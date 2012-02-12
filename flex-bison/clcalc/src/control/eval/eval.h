#ifndef EVAL_H
#define EVAL_H

#include "ast.h"
#include "hashtable.h"

typedef enum
{
	EVAL_INT,
	EVAL_FLOAT
} SymbolType_T;

typedef union
{
	int    Integer;
	double Float;
} SymbolValue_T;

typedef struct _Symbol_T 
{
	SymbolType_T  type;
	SymbolValue_T value;
} Symbol_T;

void Eval_EvalStmnt(HashTable_T* symbols, Node_T* ast);

#endif
