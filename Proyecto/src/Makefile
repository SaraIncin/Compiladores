CXX=g++
BIN=recursive_parser
INC=headers

SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.c)

all: flex fin

fin: lex.yy.c tokens.cpp tipo.cpp simbolo.cpp parser.cpp codigo.cpp main.cpp 
	$(CXX) -I$(INC) -g -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

.PHONY: clean
clean :
	rm -f $(BIN) *.o lex.yy.c

.PHONY: flex
flex:
	flex lexer.lex
