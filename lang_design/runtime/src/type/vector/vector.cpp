#include <typeinfo>
#include <sstream>
#include <cstdlib>
#include "vector.h"

VectorIndexException out_of_bounds;

Vector::Vector(int count, ...) : start(NULL), end(NULL)
{
	va_list arg_list;
	int i = 0;
	start = new type_ptr[count];
	end   = &start[count-1]; 

	va_start (arg_list, count); 
	for (i = 0; i < count; i++)
	{
		start[i] = va_arg(arg_list, Type*);
	}
	va_end(arg_list);
}

Vector::~Vector(void)
{
	delete [] start;
}

const std::type_info& Vector::type(void) const
{
	return typeid(this);
}

const std::string Vector::toString(void) const
{
	std::ostringstream oss;
	oss << "<" << type().name() << ":" << this << ">";
	return oss.str();
}

const type_ptr& Vector::operator [] (unsigned int index) const
{
	return start[index];
}

