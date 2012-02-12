#include "llkparser.h"

LLKParser::LLKParser(int k_val, Lexer* lxer) : k(k_val), next(0), lexer(lxer)
{
	if ( lexer != NULL )
	{
        lookahead = new Token*[k];
        for (int i = 0; i < k; i++)
		{
			consume();
		}
	}
	else
	{
		throw std::exception();
	}
}

void LLKParser::consume(void)
{
	if ( lookahead != NULL )
	{
		lookahead[next] = lexer->next();
		next = (next + 1) % k;
	}
}

void LLKParser::match(TokenType_T type)
{
	if( lookaheadType(1) == type )
	{
		consume();
	}
	else
	{
		throw std::exception();
	}
}

Token* LLKParser::lookaheadToken(int i)
{
	Token* ret = NULL;
	if( lookahead != NULL )
	{
		ret = lookahead[(next + i - 1) % k];
	}
	return ret; 
}

TokenType_T LLKParser::lookaheadType(int i)
{
	TokenType_T ret = EOF;
	if( lookahead != NULL )
	{
		Token* tok = lookaheadToken(i);
		ret = (tok != NULL) ? tok->type() : EOF;
	}
	return ret;
}


