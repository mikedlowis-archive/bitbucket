#ifndef FUNC_H
#define FUNC_H 

#include "type.h"
#include "vector.h"

class Func : public Type
{
	public:
		~Func(void);
		const std::type_info& type(void) const;
		const std::string toString(void) const;
		virtual type_ptr operator () (Vector& args) const = 0;
};

#endif
