#ifndef REF_H
#define REF_H 

#include <typeinfo>
#include <string>
#include <exception>

class NullRefException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Null Reference: A pointer was used without being initialized";
	}
};

template <class T>
class gc_ptr {
	protected:
		T* ptr;
	private:
		// Disallow direct instantiation on the heap
		void*operator new( size_t );
		void operator delete( void* );
	public:
		gc_ptr(T* p = 0);
		gc_ptr(const gc_ptr& right);
		~gc_ptr();
		T* value(void);
		gc_ptr& operator = (gc_ptr& right);
		gc_ptr& operator = (T* right);
		T& operator * (void);
		T* operator -> (void);
};

template <class T>
gc_ptr<T>::gc_ptr(T* p) : ptr(p)
{
	if (ptr != 0)
	{
		ptr->incRefCount();
	}
}

template <class T>
gc_ptr<T>::gc_ptr(const gc_ptr& right) : ptr(right.ptr)
{
	if (ptr != 0)
	{
		ptr->incRefCount();
	}
}

template <class T>
gc_ptr<T>::~gc_ptr()
{
	if (ptr != 0)
	{
		ptr->decRefCount();
	}
}

template <class T>
T* gc_ptr<T>::value(void)
{
	return ptr;
}

template <class T>
gc_ptr<T>& gc_ptr<T>::operator = (gc_ptr& right)
{
	if(ptr) ptr->decRefCount();
	ptr = right.value();
	if(ptr) ptr->incRefCount();
	return *this;
}

template <class T>
gc_ptr<T>& gc_ptr<T>::operator = (T* right)
{
	if(ptr) ptr->decRefCount();
	ptr = right;
	if(ptr) ptr->incRefCount();
	return *this;
}

template <class T>
T& gc_ptr<T>::operator * (void)
{
	return *ptr;
}

template <class T>
T* gc_ptr<T>::operator -> (void)
{
	return ptr;
}

#endif
