#include "dot.h"
#include "grammar.tab.h"

using namespace std;

string DOT::str()
{
	return stream.str();
}

void DOT::beforeVisit(AST* cur, int depth)
{
	stream << "digraph {" << endl;	
}

void DOT::afterVisit(AST* cur, int depth)
{
	stream << "}" << endl;
}

void DOT::beforeChildren(AST* cur, int depth)
{
	list<AST*>* children = cur->children();
	stream << "\t" << current_id++ << " [label=\"";
	if ( children->empty() && (!cur->text().empty()))
	{
		stream << cur->text() << "\"]" << endl;	
	}
	else
	{
		stream << typeToString(cur->type()) << "\"]" << endl;	
	}

	if(!parents.empty())
	{
		stream << "\t" << parents.top() << "->" << current_id-1 << endl;
	}
	parents.push(current_id-1);
}

void DOT::afterChildren(AST* cur, int depth)
{
	parents.pop();
}

void DOT::beforeChild(AST* cur, int depth)
{
}

void DOT::afterChild(AST* cur, int depth)
{
}

