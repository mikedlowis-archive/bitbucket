#include <iostream>
#include "runtime.h"
#include "cork.h"

using namespace std;

void test_vectors(void)
{
	type_ptr foo = _new Vector(3, _new Atom(), _new Atom(), _new Atom());
}

void test_atoms(void)
{
	Atom foo;
	Atom True;
	if(foo.value() == foo.value()) cout << "yes!" << endl;
	if(foo == foo) cout << "yes!" << endl;
	if(foo == True) cout << "yes!" << endl;
	if(foo.value() == True.value()) cout << "yes!" << endl;
	cout << foo << endl;
	cout << sizeof(foo) << endl;
	cout << sizeof(Atom) << endl;
}

void test_gc(void)
{
	type_ptr ref1( _new Atom() );
	type_ptr ref2(_new Atom());
	type_ptr ref3(ref2);
	type_ptr ref4( _new List(_new Atom(), 0) );

	Atom foo1 = *(cast<Atom>(ref2.value()));
	Type* t1 = ref2.value();
	Atom* t2 = cast<Atom>(t1);
	(void)t2;

	try
	{
		type_ptr ref((Atom*)0);
		Atom foo = *(cast<Atom>(ref.value()));
		(void) foo;
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
	}

	// Explicit heap allocation is disallowed:
	//type_ptr* foo = _new Ref<Atom>(_new Atom());
}

void test_lists(void)
{
	type_ptr foo( _new List( 2, _new Atom(), _new Atom() ) );
	cout << *foo << endl;
	cout << foo->toString() << endl;
}

void test_nums(void)
{
	type_ptr a = _new Num(2);
	type_ptr b = _new Num(3);

	type_ptr c = *(cast<Num>(a)) + *(cast<Num>(b));
	cout << "2 + 3 = " << *c << endl;
	
	type_ptr d = *(cast<Num>(a)) - *(cast<Num>(b));
	cout << "2 - 3 = " << *d << endl;

	type_ptr e = *(cast<Num>(a)) * *(cast<Num>(b));
	cout << "2 * 3 = " << *e << endl;

	type_ptr f = *(cast<Num>(a)) / *(cast<Num>(b));
	cout << "2 / 3 = " << *f << endl;
}

void test_funcs(void)
{
}

int main(int argc, char** argv)
{
	test_vectors();
	test_atoms();	
	test_lists();
	test_gc();

	test_nums();
	test_funcs();

	REPORT_LEAKS();
	return 0;
}
