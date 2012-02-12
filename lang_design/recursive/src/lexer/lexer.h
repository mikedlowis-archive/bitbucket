#ifndef LEXER_H
#define LEXER_H 

#include <iostream>
#include <sstream>
#include <cstdio>
#include "token.h"

class Lexer
{
	public:
		int line;
		int column;
		char current;
		std::istream* input;

		Lexer();
		Lexer(std::string in);
		Lexer(std::istream* in);
		virtual ~Lexer(){}
		void consume(void);
		void match(char x);
		bool eof(void);
		virtual Token* next(void) = 0;
};

#endif
