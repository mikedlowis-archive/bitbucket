#ifndef LIST_H
#define LIST_H 

#include <stdarg.h>
#include "type.h"
#include "ref.h"

class List : public Type
{
	protected:
		gc_ptr lst_head;
		gc_ptr lst_tail;
	public:
		List(Type* hd, List* tl);
		List(int count, ...);
		~List(){ std::cout << "Deconstructing List: " << this << std::endl; }
		std::string type(void);
		const gc_ptr& head(void) const;
		const gc_ptr& tail(void) const;
};

#endif
