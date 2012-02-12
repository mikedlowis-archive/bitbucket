#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstdio>

#include "lexer.h"
#include "llkparser.h"
#include "sexp.h"

using namespace std;

typedef enum LexException
{
	UnexpectedCharacter,
	InvalidCharacter
} LexException_T;

typedef enum TokenTypes
{
	ID      = 0,
	NUM     = 1,
	CHAR    = 2,
	LBRACK  = 3,
	RBRACK  = 4,
	LPAR    = 5,
	RPAR    = 6,
	LBRACE  = 7,
	RBRACE  = 8,
	COMMA   = 9,
	PIPE    = 10,

	// AST Node Types
	PROGRAM = 11,
	VECTOR  = 12,
	LIST    = 13,
	BLOCK   = 14,
	FUNC    = 15
} eTokenTypes;

class LambdaLexer : public Lexer {
	public:
		LambdaLexer() : Lexer() {}
		LambdaLexer(std::string in) : Lexer(in) {}
		LambdaLexer(std::istream* in) : Lexer(in) {}

		bool isWhiteSpace(void)
		{
			return (current == ' ') ||
				   (current == '\t') ||
				   (current == '\r') ||
				   (current == '\n');
		}

		bool isLetter(void)
		{
			return  ((current >= 'a') && (current <= 'z')) ||
					((current >= 'A') && (current <= 'Z'));
		}

		bool isDigit(void)
		{
			return ((current >= '0') && (current <= '9'));
		}

		Token* next(void)
		{
			while ( ! input->eof() )
			{
				if (isWhiteSpace()) 
				{ 
					WS(); 
				}
				else if (isLetter())
				{
					return Id();
				}
				else if (isDigit())
				{
					return Number();
				}
				else
				{
					switch (current)
					{
						case '\'':
							return Char();	
						case '|':
							consume(); return new Token(PIPE);
						case '[':
							consume(); return new Token(LBRACK);
						case ']':
							consume(); return new Token(RBRACK);
						case '(':
							consume(); return new Token(LPAR);
						case ')':
							consume(); return new Token(RPAR);
						case '{':
							consume(); return new Token(LBRACE);
						case '}':
							consume(); return new Token(RBRACE);
						case ',':
							consume(); return new Token(COMMA);
						default:
							throw InvalidCharacter;
					}
				}
			}
			return NULL;
		}

		void WS(void)
		{
			do
			{
				consume();
			}
			while(isWhiteSpace());
		}

		Token* Id(void)
		{
			ostringstream oss;
			do
			{
				oss << current;
				consume();
			}
			while(isLetter() || isDigit() || current == '_');
			return new Token(ID, oss.str());
		}

		Token* Number(void)
		{
			ostringstream oss;
			do
			{
				oss << current;
				consume();
			}
			while(isDigit());

			if(current == '.')
			{
				return Decimal(oss);
			}

			return new Token(NUM, oss.str());
		}

		Token* Decimal(ostringstream& oss)
		{
			oss << current;
			consume();
			
			if(!isDigit())
			{
				throw UnexpectedCharacter;
			}
			
			do
			{
				oss << current;
				consume();
			}
			while ( isDigit() );

			return new Token(NUM,oss.str());
		}

		Token* Char(void)
		{
			ostringstream oss;

			match('\'');
			if(current != '\'')
			{
				oss << current;
				consume();
			}
			else
			{
				throw UnexpectedCharacter;
			}
			match('\'');

			return new Token( CHAR, oss.str() );
		}
};

class LambdaParser : public LLKParser
{
	public:
		LambdaParser(std::string in) : LLKParser(2,new LambdaLexer(in))
		{
		}

		LambdaParser(std::istream* in) : LLKParser(2,new LambdaLexer(in))
		{
		}

		AST* parse(void)
		{
			return program();
		}

		AST* program(void)
		{
			AST* node = new AST( PROGRAM );
			while( lookaheadType(1) != EOF )
			{
				node->addChild( expression() );
			}
			return node;
		}

		AST* expression(void)
		{
			return literal();
		}

		AST* literal(void)
		{
			AST* node = NULL;
			AST* child1 = NULL;
			AST* child2 = NULL;
			switch(lookaheadType(1))
			{
				// Literal = '[' ExpList? ']'
				case LBRACK:
					match(LBRACK);
					node = explist(VECTOR, RBRACK);
					match(RBRACK);
					break;

				// Literal = '(' ExpList? ')'
				case LPAR:
					match(LPAR);
					node = explist(LIST, RPAR);
					match(RPAR);
					break;

				// Literal = '{' ExpBlock? '}'
				case LBRACE:
					match(LBRACE);
					node = expblock(BLOCK,RBRACE);
					match(RBRACE);
					break;

				// Literal = '|' ExpList '|' '{' ExpBlock? '}'
				case PIPE:
					match(PIPE);
					child1 = explist(LIST, PIPE);
					match(PIPE);
					match(LBRACE);
					child2 = expblock(BLOCK, RBRACE);
					match(RBRACE);
					node = new AST(FUNC, 2, child1, child2);
					break;

				// Literal = ID
				case ID:
					node = new AST( ID,(char*)(lookaheadToken(1)->text().c_str()) );
					consume(); 
					break;

				// Literal = NUM
				case NUM:
					node = new AST( NUM,(char*)(lookaheadToken(1)->text().c_str()) );
					consume();
					break;

				// Literal = CHAR
				case CHAR:
					node = new AST( CHAR,(char*)(lookaheadToken(1)->text().c_str()) );
					consume(); 
					break;

				default:
					throw "Unexpected Token";
			}
			return node;
		}

		// ExpList = (Expression (',' Expression)*)?
		AST* explist(TokenType_T node_type, TokenType_T terminator)
		{
			AST* node = new AST( node_type );
			if(lookaheadType(1) != terminator)
			{
				node->addChild( expression() );
				while(lookaheadType(1) == COMMA)
				{
					match(COMMA);
					node->addChild( expression() );
				}
			}
			return node;
		}
		
		// ExpBlock = Expression+
		AST* expblock(TokenType_T node_type, TokenType_T terminator)
		{
			AST* node = new AST(node_type);
			while(lookaheadType(1) != RBRACE)
			{
				node->addChild( expression() );
			}
			return node;
		}
};

int main(int argc, char** argv)
{
	istringstream input("asd asd1 as1d a_sd a_s1d 1 1.0 1.1 'a' 'b' 'c' [ ] ( ) { } [ 1, 'a', abc, [a]] { 1 2 3 { 1 } {} } ||{} |a,b,c,d|{ a b c d }");
	LambdaParser parser(&input);
	AST* ast = parser.parse();
	Visitor* visitor = new SEXP(ast);
	visitor->visit();
	cout << visitor->str();
	return 0;
}
