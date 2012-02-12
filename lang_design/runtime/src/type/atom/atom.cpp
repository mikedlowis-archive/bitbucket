#include <string>
#include <typeinfo>
#include <sstream>
#include "atom.h"

Atom::~Atom(void)
{
}

const std::type_info& Atom::type(void) const
{
	return typeid(this);
}

const std::string Atom::toString(void) const
{
	std::ostringstream oss;
	oss << "<" << type().name() << ":" << this << ">";
	return oss.str();
}
