#include "runtime.h"

DuckyType T_INT    = { "integer" };
DuckyType T_FLOAT  = { "float" };
DuckyType T_STRING = { "string" };
DuckyType T_ARRAY  = { "array" };
DuckyType T_MAP    = { "map" };

DuckyVar Ducky_DeclareVar(DuckyType* type, U32 size)
{
	DuckyVar temp = (DuckyVar)malloc( TYPE_PTR_SIZE + size );
	TYPE(temp) = type;
	return temp;
}

int main()
{
	DuckyVar foo = Ducky_DeclareVar(&T_INT, sizeof(int));
	VALUE(int,foo) = 5;
	return 0;
}

