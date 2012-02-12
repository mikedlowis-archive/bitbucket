#ifndef ATOM_H
#define ATOM_H 

#include "type.h"

class Atom : public Type 
{
	public:
		~Atom(void);
		const std::type_info& type(void) const;
		const std::string toString(void) const;
};

#endif
