#ifndef ATOM_H
#define ATOM_H 

#include "type.h"

class Atom : public Type {
	public:
		~Atom(){ std::cout << "Deconstructing Atom: " << this << std::endl; }
		std::string type(void);
};

#endif
