#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <typeinfo>
#include "gc.h"

class Type : public gc_obj
{
	public:
		Type(void);
		~Type(void);

		// Default Type Functionality and Behavior
		virtual const std::type_info& type(void) const = 0;
		virtual const std::string toString(void) const = 0;
		const Type* value(void) const;

		// Overloaded Operators
		bool operator == (const Type& right) const;
		bool operator != (const Type& right) const;
		friend std::ostream& operator << (std::ostream &out, Type& type);
};

typedef	gc_ptr<Type> type_ptr;

#endif
