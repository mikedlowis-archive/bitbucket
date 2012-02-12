#ifndef LIST_H
#define LIST_H 

#include <stdarg.h>
#include "type.h"

class List : public Type
{
	private:
		type_ptr lst_head;
		type_ptr lst_tail;
	public:
		List(Type* hd, List* tl);
		List(int count, ...);
		~List(void);
		const std::type_info& type(void) const;
		const std::string toString(void) const;
		const type_ptr& head(void) const;
		const type_ptr& tail(void) const;
};

#endif
