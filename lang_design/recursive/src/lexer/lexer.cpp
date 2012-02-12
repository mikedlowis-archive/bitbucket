#include <exception>
#include "lexer.h"

Lexer::Lexer() : line(-1), column(-1), input(&std::cin)
{
	consume();
}

Lexer::Lexer(std::string in) : line(-1), column(-1)
{
	input = new std::istringstream(in);
	consume();
}

Lexer::Lexer(std::istream* in) : line(-1), column(-1), input(in)
{
	consume();
}

bool Lexer::eof(void)
{
	return ((input == NULL) || (input->eof()));
}

void Lexer::consume(void)
{
	if(input->eof())
	{
		current = EOF;
	}
	else
	{
		current = input->get(); 
		if(current == '\n')
		{
			line++;
			column = 0;
		}
		else
		{
			column++;
		}
	}
}

void Lexer::match(char x) {
	if ( current == x)
	{
		consume();
	}
	else 
	{
		throw std::exception();
	}
}


