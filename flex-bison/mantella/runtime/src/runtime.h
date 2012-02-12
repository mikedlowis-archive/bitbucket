#ifndef RUNTIME_H
#define RUNTIME_H 

typedef unsigned char Byte;
typedef unsigned int  U32;
typedef Byte* DuckyVar;
typedef struct DuckyType {
	Byte* name;
	DuckyType* parent_type;
} DuckyType;

#define TYPE_PTR_SIZE 4u

DuckyVar Ducky_DeclareVar(DuckyType* type, U32 size);
#define TYPE(name)           *((DuckyType**)name)
#define TYPE_PTR(name)       (((DuckyType**)name)[0])
#define VALUE(type,name)     *((type*)(name + TYPE_PTR_SIZE))
#define VALUE_PTR(type,name) ((type*)(name + TYPE_PTR_SIZE))

#endif
