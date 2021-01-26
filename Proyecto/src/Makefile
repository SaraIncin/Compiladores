CXX=gcc
BIN=recursive_parser
INC=headers

SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.c)

all: flex fin

fin: lex.yy.c tokens.c tipo.c simbolo.c lista.c parser.c main.c
	$(CXX) -I$(INC) -g -o $(BIN) $^ 

%.o: %.c
	$(CXX) $@ -c $<

.PHONY: clean
clean :
	rm -f $(BIN) *.o lex.yy.c

.PHONY: flex
flex:
	flex lexer.lex
