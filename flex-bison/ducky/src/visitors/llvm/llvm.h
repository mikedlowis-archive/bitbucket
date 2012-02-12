#ifndef LLVM_H
#define LLVM_H 

#include "visitor.h"
#include <sstream>
#include <stack>

class LLVM : public Visitor {
	protected:
		ostringstream stream;
		stack<string> buffer;
		int temp_register;
	public:
		LLVM(AST* root) : Visitor(root), temp_register(0) {};
		string str();
	private:
		// Visitor Actions
		void beforeVisit(AST* cur, int depth);
		void afterVisit(AST* cur, int depth);
		void beforeChildren(AST* cur, int depth);
		void afterChildren(AST* cur, int depth);
		void beforeChild(AST* cur, int depth);
		void afterChild(AST* cur, int depth);

		// Tree Parsing Actions
 		void translateLiteral(AST* cur);
		void evaluateExpression(AST* cur);
 		void assignValue(AST* cur);
 		void declareValue(AST* cur);
 		void displayError(AST* cur, string msg);

		// Helper Methods
		string getTempRegister();
		string getInstruction(ASTNodeType type);
};

#endif
