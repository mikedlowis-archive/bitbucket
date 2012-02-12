#ifndef REF_H
#define REF_H 

#include <typeinfo>
#include <string>
#include <exception>
#include "type.h"

class NullRefException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Null Reference: A pointer was used without being initialized";
	}
};

class gc_ptr {
	protected:
		Type* ptr;
	private:
		// Disallow direct instantiation on the heap
		void*operator new( size_t );
		void* operator new[]( size_t );
		void operator delete( void* );
		void operator delete[]( void* );
	public:
		gc_ptr(Type* p = 0);
		gc_ptr(const gc_ptr& right);
		~gc_ptr();
		Type* value(void);
		gc_ptr& operator = (gc_ptr& right);
		gc_ptr& operator = (Type* right);
		Type& operator * (void);
		Type* operator -> (void);
};

#endif
