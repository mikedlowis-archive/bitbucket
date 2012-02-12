#include "llvm.h"
#include "grammar.tab.h"
using namespace std;

string LLVM::str()
{
	return stream.str();
}

void LLVM::beforeVisit(AST* cur, int depth)
{
}

void LLVM::afterVisit(AST* cur, int depth)
{
}

void LLVM::beforeChildren(AST* cur, int depth)
{
}

void LLVM::afterChildren(AST* cur, int depth)
{
	cout << "stack: " << buffer.size() << endl;
	switch((int)cur->type())
	{
		// Attributes
		case tVAR:
		case tCONST:
			// These are attributes used by later rules
			break;
		
		// Arithmetic
		case tADD:
		case tSUB:
		case tMUL:
		case tDIV:
		case tMOD:
		case tPOW:
			// Evaluate Expression
			evaluateExpression(cur);
			break;

		// Operators
		case '=':
			assignValue(cur);
			break;
		case tDECL:
			declareValue(cur);
			break;

		// Types
		case tINT:
		case tFLOAT:
		case tID:
		case tSTRING:
			translateLiteral(cur);
			break;

		// If we got a node we don't recognize
		default:
			//displayError();
			break;
	}
}

void LLVM::beforeChild(AST* cur, int depth)
{
}

void LLVM::afterChild(AST* cur, int depth)
{
}

/******************************************************************************
 * Rule Actions
 *****************************************************************************/
 void LLVM::translateLiteral(AST* cur)
 {
 	ostringstream oss;
 	switch(cur->type())
	{
		case tINT:
			oss << "i32 " << cur->text();
			break;
		case tFLOAT:
			oss << "float " << cur->text();
			break;
		case tID:
			oss << "$" << cur->text();
			break;
		case tSTRING:
			oss << "string c" << cur->text();
			break;
		default:
			//displayError();
			break;
	}
	cout << "pushing: " << oss.str() << endl;
	buffer.push(oss.str());
 }

void LLVM::evaluateExpression(AST* cur)
{
	string reg = getTempRegister();
	string src1 = buffer.top();
	buffer.pop();
	string src2 = buffer.top();
	buffer.pop();

	cout << "popping 2 items for: " << typeToString(cur->type()) << endl;
	stream << reg << " = " << getInstruction(cur->type()) << " ";
	stream << src2 << ", " << src1 << endl;
	buffer.push(reg);
}

void LLVM::assignValue(AST* cur)
{
}

void LLVM::declareValue(AST* cur)
{
}

void LLVM::displayError(AST* cur, string msg)
{
}

/******************************************************************************
 * Helper Functions
 *****************************************************************************/
string LLVM::getTempRegister()
{
	ostringstream oss;
	oss << "$" << temp_register++;
	return oss.str();
}

string LLVM::getInstruction(ASTNodeType type)
{
	ostringstream oss;
	switch(type)
	{
		case tADD: oss << "add"; break;
		case tSUB: oss << "sub"; break;
		case tMUL: oss << "mul"; break;
		case tDIV: oss << "div"; break;
		case tMOD: oss << "mod"; break;
		case tPOW: oss << "pow"; break;
		default:
			// displayError();
			break;
	}
	return oss.str();
}

