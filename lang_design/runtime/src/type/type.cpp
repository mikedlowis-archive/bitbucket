#include <iostream>
#include <sstream>
#include "type.h"

/******************************************************************************
 * Constructors and Destructors
 *****************************************************************************/
Type::Type(void)
{
}

Type::~Type(void)
{
}

/******************************************************************************
 * Type Related Methods
 *****************************************************************************/
const Type* Type::value(void) const
{
	return this;
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

