#include <map>
#include <string>
#include <exception>
#include <iostream>


using namespace std;

extern void * const Nil; // Nil prototype object. Defined here so we can use it inside Prototype

#include "types/prototype.h"
#include "types/object.h"
#include "types/number.h"
#include "types/bool.h"
#include "types/char.h"
#include "types/string.h"
#include "types/vector.h"
#include "types/list.h"
#include "types/block.h"
#include "types/symbol.h"

// Definition of Nil
void * const Nil = new Prototype(NULL);

int main(int argc, char** argv)
{
    Number* aaa = new Number(1.0);
    Number* bbb = new Number(2.1);
    Prototype ccc = (*aaa) + (*bbb);

    Prototype* aa = new Number(1.0);
    Prototype* bb = new Number(2.1);
    Prototype cc = (*aa) + (*bb);

    Number a = Number(1.0);
    Number b = Number(2.1);
    Prototype c = a + b;
}
