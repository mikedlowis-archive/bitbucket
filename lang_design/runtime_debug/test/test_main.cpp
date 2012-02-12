#include <iostream>
#include "runtime.h"
#include "cork.h"

using namespace std;

int main(int argc, char** argv)
{
	{
	gc_ptr foo1( _new Atom() );
	gc_ptr foo2(
		_new List(
			_new Atom(), 
			_new List(
				_new Atom(),
				0 )));
	}
	REPORT_LEAKS();
	return 0;
}
