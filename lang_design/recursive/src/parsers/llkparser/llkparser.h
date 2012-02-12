#ifndef LLK_PARSER_H
#define LLK_PARSER_H

#include <exception>
#include "lexer.h"
#include "ast.h"

class LLKParser
{
	public:
		int k;
		int next;
		Lexer*  lexer;
		Token** lookahead;

		// Constructors
		LLKParser(int k_val, Lexer* lxer);

		// Utility methods
		void consume(void);
		void match(TokenType_T type);
		Token* lookaheadToken(int i);
		TokenType_T lookaheadType(int i);

		// Main parsing function
		virtual AST* parse(void) = 0;
};

#endif
