#include <iostream>
#include <sstream>
#include "type.h"

/******************************************************************************
 * Constructors and Destructors
 *****************************************************************************/
Type::Type() : ref_count(0)
{
}

//Type::~Type()
//{
//}

/******************************************************************************
 * Garbage Collection Methods
 *****************************************************************************/
int Type::refCount(void)
{
	return ref_count;	
}

void Type::incRefCount(void)
{
	++ref_count;
}

void Type::decRefCount(void)
{
	std::cout << "removing ref" << std::endl;
	if((--ref_count) == 0)
	{
		std::cout << "deleting self" << std::endl;
		delete this;
	}
}

/******************************************************************************
 * Type Related Methods
 *****************************************************************************/
const Type* Type::value(void) const
{
	return this;
}


const std::type_info& Type::type(void) const
{
	return typeid(this);
}

std::string Type::toString(void) const
{
	std::ostringstream oss;
	oss << "<" << type().name() << ":" << this << ">";
	return oss.str();
}

/******************************************************************************
 * Operators
 *****************************************************************************/
bool Type::operator == (const Type& right) const
{
	return (this == &right) || (value() == right.value());
}

bool Type::operator != (const Type& right) const
{
	return (this != &right) || (value() != right.value());	
}

std::ostream& operator << (std::ostream &out, Type& type)
{
	out << type.toString();
	return out;
}

