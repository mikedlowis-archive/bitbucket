#include <typeinfo>
#include <sstream>
#include "func.h"

Func::~Func(void)
{
}

const std::type_info& Func::type(void) const
{
	return typeid(this);
}

const std::string Func::toString(void) const
{
	std::ostringstream oss;
	oss << "<" << type().name() << ":" << this << ">";
	return oss.str();
}

