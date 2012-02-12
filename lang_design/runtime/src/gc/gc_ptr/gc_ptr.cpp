#include "gc_ptr.h"

/*gc_ptr::gc_ptr(gc_obj* p) : ptr(p)*/
//{
	//if (ptr != 0)
	//{
		//ptr->incRefCount();
	//}
//}

//gc_ptr::gc_ptr(const gc_ptr& right) : ptr(right.ptr)
//{
	//if (ptr != 0)
	//{
		//ptr->incRefCount();
	//}
//}

//gc_ptr::~gc_ptr()
//{
	//if (ptr != 0)
	//{
		//ptr->decRefCount();
	//}
//}

//gc_obj* gc_ptr::value(void)
//{
	//return ptr;
//}

//gc_ptr& gc_ptr::operator = (gc_ptr& right)
//{
	//ptr->decRefCount();
	//ptr = right.value();
	//ptr->incRefCount();
	//return *this;
//}

//gc_ptr& gc_ptr::operator = (gc_obj* right)
//{
	//ptr->decRefCount();
	//ptr = right;
	//ptr->incRefCount();
	//return *this;
//}

//gc_obj& gc_ptr::operator * (void)
//{
	//return *ptr;
//}

//gc_obj* gc_ptr::operator -> (void)
//{
	//return ptr;
//}

