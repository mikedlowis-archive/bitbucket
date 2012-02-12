#include <typeinfo>
#include <sstream>
#include "num.h"
#include "cast.h"

Num::Num(double num) : val(num)
{
}

Num::~Num(void)
{
}

const std::type_info& Num::type(void) const
{
	return typeid(this);
}

const std::string Num::toString(void) const
{
	std::ostringstream oss;
	oss << value();
	return oss.str();
}

double Num::value(void) const
{
	return val;
}

const type_ptr Num::operator + (Num& right) const
{
	type_ptr res = new Num( value() + right.value() );
	return res;
}

const type_ptr Num::operator - (Num& right) const
{
	type_ptr res = new Num( value() - right.value() );
	return res;
}

const type_ptr Num::operator * (Num& right) const
{
	type_ptr res = new Num( value() * right.value() );
	return res;
}

const type_ptr Num::operator / (Num& right) const
{
	type_ptr res = new Num( value() / right.value() );
	return res;
}

