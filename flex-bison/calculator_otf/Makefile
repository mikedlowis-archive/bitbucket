LEX=flex
BISON=bison
CC=gcc

#------------------------------------------------------------------------------

all: parser.exe

parser.exe: parser.tab.c lex.yy.c 
	$(CC) -o parser parser.tab.c lex.yy.c

clean:
	rm -f lex.yy.c
	rm -f lexer.exe
	rm -f parser.tab.c
	rm -f parser.tab.h
	rm -f parser.exe

#------------------------------------------------------------------------------

parser.tab.c: parser.y 
	$(BISON) -d parser.y

lex.yy.c: lexer.l
	$(LEX) lexer.l

