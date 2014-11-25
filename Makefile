CC=gcc
TARGET=rosh
BISON=bison
FLEX=flex

all : main.c env.c input.c alias.c
	$(BISON) -d parse.y
	$(FLEX) parse.lex
	$(CC) -o $(TARGET) main.c env.c input.c alias.c parse.tab.c lex.yy.c -lfl -lm

debug : main.c env.c input.c alias.c
	$(BISON) -d parse.y
	$(FLEX) parse.lex
	$(CC) -g -o $(TARGET)  main.c env.c input.c alias.c parse.tab.c lex.yy.c -lfl -lm

test_math :
	$(BISON) -d parse.y
	$(FLEX) parse.lex
	$(CC) -g test_thing.c parse.tab.c lex.yy.c -lfl -lm -o test_math
	rm parse.tab.c parse.tab.h lex.yy.c

test_str :
	$(BISON) -d string.y
	$(FLEX) string.lex
	$(CC) string.tab.c lex.yy.c -lfl -o test_str
	rm string.tab.c string.tab.h lex.yy.c

.PHONY: clean

clean:
	rm test_math test_str
