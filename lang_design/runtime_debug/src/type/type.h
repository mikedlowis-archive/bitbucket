#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <typeinfo>
#include <iostream>

class gc_ptr;
class Type
{
	protected:
		int ref_count;
	private:
		// Garbage Collection Methods
		int refCount(void);
		void incRefCount(void);
		void decRefCount(void);

		// Make sure References can access the garbage collection methods
		friend class gc_ptr;
	public:
		Type();
		virtual ~Type() { std::cout << "Deconstructing Type: " << this << std::endl; };
		// Default Type Functionality and Behavior
		const Type* value(void) const;
		const std::type_info& type(void) const;
		virtual std::string type(void) = 0;
		std::string toString(void) const;
		bool operator == (const Type& right) const;
		bool operator != (const Type& right) const;
		friend std::ostream& operator << (std::ostream &out, Type& type);
};

#endif
