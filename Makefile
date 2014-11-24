CC=gcc
TARGET=rosh
BISON=bison
FLEX=flex

all : main.c env.c input.c alias.c
	$(CC) -o $(TARGET) main.c env.c input.c alias.c

debug : main.c env.c input.c alias.c
	$(CC) -g -o $(TARGET)  main.c env.c input.c alias.c

test_math :
	$(BISON) -d parse.y
	$(FLEX) parse.lex
	$(CC) parse.tab.c lex.yy.c -lfl -lm -o test_math
	rm parse.tab.c parse.tab.h lex.yy.c

test_str :
	$(BISON) -d string.y
	$(FLEX) string.lex
	$(CC) string.tab.c lex.yy.c -lfl -o test_str
	rm string.tab.c string.tab.h lex.yy.c
