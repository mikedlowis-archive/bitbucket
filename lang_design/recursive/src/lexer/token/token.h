#ifndef TOKEN_H
#define TOKEN_H 

#include <string>

typedef int TokenType_T;

class Token
{
	private:
		TokenType_T tok_type;
		std::string tok_text;
	public:
		Token(TokenType_T ttype);
		Token(TokenType_T ttype, std::string ttext);
		TokenType_T type();
		const std::string& text();
};

#endif
