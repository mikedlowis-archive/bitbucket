#ifndef GC_OBJ_H
#define GC_OBJ_H 

#include <iostream>

class gc_obj
{
	private:
		unsigned int ref_count;
	public:
		gc_obj();
		virtual ~gc_obj();
		void incRefCount();
		void decRefCount();
};

#endif
