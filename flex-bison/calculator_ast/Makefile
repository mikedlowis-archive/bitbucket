# Tools
LEX=flex
BISON=bison
CC=gcc

# File Locations
GRAMMAR_FILE=src/parser.y
TOKENS_FILE=src/lexer.l
APP_NAME=parser

INCLUDE_PATH= \
	-I. \
	-Isrc \
	-Isrc/ast \
	-Isrc/linked_list

SRC_FILES= \
	src/main.c \
	parser.tab.c \
	lex.yy.c \
	src/ast/ast.c \
	src/ast/ast_debug.c \
	src/linked_list/linked_list.c

#------------------------------------------------------------------------------

all: clean test $(APP_NAME).exe

$(APP_NAME).exe: $(SRC_FILES) 
	$(CC) -o $(APP_NAME) $(INCLUDE_PATH) $(SRC_FILES)

clean:
	rake clobber
	rm -f lex.yy.c
	rm -f parser.tab.c
	rm -f parser.tab.h
	rm -f $(APP_NAME).exe
	rm -f test.bmp

test:
	rake

#------------------------------------------------------------------------------

parser.tab.c: $(GRAMMAR_FILE) 
	$(BISON) -d $(GRAMMAR_FILE)

lex.yy.c: $(TOKENS_FILE)
	$(LEX) $(TOKENS_FILE)

