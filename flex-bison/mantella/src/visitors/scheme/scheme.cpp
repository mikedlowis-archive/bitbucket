#include "scheme.h"
#include "grammar.tab.h"

using namespace std;

string Scheme::str()
{
	return stream.str();
}

void Scheme::beforeVisit(AST* cur, int depth)
{
}

void Scheme::afterVisit(AST* cur, int depth)
{
	stream << endl;
}

void Scheme::beforeChildren(AST* cur, int depth)
{
	if(isLiteral(cur))
	{
		stream << cur->text();
	}
	else
	{
		stream << "(" << typeToString(cur) << " " << cur->text();
	}
}

void Scheme::afterChildren(AST* cur, int depth)
{
	if(!isLiteral(cur))
	{
		stream << ")";
	}
}

void Scheme::beforeChild(AST* cur, int depth)
{
	stream << endl;
	for(int i = 0; i< depth; i++)
	{
		stream << "  ";
	}
}

void Scheme::afterChild(AST* cur, int depth)
{
}

string Scheme::typeToString(AST* cur)
{
	ostringstream oss;
	switch((int)cur->type())
	{
		case tFUNC:    oss << "lambda"; break;
		case tWHILE:   oss << "while"; break;
		case tIF:      oss << "if"; break;
		case tADD:     oss << "+"; break;
		case tSUB:     oss << "-"; break;
		case tMUL:     oss << "*"; break;
		case tDIV:     oss << "/"; break;
		case tMOD:     oss << "modulo"; break;
		case tPOW:     oss << "pow"; break;
		case tASSIGN:  oss << "define"; break;
		case tBLOCK:   oss << "begin"; break;
		case tCALL:    oss << "apply"; break;
		case tEXPLST:  oss << "list"; break;

		case tEQ:      oss << "eq?"; break;
		case tNE:      oss << "!="; break;
		case tLT:      oss << "<"; break;
		case tGT:      oss << ">"; break;
		case tLTE:     oss << "<="; break;
		case tGTE:     oss << ">="; break;
		case tAND:     oss << "and"; break;
		case tOR:      oss << "or"; break;
		case tNOT:     oss << "not"; break;
	}
	return oss.str();
}

BOOL Scheme::isLiteral(AST* cur)
{
	BOOL ret = FALSE;
	switch(cur->type())
	{
		case tINT:   
		case tFLOAT: 
		case tSTRING: 
		case tID:    ret = TRUE; break;
		default: break;
	}
	return ret;
}

