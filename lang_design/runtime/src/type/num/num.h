#ifndef NUM_H
#define NUM_H 

#include "type.h"

class Num : public Type
{
	protected:
		double val;
	public:
		Num(double num);
		~Num(void);
		const std::type_info& type(void) const;
		const std::string toString(void) const;

		double value(void) const;

		const type_ptr operator + (Num& right) const;
		const type_ptr operator - (Num& right) const;
		const type_ptr operator * (Num& right) const;
		const type_ptr operator / (Num& right) const;
};

#endif
