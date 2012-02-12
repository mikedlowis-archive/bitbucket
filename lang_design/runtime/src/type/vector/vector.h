#ifndef ARRAY_H
#define ARRAY_H 

#include <exception>
#include <stdarg.h>
#include "type.h"

class VectorIndexException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "VectorIndexException: Vector index was out of bounds.";
  }
};

class Vector : public Type {
	protected:
		type_ptr* start;
		type_ptr* end;
	public:
		Vector(int count, ...);
		~Vector(void);
		const std::type_info& type(void) const;
		const std::string toString(void) const;
		const type_ptr& operator [] (unsigned int index) const;
};

#endif
