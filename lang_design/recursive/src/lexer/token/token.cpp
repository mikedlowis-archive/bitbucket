#include "token.h"

Token::Token(TokenType_T ttype, std::string ttext) : tok_type(ttype), tok_text(ttext)
{
}

Token::Token(TokenType_T ttype) : tok_type(ttype)
{
}

TokenType_T Token::type()
{
	return tok_type;
}

const std::string& Token::text()
{
	return tok_text;
}


