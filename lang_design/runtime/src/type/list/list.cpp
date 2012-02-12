#include <typeinfo>
#include <sstream>
#include "list.h"

List::List(Type* hd, List* tl) : lst_head(hd), lst_tail(tl)
{
}

List::List(int count, ...)
{
	va_list arg_list;
	int i = 0;
	List* prev = NULL;
	va_start (arg_list, count); 
	for (i = 0; i < count; i++)
	{
		prev = new List( va_arg(arg_list, Type*), prev);	
	}
	lst_head = va_arg(arg_list, Type*);
	lst_tail = prev;
	va_end(arg_list);
}

List::~List(void)
{
}

const std::type_info& List::type(void) const
{
	return typeid(this);
}

const std::string List::toString(void) const
{
	std::ostringstream oss;
	oss << "<" << type().name() << ":" << this << ">";
	return oss.str();
}

const type_ptr& List::head(void) const
{
	return lst_head;
}

const type_ptr& List::tail(void) const
{
	return lst_tail;
}

