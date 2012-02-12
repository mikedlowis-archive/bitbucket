#include "ref.h"
#include "type.h"

#include <iostream>

gc_ptr::gc_ptr(Type* p) : ptr(p)
{
	if (ptr != 0)
	{
		ptr->incRefCount();
	}
}

gc_ptr::gc_ptr(const gc_ptr& right) : ptr(right.ptr)
{
	if (ptr != 0)
	{
		ptr->incRefCount();
	}
}

gc_ptr::~gc_ptr()
{
	if (ptr != 0)
	{
		ptr->decRefCount();
	}
}

Type* gc_ptr::value(void)
{
	return ptr;
}

gc_ptr& gc_ptr::operator = (gc_ptr& right)
{
	ptr->decRefCount();
	ptr = right.value();
	ptr->incRefCount();
	return *this;
}

gc_ptr& gc_ptr::operator = (Type* right)
{
	ptr->decRefCount();
	ptr = right;
	ptr->incRefCount();
	return *this;
}

Type& gc_ptr::operator * (void)
{
	return *ptr;
}

Type* gc_ptr::operator -> (void)
{
	return ptr;
}

