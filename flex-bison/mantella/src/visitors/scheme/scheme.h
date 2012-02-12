#ifndef Scheme_H
#define Scheme_H 

#include <iostream>
#include <sstream>
#include "visitor.h"
#include "common.h"

class Scheme : public Visitor {
	protected:
		ostringstream stream;
	public:
		Scheme(AST* root) : Visitor(root) {};
		string str();
	private:
		string typeToString();
		void beforeVisit(AST* cur, int depth);
		void afterVisit(AST* cur, int depth);
		void beforeChildren(AST* cur, int depth);
		void afterChildren(AST* cur, int depth);
		void beforeChild(AST* cur, int depth);
		void afterChild(AST* cur, int depth);
		string typeToString(AST* cur);
		BOOL isLiteral(AST* cur);
};

class SchemeFactory : public VisitorFactory {
	public:
		Visitor* createVisitor(AST* root) { return new Scheme(root); }
};

#endif
