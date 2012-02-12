#include "gc_obj.h"

gc_obj::gc_obj() : ref_count(0) 
{
}

gc_obj::~gc_obj() 
{
}

void gc_obj::incRefCount(void)
{
	ref_count++;
}

void gc_obj::decRefCount(void)
{
	if ( (--ref_count) == 0 )
	{
		delete this;
	}
}


