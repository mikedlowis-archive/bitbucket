#include "ref.h"
#include "type.h"

#include <iostream>
gc_ptr::gc_ptr(Type* p) : ptr(p)
{
	std::cout << "created" << std::endl;
	if (ptr != 0)
	{
		ptr->incRefCount();
		std::cout << "c_ref " << ptr->ref_count << std::endl;
	}
}

gc_ptr::gc_ptr(const gc_ptr& right) : ptr(right.ptr)
{
	std::cout << "created" << std::endl;
	if (ptr != 0)
	{
		ptr->incRefCount();
		std::cout << "c_ref " << ptr->ref_count << std::endl;
	}
}

gc_ptr::~gc_ptr()
{
	std::cout << "deleted" << std::endl;
	if (ptr != 0)
	{
		std::cout << "b_ref " << ptr->ref_count << std::endl;
		ptr->decRefCount();
		std::cout << "a_ref " << ptr->ref_count << std::endl;
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

std::string gc_ptr::type(void)
{
	return typeid(this).name();
}


