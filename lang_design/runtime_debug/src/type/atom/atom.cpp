#include <string>
#include <typeinfo>
#include "atom.h"


std::string Atom::type(void)
{
	return typeid(this).name();
}
