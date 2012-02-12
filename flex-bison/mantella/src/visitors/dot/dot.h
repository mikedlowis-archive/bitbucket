#ifndef DOT_H
#define DOT_H 

#include "visitor.h"
#include <iostream>
#include <sstream>
#include <stack>

class DOT : public Visitor {
	protected:
		stack<int> parents;
		ostringstream stream;
		int current_id;
	public:
		DOT(AST* root) : Visitor(root), current_id(0) {};
		string str();
	private:
		void beforeVisit(AST* cur, int depth);
		void afterVisit(AST* cur, int depth);
		void beforeChildren(AST* cur, int depth);
		void afterChildren(AST* cur, int depth);
		void beforeChild(AST* cur, int depth);
		void afterChild(AST* cur, int depth);
};

#endif
