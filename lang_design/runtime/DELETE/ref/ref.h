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

template <class T>
class Ref {
	protected:
		T* ptr;
	private:
		// Disallow instantiation without a parameter
		Ref() : ptr(0) {}
		// Disallow direct instantiation on the heap
		void*operator new( size_t );
  		void* operator new[]( size_t );
		void operator delete( void* );
		void operator delete[]( void* );
	public:
		Ref(T* p = 0);
		Ref(const Ref& right);
		~Ref();
		//Ref<T> operator [] (unsigned int index);
		T* value(void);
		Ref<T>& operator = (Ref<T>& right);
		Ref<T>& operator = (T* right);
		T& operator * (void);
		T* operator -> (void);
		std::string type(void);
};

template <class T>
Ref<T>::Ref(T* p) : ptr(p)
{
	if (ptr != 0)
	{
		ptr->incRefCount();
	}
}

template<class T>
Ref<T>::Ref(const Ref& right) : ptr(right.ptr)
{ 
	if (ptr != 0)
	{
		ptr->incRefCount();
	}
}

template <class T>
Ref<T>::~Ref()
{
	if (ptr != 0)
	{
		ptr->decRefCount();
	}
}

template <class T>
T* Ref<T>::value(void)
{
	return ptr;
}

/*template <class T>*/
//Ref<T> Ref<T>::operator [] (unsigned int index)
//{
	//return ptr[index];
//}

template <class T>
Ref<T>& Ref<T>::operator = (Ref<T>& right)
{
	ptr->decRefCount();
	ptr = right.value();
	ptr->incRefCount();
	return *this;
}

template <class T>
Ref<T>& Ref<T>::operator = (T* right)
{
	ptr->decRefCount();
	ptr = right;
	ptr->incRefCount();
	return *this;
}

template <class T>
T& Ref<T>::operator * (void)
{
	if(ptr == 0)
	{
		NullRefException null_ref_exception;
		throw null_ref_exception;
	}
	return *ptr;
}

template <class T>
T* Ref<T>::operator -> (void)
{
	if(ptr == 0)
	{
		NullRefException null_ref_exception;
		throw null_ref_exception;
	}
	return ptr;
}

template <class T>
std::string Ref<T>::type(void)
{
	return typeid(this).name();
}

#endif
