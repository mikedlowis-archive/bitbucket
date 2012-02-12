#ifndef CAST_H
#define CAST_H 

#include "type.h"

class BadCastException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Bad Cast: Incompatible types";
	}
};

template <class T>
T* cast(type_ptr ptr)
{
	T* new_ptr = dynamic_cast<T*>( ptr.value() );
	if (!new_ptr) 
	{
		throw BadCastException();
	}
	return new_ptr;
}

#endif
