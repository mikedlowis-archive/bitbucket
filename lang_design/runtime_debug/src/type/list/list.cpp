#include <typeinfo>
#include "list.h"

List::List(Type* hd, List* tl) : lst_head(hd), lst_tail(tl)
{
}

std::string List::type(void)
{
	return typeid(this).name();
}

const gc_ptr& List::head(void) const
{
	return lst_head;
}

const gc_ptr& List::tail(void) const
{
	return lst_tail;
}

